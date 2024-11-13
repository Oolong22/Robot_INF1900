#include "sonySIRCreceiver.h"
#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>
#include "robot.h"
#include <util/crc16.h>

const uint16_t READING_DELAY = 50;

enum class State {
    SCANNING,        // Scanning for a start bit
    COMMAND_READING, // Reading the command
    ADDRESS_READING, // Reading the address
    COMPUTING
};
// 40 à 54 pour les startBit
// 10 à 18 pour les zéros
// 19 à 27 pour les un

bool SonySIRCreceiver::readInfo(Segment* segmentList, Timer0& timer0, UART& uart) {
    bool isCorrupted = false;
    State currentState = State::SCANNING;
    while (true) {
        switch (currentState) {
            case State::SCANNING:
                if (fullInfoCounter == 3) {
                    currentState = State::COMPUTING;
                    fullInfoCounter = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    foundReading = true;
                }
                while (foundReading) {
                    if (!(PINA & (1 << PINA1))) {
                        counter++;
                    }
                    
                    if ((PINA & (1 << PINA1))) {
                        if (counter >= 40 && counter <= 54) {
                            currentState = State::COMMAND_READING;
                            foundReading = false;
                        }
                        if (counter >= 3) {
                            //uart.transmissionUART(counter);
                        }
                        counter = 0;
                        //break;
                    }
                    _delay_us(READING_DELAY);
                }
                break;

            case State::COMMAND_READING:
                if (bitCounter == 7) {
                    //uart.transmissionUART(32);
                    currentState = State::ADDRESS_READING;
                    partCounter++;
                    bitCounter = 0;
                    data[fullInfoCounter] = command;
                    command = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    counter++;
                }
                if ((PINA & (1 << PINA1))) {
                    if (counter >= 19 && counter <= 27) { //Received 1
                        //uart.transmissionUART('1');
                        command |= (1 << bitCounter);
                        bitCounter++;
                    }
                    else if (counter >= 10 && counter <= 18) { //Received 0
                        //uart.transmissionUART('0');
                        command &= ~(1 << bitCounter);
                        bitCounter++;
                    }
                    counter = 0;
                }
                _delay_us(READING_DELAY);
                break;
                
            case State::ADDRESS_READING:
                if (bitCounter == 5) {
                    //uart.transmissionUART(32);
                    //uart.transmissionUART(32);
                    currentState = State::SCANNING;
                    partCounter++;
                    bitCounter = 0;
                    fullInfoCounter++;
                    address = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    counter++;
                }
                if ((PINA & (1 << PINA1))) {
                    if (counter >= 19 && counter <= 27) { //Received 1
                        //uart.transmissionUART('1');
                        address |= (1 << bitCounter);
                        bitCounter++;
                    }
                    else if (counter >= 10 && counter <= 18) { //Received 0
                        //uart.transmissionUART('0');
                        address &= ~(1 << bitCounter);
                        bitCounter++;
                    }
                    counter = 0;
                }
                _delay_us(READING_DELAY);
                break;

            case State::COMPUTING:
                uint16_t crcReceived = readCRC(timer0, uart);
                uint16_t crc = 0xFFFF;
                //uart.transmissionUART(data[0]);
                //uart.transmissionUART(data[1]);
                //uart.transmissionUART(data[2]);
                crc = _crc16_update(crc, data[0]);
                crc = _crc16_update(crc, data[1]);
                crc = _crc16_update(crc, data[2]);
                //uart.transmissionUART(crcReceived);
                //uart.transmissionUART(crc);
                if (crcReceived == crc) {
                    currentState = State::COMMAND_READING;
                    segmentList[nSegmentsReceived].size = data[0];
                    segmentList[nSegmentsReceived].position = data[1];
                    segmentList[nSegmentsReceived].isDown = data[2];
                    //uart.transmissionUART('R');
                    //uart.transmissionUARTstring("Segment: ");
                    // uart.transmissionUART(uint8_t(data[0]));
                    // uart.transmissionUART(uint8_t(data[1]));
                    // uart.transmissionUART(uint8_t(data[2]));
                }
                else {
                    //uart.transmissionUART('F');
                    isCorrupted = true;
                    segmentList[nSegmentsReceived] = Segment(0, 0, 0);
                }
                nSegmentsReceived++;

                if (nSegmentsReceived < 6) {
                    currentState = State::SCANNING; 
                }
                else {
                    return isCorrupted;
                }
        }
    }
}

uint16_t SonySIRCreceiver::readCRC(Timer0& timer0, UART& uart) {
    State currentStateCRC = State::SCANNING;
    while (true) {
        switch (currentStateCRC) {
            case State::SCANNING:
                if (fullInfoCounter == 3) {
                    currentStateCRC = State::COMPUTING;
                    fullInfoCounter = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    foundReading = true;
                }
                while (foundReading) {
                    if (!(PINA & (1 << PINA1))) {
                        counter++;
                    }
                    
                    if ((PINA & (1 << PINA1))) {
                        if (counter >= 30) {
                            currentStateCRC = State::COMMAND_READING;
                            foundReading = false;
                        }
                        // if (counter >= 3) {
                        //     uart.transmissionUART(counter);
                        // }
                        counter = 0;
                        break;
                    }
                    _delay_us(READING_DELAY);
                }
                break;

            case State::COMMAND_READING:
                if (bitCounter == 7) {
                    currentStateCRC = State::ADDRESS_READING;
                    bitCounter = 0;
                    dataCRC[fullInfoCounter] = command;
                    command = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    counter++;
                }
                if ((PINA & (1 << PINA1))) {
                    if (counter >= 19 && counter <= 27) { //Received 1
                        command |= (1 << bitCounter);
                        bitCounter++;
                    }
                    else if (counter >= 10 && counter <= 18) { //Received 0
                        command &= ~(1 << bitCounter);
                        bitCounter++;
                    }
                    counter = 0;
                }
                _delay_us(READING_DELAY);
                break;
                
            case State::ADDRESS_READING:
                if (bitCounter == 5) {
                    currentStateCRC = State::SCANNING;
                    bitCounter = 0;
                    fullInfoCounter++;
                    address = 0;
                    break;
                }
                if (!(PINA & (1 << PINA1))) {
                    counter++;
                }
                if ((PINA & (1 << PINA1))) {
                    if (counter >= 19 && counter <= 27) { //Received 1
                        //uart.transmissionUART('1');
                        address |= (1 << bitCounter);
                        bitCounter++;
                    }
                    else if (counter >= 10 && counter <= 18) { //Received 0
                        //uart.transmissionUART('0');
                        address &= ~(1 << bitCounter);
                        bitCounter++;
                    }
                    counter = 0;
                }
                _delay_us(READING_DELAY);
                break;

            case State::COMPUTING:
                // uart.transmissionUART(dataCRC[0]);
                // uart.transmissionUART(dataCRC[1]);
                // uart.transmissionUART(dataCRC[2]);
                uint16_t crc = 0;
                crc = dataCRC[2];
                crc = (crc << 7);
                crc |= dataCRC[1];
                crc = (crc << 7);
                crc |= dataCRC[0];

                return crc;
        }
    }
}