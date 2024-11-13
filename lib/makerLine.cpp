#include "makerLine.h"
#include "debug.h"
#include <util/delay.h>
#include "sensorDefinitions.h"
#include "timer0.h"
#include "segment.h"

// #define S1 (PINA & (1 << PINA0))
// #define S2 (PINA & (1 << PINA1))
// #define S3 (PINA & (1 << PINA2))
// #define S4 (PINA & (1 << PINA3))
// #define S5 (PINA & (1 << PINA4))

//Specifications des lignes:
//Longueur : 4,5, 6,5 ou 8,5 pouces
//Distance minimale de 9 pouces de AE et BF
//Distance minimale de 9 pouces de tout autre segment ajouté

volatile uint16_t lineMeasure = 0;
const uint16_t LINE_DETECTION_TIME_LIMIT = 300;


ISR ( TIMER0_COMPA_vect ) { //Comppteur pour mesure de ligne
    lineMeasure += 1; //1 seconde = 116 fois
}

void MakerLine::followLine(uint8_t speed, uint8_t turnSpeed, Timer0& timer0) {
    if (S5) { //Turn Right
        _delay_ms(500);
        if (S3) { //Trouver segment
            //lineMovement(speed, turnSpeed, timer0, );
        }
        else if (!S3) {
            turnCorner(speed, turnSpeed);
        }
    }
    else if (S1) { //Turn Left
        delayWithCorrection(speed);
        turnLeftContinuous(turnSpeed);
        _delay_ms(1000);
        while (!S2 && !S3) {} //TEST: Reversed

    }
    else
        correctDeviation(speed);
}

void MakerLine::delayWithCorrection(uint8_t speed) {
    uint16_t delay = (speed * 5);
    for (uint16_t i = 0; i != delay; i++) {
        correctDeviation(speed);
        _delay_ms(1);
    }
}

void MakerLine::delayWithCorrectionPrecise(uint16_t delay, uint8_t speed) {
    forwardR2(255);
    _delay_ms(50);
    for (uint16_t i = 0; i != delay ; i++) {
        correctDeviation(speed);
        _delay_ms(1);
    }
}

void MakerLine::correctDeviation(uint8_t speed) { 
    if (S4)
        microAjustment(speed, true);
    else if (S2)
        microAjustment(speed, false);
    else {
        forwardR2(speed);
    }
}

// void MakerLine::correctDeviationBackward(uint8_t speed) { 
//     if (S2)
//         microAjustmentBackward(speed, true);
//     else if (S4)
//         microAjustmentBackward(speed, false);
//     else {
//         backward(speed);
//     }
// }

void MakerLine::correctDeviationHard(uint8_t speed) {
    if (S4 || S5)
        microAjustment(speed, true);
    else if (S2 || S1)
        microAjustment(speed, false);
    else {
        forwardR2(speed);
    }
}

void MakerLine::lineMeasurement(uint8_t speed, Timer0& timer0, uint16_t position, bool isDown) {
    //Start Timer0
    lineMeasure = 0;
    timer0.startTimer(255, true);
    forwardR2(255);
    _delay_ms(50);
    while (S1 || S2 || S3 || S4 || S5) {
        correctDeviationHard(speed);
    }
    timer0.stopTimer();
    if (lineMeasure < 120) {
        //save line as 4.5 inches
        segmentList[lineCounter] = Segment(2, position, isDown);
    }
    else if (lineMeasure < 200) {
        //save line as 6.5 inches
        segmentList[lineCounter] = Segment(3, position, isDown);
    }
    else {
        //save line as 8.5 inches
        segmentList[lineCounter] = Segment(4, position, isDown);
    }
    lineCounter++;

    stop();
    _delay_ms(1000);
}

void MakerLine::lineMovement(uint8_t speed, uint8_t turnSpeed, Timer0& timer0, uint16_t position, bool isDown) {
    stop();
    _delay_ms(500);
    //Tourne sur la ligne
    modifyPWM(speed + 5, 0, false, true);
    _delay_ms(1000);
    while (!S3) {}
    stop();
    _delay_ms(500);
    //Avance sur la ligne pour mesurer
    lineMeasurement(speed, timer0, position, isDown);
    //Recule
    modifyPWM(200, 200 + 8, true, true);
    _delay_ms(50);
    modifyPWM(speed - 25, speed, true, true);
    while (!S1 || !S2 || !S3 || !S4 || !S5) {}
    while (S1 || S2 || S3 || S4 || S5) {}
    forwardR2(255);
    _delay_ms(10);
    stop();
    _delay_ms(500);
    forwardR2(255);
    _delay_ms(80);
    forward(speed);
    _delay_ms(1500);
    stop();
    _delay_ms(500);
    turnLeftContinuous(255);
    _delay_ms(50);
    turnLeftContinuous(turnSpeed);
    _delay_ms(500);
    while (!S3) {}
    stop();
    _delay_ms(500);
    forwardR2(255);
    _delay_ms(50);
}

void MakerLine::turnCorner(uint8_t speed, uint8_t turnSpeed) {
    delayWithCorrection(speed);
    turnRightContinuous(turnSpeed);
    while (!S3) {}
    stop();
    _delay_ms(500);
    forwardR2(255);
    _delay_ms(40);
}