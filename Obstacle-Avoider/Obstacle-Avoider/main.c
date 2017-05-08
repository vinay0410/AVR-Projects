#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_16.h"
#include <stdlib.h>


void adc_init(void);
uint16_t read_adc(uint8_t channel);


void adc_init(void) {

    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    
    ADMUX=(1<<REFS0);

}

uint16_t read_adc(uint8_t channel) {

    channel&=0b00000111;
    
    ADMUX = (ADMUX & 0xF8)|channel;
    
    ADCSRA|=(1<<ADSC);
    
    while (ADCSRA & (1<<ADSC));
        
    return (ADC);

}


int main(void) {
    
    DDRB=0b00001111;
    
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    
    adc_init();
    
    char buffer[6];
    
    uint16_t left, center, right;
    
    while (1) {
     
    left=read_adc(1);
    center=read_adc(2);
    right=read_adc(3);
        
        lcd_clrscr();
        itoa(left, buffer, 10);
        lcd_gotoxy(0, 0);
        lcd_puts(buffer);
        itoa(center, buffer, 10);
        lcd_gotoxy(5, 0);
        lcd_puts(buffer);
        itoa(right, buffer, 10);
        lcd_gotoxy(10, 0);
        lcd_puts(buffer);
        
        
                
        if (left>300 && right>300) {
        
            if (center>360) {
            
                if (left<right-50) {
                
                    while (left>380) {
                        
                        PORTB=0b00001001;
                        left=read_adc(1);
                    }
                
                }
                else {
                
                    while (right>380) {
                        PORTB=0b00000110;
                        right=read_adc(3);
                        
                    }
                
                }
            
            }
            else {
                if (left<800 && right<800) {
                    PORTB=0b00001010;
                }
                else {
                    PORTB=0b00000101;
                    _delay_ms(400);
                    PORTB=0b00001001;                    
                    _delay_ms(500);
                    
                    
                }
            
            }
        
        }
        else if (left>300 && right<300) {
    
        
            PORTB=0b00000110;
        
        }
        else if (left<300 && right>300) {
        
            PORTB=0b00001001;
        
        }
        else if (left<300 && center<360 && right<300) {
    
            PORTB=0b00001010;
    
    
        }
        else if (left<300 && center>350 && right<300) {
            if (left<right-80) {
                PORTB=0b00000101;
                _delay_ms(500);
                PORTB=0b00001001;
                _delay_ms(500);
            }
            else {
                PORTB=0b00000101;
                _delay_ms(500);
                PORTB=0b00000110;
                _delay_ms(500);
            }
        
        }
        else {
            PORTB=0b00000000;
        }

}
}