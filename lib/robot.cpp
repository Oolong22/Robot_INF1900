#include <util/delay.h>
#include <avr/interrupt.h>
#include "robot.h"

Robot::Robot() {
        DDRC |= (1 << PORTC2) | (1 << PORTC3);
}

void Robot::init(uint8_t correctionR, uint8_t correctionL) {
    uart.initialisationUART();
    memoire.init();
    sound.init();
    movement.init(correctionR, correctionL);
    makerLine.init();
}