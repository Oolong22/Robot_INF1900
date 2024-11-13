#pragma once
#include "segment.h"
#include "timer0.h"
#include "uart.h"
#include "robot.h"

class SonySIRCreceiver {
 public:
     bool readInfo(Segment* segmentList, Timer0& timer0, UART& uart);
     uint16_t readCRC(Timer0& timer0, UART& uart);

private:
    uint8_t partCounter = 0;
    uint16_t counter = 0;
    bool foundReading = false;
    uint8_t bitCounter = 0;
    uint8_t fullInfoCounter = 0;
    uint8_t command = 0;
    uint8_t address = 0;
    uint8_t data[3];
    uint8_t dataCRC[3];
    uint8_t nSegmentsReceived = 0;
    Robot robot;
    
};