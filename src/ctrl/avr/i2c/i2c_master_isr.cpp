void send_start(){ TWCR &= ~(1 << TWSTO); TWCR |= (1 << TWINT) | (1 << TWSTA); }

void send_stop(){ TWCR &= ~(1 << TWSTA);  TWCR |= (1 << TWINT) | (1 << TWSTO); }

void send_data(){ TWCR &= ~((1 << TWSTA) | (1 << TWSTO)); TWCR |= (1 << TWINT); }

void toggle(){PORTB ^= (1 << PORTB0);}

ISR(TWI_vect)
{
    status = TWSR & 0xF8;
    if(status == 0x08 || status == 0x10)
    {
        pstatus = 1;
        TWDR = rw;
        send_data();
        return;
    }
    if(status == 0x38)
    {
        pstatus = 2;
        send_start();
        return;
    }
    if(status == 0x40)
    {
        pstatus = 3;
        TWCR &= ~(1 << TWEA);
        send_data();
        return;
    }
    if(status == 0x48)
    {
        pstatus = 4;
        send_start();
        return;
    }
    if(status == 0x50)
    {
        pstatus = 5;
        ledValue = TWDR;
        TWCR &= ~(1 << TWEA);
        send_data();
        return;
    }
    if(status == 0x58)
    {
        pstatus = 6;
        ledValue = TWDR;
        receiveQ = false;
        transmitQ = true;
        send_stop();
        return;
    }
    if(status == 0x18 || status == 0x20)
    {
        pstatus = 7;
        TWDR = refValue; //data to be transmitted
        send_data();
        return;
    }
    if(status == 0x28 || status == 0x30)
    {
        pstatus = 8;
        receiveQ = true;
        transmitQ = false;
        send_stop();
        return;
    }
    if((pstatus == 8 || pstatus == 6)){toggle();}
    pstatus = 0;
    send_stop();
}


int main(void)
{
    DDRB |= (1 << DDB0);
    TWBR = 10;
    TWCR = (1 << TWEN) | (1 << TWIE);
    sei();

    while(1)
    {
        if(receiveQ)
        {
            rw = 11; //BitShiftLeft[5, 1] + 1, read
            refValue += 5;
            if(refValue > 255){refValue = 0;}
            send_start();
        }
        _delay_ms(100);
        OCR2B = ledValue;
        if(transmitQ)
        {
            rw = 10; //BitShiftLeft[5, 1], write
            send_start();
        }
    }
    return 0;

}
