#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd_16.h"


void adc_init(void)
{
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  //Prescaling factor 128
    ADMUX=(1<<REFS0);   //AVCC as Vref
}

uint16_t read_adc(uint8_t channel)
{
    
    channel &= 0b00000111;
    
    ADMUX|=channel;         //selecting adc port
    
    ADCSRA|=(1<<ADSC);    //to start conversion
    
    while(ADCSRA & (1<<ADSC));  //wait
    
    return (ADC);       //return
}


int main(void) {
	
    
    unsigned int adc_output;
    
    char buffer[5];
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    
    adc_init();
    
    while (1) {
        
        adc_output=read_adc(1);
        adc_output=adc_output/0.2046;
        
        
        itoa(adc_output/10, buffer, 10);
        
        lcd_clrscr();
        lcd_gotoxy(0, 0);
        lcd_puts(buffer);
        lcd_puts(".");
        
        itoa(adc_output - (adc_output/10)*10, buffer, 10);
        
        lcd_puts(buffer);
        
        _delay_ms(500);
        
        
        
        
    }


}
