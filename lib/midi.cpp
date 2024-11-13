#include "midi.h"
#include "debug.h"
#include <util/delay.h>

const uint16_t midiFrequencies[] = {
    110, 117, 123, 131, 139, 147, 156, 165, 175, 185,
    196, 208, 220, 233, 247, 262, 277, 294, 311, 330,
    349, 370, 392, 415, 440, 466, 494, 523, 554, 587,
    622, 659, 698, 738, 784, 831, 880
};

void Midi::playSound(uint8_t note) {
    if ((note <= 81) && (note >= 45)) {
        DDRB |= (1 << DDB2) | (1 << DDB3);
        uint16_t frequency = midiFrequencies[note - 45];
        uint16_t compareEval = (uint16_t)((8000000UL) / (2.0 * 256 * frequency) - 1);
        OCR0A = compareEval;
    }
}

void Midi::init() {
    DDRB |= (1 << DDB2) | (1 << DDB3);
    TCNT0 = 0;
    OCR0A = 0;
    TCCR0A = (1 << COM0A0) | (1 << COM0B0) | (1 << WGM01) ;
    TCCR0B = (1 << CS02); //Prescaler 256
    stopSound();
}

void Midi::stopSound() {
    DDRB &= ~(1 << DDB2);
    DDRB &= ~(1 << DDB3);
    OCR0A = 0;
}

void Midi::song() {
    for (uint8_t i = 0; i < 20; i++) {
        playSound(68);
        _delay_ms(10);
        stopSound();

        playSound(62);
        _delay_ms(10);
        stopSound();

        playSound(72);
        _delay_ms(10);
        stopSound();
    }
}

void Midi::song2(){
        playSound(68);
        _delay_ms(50);

        stopSound();
        _delay_ms(50);

        playSound(68);
        _delay_ms(50);

        stopSound();
        _delay_ms(50);

        playSound(81);
        _delay_ms(50);

        stopSound();
        _delay_ms(50);
}

void Midi::deepSound(){
    playSound(45);
    _delay_ms(1000);

    stopSound();
}