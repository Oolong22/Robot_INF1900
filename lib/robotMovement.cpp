#include <util/delay.h>
#include <avr/interrupt.h>
#include "robotMovement.h"

void RobotMovement::init(uint8_t correctionR, uint8_t correctionL) {
    cli();
    correctionR_ = correctionR;
    correctionL_ = correctionL;
    DDRD |= (1 << DDD4) | (1 << DDD5) |
            (1 << DDD6) | (1 << DDD7);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    sei();
}

void RobotMovement::wait(uint16_t time) {
    for (uint16_t i = 0; i < time; i++) {
        _delay_ms(25);
    }
}

void RobotMovement::modifyPWM (uint8_t ratioRight, uint8_t ratioLeft,
                               bool reverseRight, bool reverseLeft) const
{
    cli();
    if (reverseRight) { PORTD |= (1 << PORTD4); }
    else { PORTD &= ~(1 << PORTD4); }
    if (reverseLeft) { PORTD |= (1 << PORTD5); }
    else { PORTD &= ~(1 << PORTD5); }

    OCR2A = ratioRight;
    OCR2B = ratioLeft;
    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B = (1 << CS21);
    sei();
}

void RobotMovement::forward(uint8_t ratio) {
    modifyPWM(255, 255, false, false);
    _delay_ms(5);
    modifyPWM(ratio - correctionR_, ratio - correctionL_);
}

void RobotMovement::forwardR2(uint8_t ratio) {
    modifyPWM(ratio - correctionR_, ratio - correctionL_);
}

void RobotMovement::microAjustment(uint8_t ratio, bool rightSide) {
    if (rightSide) {
        // if (255 <= OCR2B + 80) {}
        // else
        //     OCR2B += 1;
        OCR2B += 35;
        _delay_ms(1);
        forwardR2(ratio);
    }
    else {
        // if (255 <= OCR2A + 80) {}
        // else
        //     OCR2A += 1;
        OCR2A += 35;
        _delay_ms(1);
        forwardR2(ratio);
    }
}

void RobotMovement::backward(uint8_t ratio) {
    modifyPWM(ratio, ratio, true, true);
}

void RobotMovement::backwardR1(uint8_t ratio) {
    modifyPWM(255, 255, true, true);
    _delay_ms(30);
    modifyPWM(ratio, ratio-8, true, true);
}

void RobotMovement::turnLeft(uint8_t ratio){
    modifyPWM(ratio, ratio, true, false);
}

void RobotMovement::turnLeftContinuous(uint8_t ratio){
    modifyPWM(255, 255, true, false);
    _delay_ms(30);
    modifyPWM(ratio, ratio + 15, true, false);
}

void RobotMovement::turnLeftTime(uint8_t ratio, uint16_t time){
    modifyPWM(255, 255, true, false);
    _delay_ms(30);
    modifyPWM(ratio, ratio, true, false);
    wait(time);
}

void RobotMovement::turnLeft90(){
    modifyPWM(125, 125, true, false);
    wait(60);
    stop();
}

void RobotMovement::turnRightContinuous(uint8_t ratio){
    modifyPWM(255, 255, false, true);
    _delay_ms(50);
    modifyPWM(ratio, ratio + 15, false, true);
}

void RobotMovement::turnRightTime(uint8_t ratio, uint16_t time){
    modifyPWM(ratio, ratio, false, true);
    wait(time);
}

void RobotMovement::turnRight90(){
    modifyPWM(153, 153, false, true);
    wait(50);
    stop();
}

void RobotMovement::turnLeft180(){ // robot1
    modifyPWM(255, 255, false, true);
    wait(1);
    modifyPWM(125, 125, false, true);
    wait(135);
    stop();
}

void RobotMovement::stop() {
    modifyPWM(0, 0);
}