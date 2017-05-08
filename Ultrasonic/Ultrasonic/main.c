#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd_16.h"

#define US_PORT PORTB
#define US_PIN PINB
#define US_DDR DDRB

#define US_TRIG PB0
#define US_ECHO PB1

#define US_ERROR -1
#define US_NO_OBSTACLE -2


void HCSInit(void);
void HCSTrigg(void);
uint16_t GetPulseWidth(void);



void HCSInit(void) {

    US_DDR|=(1<<US_TRIG);


}

void HCSTrigg(void) {

    US_PORT|=(1<<US_TRIG);

    
    _delay_us(15);
    US_PORT&=~(1<<US_TRIG);

}

uint16_t GetPulseWidth(void) {

    uint32_t i, result;
    
    for (i=0; i<600000; i++) {
        if (!(US_PIN & (1<<US_ECHO))) {
            continue;
        }
        else {
            break;
        }
        
    }

    if (i==600000) {
        return US_ERROR;
    }

    TCCR1A=0x00;
    TCCR1B=(1<<CS11);
    
    TCNT1=0x00;
    
    for (i=0; i<600000; i++) {
        if (US_PIN & (1<<US_ECHO)) {
            
            if (TCNT1 > 60000) {
                break;
            }
            else {
                continue;
            }
        
        }
        
        else {
            break;
        }
        
    }
    
        if (i==600000) {
            return US_NO_OBSTACLE;
        
        }
        
        result=TCNT1;
        TCCR1B=0x00;
        
        if (result > 60000) {
            return US_NO_OBSTACLE;
        }
        else {
            return result;
        }
    
}


int main(void) {
	
    DDRB=0b00000001;
    
    int r, d;
    
    
    
    char s[5];
    
    _delay_ms(100);
    
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    
    HCSInit();
    
    lcd_clrscr();
    lcd_gotoxy(4, 0);
    lcd_puts("Distance");
    lcd_gotoxy(5, 1);
    lcd_puts("Robot");
    _delay_ms(2500);
    
    
    
    while (1) {
    
        //PORTB=0b00000001;
        HCSTrigg();
        
        r=GetPulseWidth();
    
        if (r==US_NO_OBSTACLE) {
            lcd_clrscr();
            lcd_puts("Clear");
        }
    
        if (r==US_ERROR) {
            lcd_clrscr();
            lcd_puts("Error");
        }

        
        
        
        if ((r!=US_NO_OBSTACLE) && (r!=US_ERROR)) {
            d=r/8.7;
            r=r/87;
            
            lcd_clrscr();
            lcd_gotoxy(0, 0);
            lcd_puts("CM:");
            lcd_gotoxy(5, 0);
            itoa(r, s, 10);
            lcd_puts(s);
            lcd_puts(".");
            d = d - r*10;
            itoa(d, s, 10);
            lcd_puts(s);
            
            
        }
        
        
        
        
        
    
    
    }
    
    
    
    
}
