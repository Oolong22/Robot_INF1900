// Pour l'en-tête, voir LISEZMOI.txt

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.h"
#include "robot.h"
#include "sendMap.h"
#include "setLed.h"
#include "timer0.h"
#include "timer1.h"
#include "sonySIRCreceiver.h"

volatile bool gTimerExpired = false;
volatile bool gButton = 0;

const uint16_t TWO_SECONDS_TIMER = 7812 * 2;
const uint8_t center = 40;
const uint8_t CENTER_MIN = center-5;
const uint8_t CENTER_MAX = center + 10;
const uint8_t OPENING = 20;
const uint8_t ONE_SECOND = 40;
const uint8_t PIN_DEBOUNCE = 6;
const uint8_t CORRECTION_RIGHT_WHEEL = 25;

 enum class Step {
    GET_POSITION,
    GET_TO_CENTER,
    FIND_OPENING,
    WAIT,
    RECEIVE,
    TRANSMIT
};

ISR ( TIMER1_COMPA_vect ) {
    gTimerExpired = true;
}

ISR ( INT0_vect ) {
    _delay_ms(30);
    gButton = 1;
}

int main() {
    DDRA &= ~(1 << DDA6);
     
    Robot robot;  
    robot.init(CORRECTION_RIGHT_WHEEL, 0);

    can converter;
    
    Timer1 timer1;
    timer1.initialisation();
    
    SendMap map;

    Timer0 timer0;
    

    SonySIRCreceiver receiver;
    Segment segmentsReceived[6];
    bool isCorrupted = false;
    uint16_t position = 0;
    bool isFacingDown = true;

    Step step = Step::GET_POSITION;
    robot.movement.wait(ONE_SECOND); 
    uint16_t tryList[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint16_t distance;
    while(true) {
        for (uint8_t i =0; i < 10; i++){
            distance = converter.lecture(PIN_DEBOUNCE) >> 2;
            tryList[i] = distance;
        }

        uint16_t minValue = tryList[0] ;
        uint16_t maxValue = tryList[0] ;
        uint16_t averageDistance; 
        for (uint8_t i = 0; i < 10; i++){
            if( tryList[i] < minValue){
                minValue = tryList[i];
            }
            if (tryList[i] > maxValue){
                maxValue = tryList[i];
            }
            averageDistance += tryList[i];
        }

        averageDistance -= (maxValue + minValue);
        averageDistance /= 8;

        switch(step) {
            case Step::GET_POSITION:
                position = distance;
                if (position > CENTER_MAX) {
                    position = 3;
                }
                else if (CENTER_MAX > position && position > CENTER_MIN) {
                    position = 7;
                }
                else {
                    position = 11;
                }

                step = Step::GET_TO_CENTER;
                
                break;

            case Step::GET_TO_CENTER:
                if (averageDistance > CENTER_MAX && (!(averageDistance < CENTER_MIN))) {
                    robot.movement.wait(ONE_SECOND);
                    robot.movement.backwardR1(110);
                }

                else if (averageDistance < CENTER_MIN) {
                    robot.movement.wait(ONE_SECOND);
                    robot.movement.forward(145);
                }

                else {
                    robot.movement.stop();
                    _delay_ms(500);
                    
                    timer1.startTimer(TWO_SECONDS_TIMER, true);
                    step = Step::FIND_OPENING;
                }
                break;

            case Step::FIND_OPENING:
                if (!(distance < OPENING)){
                    robot.movement.turnLeft(110);
                }

                else{
                    robot.movement.stop();
                    if (gTimerExpired) {
                        isFacingDown = false;
                    }
                    else {
                        isFacingDown = true;
                    }
                    gButton = false;
                    step = Step::WAIT;
                }
                break;

            case Step::WAIT:
                robot.led.red();
                if (gButton){
                    robot.sound.song2();
                    gButton = false;
                    step = Step::RECEIVE;
                }
                break;

            case Step::RECEIVE:
                robot.led.black();
                isCorrupted = receiver.readInfo(segmentsReceived, timer0, robot.uart);
                if(!isCorrupted){
                    step = Step::TRANSMIT;
                }

                else{
                    robot.sound.deepSound();
                    step = Step::WAIT;
                }
                break;

            case Step::TRANSMIT:
                robot.led.green();
                map.createMap(robot.memoire);
                map.addSegments(robot.memoire, segmentsReceived);
                map.addRobot(robot.memoire, position, isFacingDown);
                if (gButton){
                    map.printMap(robot.memoire, robot, true);
                    gButton = false;
                }
                break;
        } 
    }
}