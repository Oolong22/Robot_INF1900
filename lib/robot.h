#pragma once

#include "memoire_24.h"
#include "makerLine.h"
#include "midi.h"
#include "robotMovement.h"
#include "setLed.h"
#include "uart.h"

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    Memoire24CXXX memoire;
    Midi sound;
    RobotMovement movement;
    SetLed led = SetLed(&PORTC, PORTC2, PORTC3);
    UART uart;
    MakerLine makerLine;

    Robot();

    void init(uint8_t correctionR = 0, uint8_t correctionL = 0);
};

#endif /*ROBOT_H */