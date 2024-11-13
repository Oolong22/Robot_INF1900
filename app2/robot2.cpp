// Pour l'en-tête, voir LISEZMOI.txt

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "robot.h"
#include "sensorDefinitions.h"
#include "timer1.h"
#include "timer0.h"
#include "uart.h"
#include "memoire_24.h"
#include "sonySIRCtransmitter.h"
#include "sendMap.h"

volatile uint16_t positionCounter = 0;
volatile bool isOnVertLine = true;
const uint16_t TIMER_QUARTER_SECOND = 1953;
volatile bool isPositionTimerOn = true;

enum class State {
    INITIALIZATION,
    TURN_RIGHT,
    TURN_LEFT,
    MEASURE_LINE,
    FOLLOW_LINE,
    CALCULATE_POSITION,
    WAITING,
    TRANSMIT_TO_R1,
    TRANSMIT_TO_PC,
};

volatile State currentState = State::INITIALIZATION;

ISR ( TIMER1_COMPA_vect ) {
    positionCounter += 1;
    isPositionTimerOn = true;
}

ISR (INT0_vect) {
    _delay_ms(30);
    if (currentState == State::WAITING) {
        currentState = State::TRANSMIT_TO_R1;
    }
}


int main() {
    UART uart;
    uart.initialisationUART();
    Robot robot;
    robot.init(15, 0);
    Timer1 timer1;
    timer1.initialisation();
    Timer0 timer0;
    timer0.initialisation();
    SendMap sendMap;
    Memoire24CXXX memory;
    SonySIRCtransmitter transmitter(timer0);
    

    DDRB |= (1 << DDB0);
    //Batteries neuves: 110 - 100

    const uint8_t speed = 110; //105
    const uint8_t speedDeviation = 105; //90
    const uint8_t turnSpeed = 95; //90
    uint8_t cornerCounter = 0;
    uint16_t measureTop = 0;
    uint16_t measureBottom = 0;
    sendMap.createMap(memory);

    while (true) {
        switch (currentState) {
            case State::INITIALIZATION:
                //Load affichage into EEPROM
                robot.movement.modifyPWM(200, 255);
                _delay_ms(50);
                currentState = State::FOLLOW_LINE;
                break;

            case State::FOLLOW_LINE:
                //uart.transmissionUART((unsigned char)(positionCounter));
                if (isPositionTimerOn && !isOnVertLine) {
                    timer1.startTimer(TIMER_QUARTER_SECOND, true);
                    isPositionTimerOn = false;
                }
                robot.makerLine.correctDeviation(speedDeviation);
                if (S5) {
                    timer1.stopTimer();
                    isPositionTimerOn = false;
                    robot.movement.stop();
                    _delay_ms(500);
                    currentState = State::TURN_RIGHT;
                }
                else if (S1) {
                    timer1.stopTimer();
                    isPositionTimerOn = false;
                    robot.movement.stop();
                    _delay_ms(500);
                    currentState = State::TURN_LEFT;
                }
                break;

            case State::TURN_RIGHT:
                robot.makerLine.delayWithCorrectionPrecise(200, speed);
                robot.movement.modifyPWM(speed - 5, speed + 15);
                _delay_ms(500);
                robot.movement.stop();
                _delay_ms(500);
                if (S1 || S2 || S3 || S4 || S5) {
                    if (cornerCounter % 2 == 0) {
                        robot.movement.turnRightContinuous(turnSpeed);
                        _delay_ms(100);
                        currentState = State::FOLLOW_LINE;
                        break;
                    }
                    robot.movement.forwardR2(255);
                    _delay_ms(100);
                    robot.movement.forwardR2(speed);
                    _delay_ms(2200);
                    robot.movement.stop();
                    _delay_ms(500);
                    isPositionTimerOn = true;
                    currentState = State::MEASURE_LINE;
                    break;
                }
                else {
                    cornerCounter += 1;
                    isOnVertLine = !isOnVertLine;
                    isPositionTimerOn = true;
                    if (cornerCounter == 1) {
                        positionCounter = 5;
                    }
                    if (cornerCounter == 2) {
                        measureTop = positionCounter;
                        positionCounter = 0;
                    }
                    if (cornerCounter == 3) {
                        positionCounter = 5;
                    }
                    if (cornerCounter == 4) {
                        measureBottom = positionCounter;
                        positionCounter = 0;
                    }
                    robot.movement.forward(255);
                    _delay_ms(50);
                    robot.movement.forward(speed);
                    _delay_ms(600);
                    robot.makerLine.turnCorner(speed, turnSpeed);
                    currentState = State::FOLLOW_LINE;
                }
                break;

            case State::MEASURE_LINE:
                robot.makerLine.lineMovement(speed, turnSpeed, timer0, positionCounter, cornerCounter >= 2);
                currentState = State::FOLLOW_LINE;
                positionCounter += 5;
                break;

            case State::TURN_LEFT:
                if (cornerCounter >= 4) {
                    robot.movement.forwardR2(255);
                    _delay_ms(50);
                    robot.movement.forward(speed);
                    _delay_ms(3000);
                    robot.movement.modifyPWM(0, speed + 15, true, true);
                    _delay_ms(2000);
                    while (!S2) {}
                    robot.movement.stop();
                    _delay_ms(500);
                    robot.movement.forward(255);
                    _delay_ms(50);
                    while (S1 || S2 || S3 || S4 || S5) {
                        robot.makerLine.correctDeviation(speed);
                    }
                    robot.movement.stop();
                    _delay_ms(500);

                    currentState = State::WAITING;
                }
                else {
                    robot.movement.turnLeftContinuous(turnSpeed);
                    _delay_ms(30);
                    currentState = State::FOLLOW_LINE;
                }
                break;

            case State::CALCULATE_POSITION:
                timer1.stopTimer();
                for (uint8_t i = 0; i < 6; i++) {

                    if (robot.makerLine.segmentList[i].size == 0) {}
                    else if (robot.makerLine.segmentList[i].isDown == false) {
                        robot.makerLine.segmentList[i].position = (uint8_t)((robot.makerLine.segmentList[i].position / measureTop) * 35);
                        break;
                    }
                    else if (robot.makerLine.segmentList[i].isDown == true) {
                        robot.makerLine.segmentList[i].position = (uint8_t)((robot.makerLine.segmentList[i].position / measureBottom) * 35);
                        break;
                    }
                }
                currentState = State::WAITING;
                break;

            case State::WAITING:
                robot.led.red();
                //If D2 is pressed, transmit to R1 (ISR)
                if (PINB & (1 << PINB0)) {
                    currentState = State::TRANSMIT_TO_PC;
                }
                break;

            case State::TRANSMIT_TO_PC:
                cli();
                sendMap.addSegments(memory, robot.makerLine.segmentList);
                sendMap.printMap(memory, robot, false);
                currentState = State::WAITING;
                break;
                sei();

            case State::TRANSMIT_TO_R1:
                cli();
                robot.sound.init();
                robot.sound.song2();
                robot.led.black();
                _delay_ms(2000);
                transmitter.transmitLines(robot.makerLine.segmentList);
                transmitter.sendErrorPadding();
                currentState = State::WAITING;
                break;
                sei();
        }
    }
    

    return 0;
}