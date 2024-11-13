#pragma once

#include <avr/io.h>

class Segment {
public:
    Segment() = default;
    Segment(uint8_t size_, uint8_t position_, bool isDown_) {
        size = size_;
        position = position_;
        isDown = isDown_;
    }
    uint8_t size;
    uint16_t position;
    bool isDown;
};