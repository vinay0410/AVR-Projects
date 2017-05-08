#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
	
    DDRA=0b00000000;
    DDRB=0b11111111;
    
    short int left_sensor, right_sensor, middle_sensor;
    
    short int pleft, pmiddle, pright;
    
    pleft=1;
    pmiddle=0;
    pright=1;
        
    
    while (1) {
    
    left_sensor=PINA&(0b00000010); //PA1
        middle_sensor=PINA&(0b00000100);//PA2
    right_sensor=PINA&(0b00001000); //PA3

    
    if ((left_sensor) && (right_sensor) && !(middle_sensor)) {
    
    //move forward   
        PORTB=0b00001010;
             
    }

    else if (!(left_sensor) && (right_sensor)) {
   
    //move left     
        PORTB=0b00001000;
    }
    
    else if ((left_sensor) && !(right_sensor)) {
    
    //move right
        PORTB=0b00000010;
    }
    
    else {
    
        if ((pleft) && (pright) && !(pmiddle)) {
            
            //stop 
            PORTB=0b00000000;
           
        }
        
        else if (!(pleft) && (pright)) {
            //move left
            
            PORTB=0b00001000;
        }
        
        else if ((pleft) && !(pright)) {
            
            //move right
            PORTB=0b00000010;    
     	}
    
    }
        if (!((left_sensor && middle_sensor && right_sensor)||(!(left_sensor) && !(middle_sensor) && !(right_sensor)))) {
                    
        pleft=left_sensor;
        pmiddle=middle_sensor;
        pright=right_sensor;
            
            }

    }

}
