#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



int main(void) {
	
    DDRD = 0b00000000;
    
    DDRB=0b11111111;
    
    short int input;
    
    while (1) {
        input=PIND&0b01000000;
        
        if (input) {
            PORTB=0b00000100;  //Turn left
        
        }
        else {
            PORTB=0b00000001;  //Turn Right
        }
        
        
    }
    
    
    
    
    
}
