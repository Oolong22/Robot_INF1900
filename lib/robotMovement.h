#include <avr/io.h>

#ifndef ROBOTMOVEMENT_H
#define ROBOTMOVEMENT_H

class RobotMovement {
public:
    void init(uint8_t correctionR = 0, uint8_t correctionL = 0);

    void wait(uint16_t time);

    void modifyPWM (uint8_t ratioRight, uint8_t ratioLeft,
                    bool reverseRight = false, bool reverseLeft = false) const;

    void forward(uint8_t ratio);
    void forwardR2(uint8_t ratio);
    void microAjustment(uint8_t ratio, bool rightSide);
    void backward(uint8_t ratio);
    void backwardR1(uint8_t ratio) ;

    void turnRightContinuous(uint8_t ratio);
    void turnRightTime(uint8_t ratio, uint16_t time);
    void turnRight90();

    void turnLeft(uint8_t ratio);
    void turnLeftContinuous(uint8_t ratio);
    void turnLeftTime(uint8_t ratio, uint16_t time);
    void turnLeft90();

    void turnLeft180();

    void stop();

    uint8_t correctionR_ = 0;
    uint8_t correctionL_ = 0;
};

#endif /* ROBOTMOVEMENT_H */