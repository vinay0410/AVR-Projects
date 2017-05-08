#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    DDRA=0b00000000;

    DDRB=0b00001111;
    
    while (1) {
        if (PINA & 0b00000010) {
            //Turn Right
            PORTB=0b00000010;
        }
        else {
            //Turn left
            PORTB=0b00001000;
        }
        
        
    }


}
