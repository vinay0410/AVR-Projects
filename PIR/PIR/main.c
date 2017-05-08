#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void adc_init(void);
uint16_t read_adc(uint8_t channel);

void adc_init(void) {

    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    ADMUX=(1<<REFS0);


}

uint16_t read_adc(uint8_t channel) {

    channel&=0b00000111;

    ADMUX=(ADMUX&0xF8)|channel;

    ADCSRA|=(1<<ADSC);
    
    while (ADCSRA & (1<<ADSC));

    return (ADC);


}

int main(void) {
    
    DDRB=0b11111111;
    
    adc_init();
    
    uint16_t pir;
    
    while (1) {
        
        pir=read_adc(1);
        
        if (pir>300) {
            PORTB=0b00010000;
            //_delay_ms(1000);
        }
        else {
            PORTB=0b00000000;
        }
    }
    
}
