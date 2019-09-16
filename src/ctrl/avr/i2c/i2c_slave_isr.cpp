#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t ledValue = 0;
volatile uint8_t refValue = 0;
volatile uint8_t status;

void send_ack(){ TWCR |= (1 << TWINT) | (1 << TWEA);}

void send_n_ack(){ TWCR &= ~(1 << TWEA); TWCR |= (1 << TWINT);}

void toggle(){PORTB ^= (1 << PORTB0);}

ISR(TWI_vect)
{
    status = TWSR & 0xF8;
    if(status == 0xA8 || status == 0xB0)
    {
        TWDR = refValue;
        send_n_ack();
        return;
    }
    if(status == 0xB8)
    {
        TWDR = refValue;
        send_n_ack();
        return;
    }
    if(status == 0xC0 || status == 0xC8)
    {
        send_ack();
        return;
    }
    if(status == 0x60 || status == 0x68 || status == 0x70|| status == 0x78)
    {
        send_ack();
        return;
    }
    if(status == 0x80 || status == 0x90)
    {
        ledValue = TWDR;
        send_n_ack();
        return;
    }
    if(status == 0x88 || status == 0x98 || status == 0xA0)
    {
        send_ack(); 
        return;
    }
    toggle();
    send_ack();
}

void initialize_pwm()
{
    DDRD |= (1 << DDD3);
    TCCR2A |= (1 << COM2B1) | (1 << WGM20);
    TCCR2B |= (1 << CS20);
}

int main(void)
{
    DDRB |= (1 << DDB0);
    initialize_pwm();
    TWAR = 10; //BitShiftLeft[5, 1];
    TWCR = (1 << TWEN) | ( 1 << TWIE) | (1 << TWEA);
    sei();

    while(1)
    {
        refValue += 5;
        if(refValue > 255){refValue = 0;}
        _delay_ms(100);
        OCR2B = ledValue;
    }

}
