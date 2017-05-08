#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_16.h"
#include <stdlib.h>
#include <math.h>

void adc_init(void) {

    ADMUX=(1<<REFS0);
    
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    
    

}

uint16_t read_adc(uint8_t channel) {
    
    
    channel&=0b00000111;
    
    ADMUX = (ADMUX & 0xF8)|channel;
    
    ADCSRA|=(1<<ADSC);
    
    while (ADCSRA & (1<<ADSC));
    
    return (ADC);
    
    
}

int main(void) {
    
    DDRD=0b11111111;
    DDRB=0b00000011;
    
    
    uint16_t x;
    uint16_t y;
    int power;
    char buffer[10];
    
    //OCR1A --> Left Motor
    //OCR1B --> Right Motor
    
    
    TCNT1=0;
    TCCR1A=0b10100010;
    TCCR1B=0b00011001;
    ICR1=500;
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);

    adc_init();
    
    while (1) {
        
        x=read_adc(1);
        y=read_adc(2);
        if (x>=950) {
            x=1023;
        }
        x=x/10;
        y=y/10;
        
        power=sqrt((x-51)*(x-51)+(y-51)*(y-51));
        if (power>51) {
            power=51;
        }
        itoa(power, buffer, 10);
        lcd_clrscr();
        lcd_puts(buffer);
        lcd_gotoxy(8, 0);
        itoa(x, buffer, 10);
        lcd_puts(buffer);
        lcd_gotoxy(8, 1);
        itoa(y, buffer, 10);
        lcd_puts(buffer);
        
        
        if (power > 1) {
        
            if (x>=51 && y>=51) {
            
                OCR1A=(power*500)/51;
                OCR1B=((y-51)*500)/51;
                PORTB=0b00000000;
                _delay_ms(100);
            }
        
            else if (x<51 && y>=51) {
            
                OCR1A=((y-51)*500)/51;
                OCR1B=(power*500)/51;
                PORTB=0b00000000;
                _delay_ms(100);
            
            }
            
            else if (x<51 && y<51) {
            
                OCR1A=(y*500)/51;
        OCR1B=((51-power)*500)/51;
                PORTB=0b00000011;
                _delay_ms(100);
            
            }
            
            else if (x>=51 && y<51) {
            
                OCR1B=(y*500)/51;
        OCR1A=((51-power)*500)/51;
                PORTB=0b00000011;
                _delay_ms(100);
            
            }
        
            else {
            //stop
                lcd_gotoxy(0, 1);
                lcd_puts("else");
                OCR1A=0;
                OCR1B=0;
                PORTB=0b00000000;
                
                
            }
        
        }
        else {
            //stop
            lcd_gotoxy(0, 1);
            lcd_puts("else");
            OCR1A=0;
            OCR1B=0;
            PORTB=0b00000000;
        
        }
        
        
    }
	
}
