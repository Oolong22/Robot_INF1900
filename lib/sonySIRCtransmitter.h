#pragma once
#include "util/delay.h"
#include "timer0.h"
#include <util/crc16.h>
#include "segment.h"
#include "uart.h"

class SonySIRCtransmitter {
public: //transmitter
    SonySIRCtransmitter(Timer0& timer0) : timer0(timer0) {}
    // void init() {
    //     cli();
    //     EIMSK |= (1 << INT1);
    //     EICRA |= (1 << ISC11) | (0 << ISC10); 
    //     sei();
    // }
    void cycle();
    void oneBit(uint16_t time);
    void sendStart();
    void sendOne();
    void sendZero();
    void sendCommand(uint8_t command);
    void sendAddress(uint8_t address);
    void sendData(uint8_t command, uint8_t address);
    void transmitLines(Segment* segementList, uint8_t nSegments = 6);
    void sendErrorPadding();

private:
    Timer0& timer0;
    UART uart;
};