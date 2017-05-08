#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd_16.h"


int main(void) {
	
    DDRD=0b00001111;
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    
    PORTD= (PORTD & 0b11110000) | 0b00000000;
    lcd_puts("HELLO");
    lcd_gotoxy(0, 1);
    lcd_puts("Waiting");
    _delay_ms(5000);
    
    while (1) {
        if (!((PIND & 0xf0) & ~(0x20)))  {
            if (!(PORTD == ((PORTD & 0b11110000) | 0b00001010))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("Moving Forward");
                PORTD = (PORTD & 0b11110000) | 0b00001010;
            }
        }
        else if (!((PIND & 0xf0) & ~(0x40))) {
            if(!(PORTD== ((PORTD & 0b11110000) | 0b00001000))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("Turing Left");
            PORTD= (PORTD & 0b11110000) | 0b00001000;
            }
        }
        else if (!((PIND & 0xf0) & ~(0x50))) {
            if(!(PORTD== ((PORTD & 0b11110000) | 0b00000000))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("Stopped");
            PORTD= (PORTD & 0b11110000) | 0b00000000;
            }
        }
        else if (!((PIND & 0xf0) & ~(0x60))) {
            if(!(PORTD== ((PORTD & 0b11110000) | 0b00000010))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("Turning Right");
            PORTD= (PORTD & 0b11110000) | 0b00000010;
            }
        }
        else if (!((PIND & 0xf0) & ~(0x80))) {
            if(!(PORTD== ((PORTD & 0b11110000) | 0b00000101))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("Moving Backward");
            PORTD= (PORTD & 0b11110000) | 0b00000101;
            }
        }
        else {
            if(!(PORTD== ((PORTD & 0b11110000) | 0b00000000))) {
            lcd_clrscr();
            lcd_puts("HELLO");
            lcd_gotoxy(0, 1);
            lcd_puts("INVALID INPUT");
            PORTD= (PORTD & 0b11110000) | 0b00000000;
            }
        }




    }
    
}
