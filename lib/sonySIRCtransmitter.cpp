#include "sonySIRCtransmitter.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "util/delay.h"
#include "timer0.h"

void SonySIRCtransmitter::sendStart() {
    timer0.send38kHz();
    _delay_us(2392);
    timer0.stopTimer();
    _delay_us(3300);
}

void SonySIRCtransmitter::sendOne() {
    timer0.send38kHz();
    _delay_us(1191);
    timer0.stopTimer();
    _delay_us(3300);
}

void SonySIRCtransmitter::sendZero() {
    timer0.send38kHz();
    _delay_us(600);
    timer0.stopTimer();
    _delay_us(3300);
}

void SonySIRCtransmitter::sendCommand(uint8_t command) {
    for (uint8_t i = 0; i < 7; i++) {
        if (command & (1 << i)) {
            sendOne();
        } else {
            sendZero();
        }
    }
}

void SonySIRCtransmitter::sendAddress(uint8_t address) {
    for (uint8_t i = 0; i < 5; i++) {
        if (address & (1 << i)) {
            sendOne();
        } else {
            sendZero();
        }
    }
}

void SonySIRCtransmitter::sendData(uint8_t command, uint8_t address) {
    sendStart();
    sendCommand(command);
    sendAddress(address);
}

void SonySIRCtransmitter::transmitLines(Segment* segmentList, uint8_t nSegments) {
    Segment segment;
    //init();
    for (uint8_t i = 0; i < nSegments; i++) {
        uint16_t crc = 0xFFFF;
        segment = segmentList[i];
        sendData(segment.size, 0);
        sendData(segment.position, 0);
        sendData(uint8_t(segment.isDown), 0);
        crc = _crc16_update(crc, segment.size);
        crc = _crc16_update(crc, segment.position);
        crc = _crc16_update(crc, segment.isDown);
        uart.transmissionUART(crc);
        sendData((crc & 127), 0 );
        sendData(((crc >> 7) & 127), 0 );
        sendData(((crc >> 14) & 127), 0 );
    }

}

void SonySIRCtransmitter::sendErrorPadding() {
    for (uint8_t i = 0; i < 36; i++) {
        sendData(0, 0);
    }
}