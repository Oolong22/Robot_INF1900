#include <avr/io.h> 

#ifndef SETLED_H
#define SETLED_H

class SetLed {
    public:
    SetLed(volatile uint8_t *port, uint8_t pin1, uint8_t pin2);

    void black();

    void green();

    void red();

    void amber();
    void flashingGreen();
    
    private:
    volatile uint8_t *port_;
    uint8_t pin1_, pin2_;
};

#endif /* SETLED_H */