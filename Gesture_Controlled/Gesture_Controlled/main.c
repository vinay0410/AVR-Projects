#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_16.h"
#include <stdlib.h>

void adc_init(void);
uint16_t read_adc(uint8_t channel);

void adc_init(void) {

    ADMUX=(1<<REFS0);
    
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    
}

uint16_t read_adc(uint8_t channel) {

    channel&=0b00000111;
    
    ADMUX=(ADMUX & 0xF8)|channel;

    ADCSRA|=(1<<ADSC);
    
    while (ADCSRA & (1<<ADSC));
    
    return (ADC);


}

int main(void) {
    
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    
    adc_init();
    DDRB=0b00001111;
    uint16_t x;
    uint16_t y;
    uint16_t z;
    char buffer[10];
    short int range = 20;
    while (1) {
        
    
    x=read_adc(1);
    y=read_adc(2);
    z=read_adc(3);
    
        lcd_clrscr();
        lcd_gotoxy(0, 0);
        itoa(x, buffer, 10);
        lcd_puts(buffer);
        
        lcd_gotoxy(5, 0);
        itoa(y, buffer, 10);
        lcd_puts(buffer);
        
        lcd_gotoxy(11, 0);
        itoa(z, buffer, 10);
        lcd_puts(buffer);
        
        
        
       if ((x-range)<334 && (x+range)>334 && (y-range)<331 && (y+range)>331 && (z-range)<264 && (z+range)>264) {
        
            //forward
            lcd_gotoxy(0, 1);
            lcd_puts("Forward");
            PORTB=0b00001010;
            _delay_ms(100);
            
        
        }
        else if ((x-range)<327 && (x+range)>327 && (y-range)<262 && (y+range)>262 && (z-range)<334 && (z+range)>334) {
        
            //stop
            lcd_gotoxy(0, 1);
            lcd_puts("Stop");
            PORTB=0b00000000;
            _delay_ms(100);
        
        }
        
        else if ((x-range)<330 && (x+range)>330 && (y-range)<397 && (y+range)>397 && (z-range)<330 && (z+range)>330) {
        
            //backward
            lcd_gotoxy(0, 1);
            lcd_puts("Backward");
            PORTB=0b00000101;
            _delay_ms(100);
        
        }
        
        else if ((x-range)<402 && (x+range)>402 && (y-range)<327 && (y+range)>327 && (z-range)<329 && (z+range)>329) {
            
            //left
            lcd_gotoxy(0, 1);
            lcd_puts("Left");
            PORTB=0b00001000;
            _delay_ms(100);
        
        }
        
        else if ((x-range)<267 && (x+range)>267 && (y-range)<330 && (y+range)>330 && (z-range)<327 && (z+range)>327) {
        
            //right
            lcd_gotoxy(0, 1);
            lcd_puts("Right");
            PORTB=0b00000010;
            _delay_ms(100);
        
        
        }
        
        else {
        
            //invalid
            lcd_gotoxy(0, 1);
            lcd_puts("Invalid");
            PORTB=0b00000000;
            _delay_ms(100);
            
        }
        
        
        
    
    }
	
}
