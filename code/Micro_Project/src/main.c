#include <avr/io.h>
#include <LCD.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

void setup_lcd(){
    init_LCD();
    LCD_cmd(0x80);         // move cursor to the first place of the first row  
    _delay_ms(1);
    LCD_cmd(0x38);                          // 8-bit mode                 
    _delay_ms(1);
    LCD_cmd(0x01);                           // clear the screen                     
    _delay_ms(1);
    LCD_cmd(0x0E);                           // turn on the cursor
    _delay_ms(1);
    LCD_cmd(0x0F);                          // Make blinking cursor
}

void ADC_stuff() {
    DDRA = 0x00;
    ADMUX = (0 << REFS1) | (1 << REFS0); // AVCC
    ADCSRA = (1<<ADEN) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // prescale = 8

    ADCSRA |= ((1 << ADSC) | (1 << ADIF));   // start conversion
    while( (ADCSRA & (1 << ADIF)) == 0 );  // wait till end of the conversion
	PORTC = (unsigned char)ADCW; // low 8 bit (ADCL);

}

int main(void) {

    // DDRC=0xFF;
    // DDRD=0x07;

    // init_LCD();

    // ADMUX = (0 << REFS1) | (0 << REFS0); // AREF
    // ADCSRA = (1<<ADEN);
    
    // LCD_write('h');
    // while (1){

    //     ADCSRA |= ((1 << ADSC) | (1 << ADIF));
    //     while( (ADCSRA & (1 << ADIF)) == 0 );


    //     int digital=(int)ADCW;
    //     int mv = (digital/1024.0)*5000;
    //     int cel = mv/10;

    //     itoa(cel,st,10);
    //     display(st);
    //     _delay_ms(500);

    // }


    //DDRC = 0xFF;
    // DDRD = (1<<DDD0);
    // SFIOR |= (1 << ACME); // enables ADC multiplexer output

    // ADMUX |= (0 << MUX2) | (0 << MUX1) | (0 << MUX0);  // select ADC0 as AIN1
    

    // ADCSRA |= (0<<ADEN); // disable ADC


    SFIOR |= (0<<ACME); // disable ADC multiplexer output
    ACSR  |= (0<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

    while(1){
        if(((ACSR >> ACO) & 1) == 1) {
            setup_lcd();
            init_LCD();
            

        }
        else{
            
        }
            
    }


}