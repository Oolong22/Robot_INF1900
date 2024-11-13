#include <avr/io.h>

#ifndef MIDI_H
#define MIDI_H

class Midi {
public:
    void playSound(uint8_t note);

    void init();

    void stopSound();

    void song();

    void song2();

    void deepSound();
};

#endif /* MIDI_H */