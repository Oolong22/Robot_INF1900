// #include <iostream>
// #include <fstream>
#include <util/delay.h>
#include <string.h>
#include "sendMap.h"

// ┌───────────────────────────────────────────────────────────────────────────────────────────────────┐\n
// │                                                                                                   │\n
// │                                                                                                   │\n
// │                                                                                                   │\n
// │   ┏━━━━━━━━━━━━━━━━━━━━━━━━┓                                                                      │\n
// │   ┃                        ┃                                                                      │\n
// │   ┃                        ┃         ╔════════════════════════════════════════════════════╗       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                                  ║                                                    ║       │\n
// │   ┃                             ═════╣                                                    ║       │\n
// │   ┃                                  ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ║                                                    ║       │\n
// │   ┃                        ┃         ╚════════════════════════════════════════════════════╝       │\n
// │   ┃                        ┃                                                                      │\n
// │   ┗━━━━━━━━━━━━━━━━━━━━━━━━┛                                                                      │\n
// │                                                                                                   │\n
// │                                                                                                   │\n
// └───────────────────────────────────────────────────────────────────────────────────────────────────┘\n
// NOM DU ROBOT: WALL-P\n"};
void SendMap::multipleChar(Memoire24CXXX& memory, uint8_t charNumber, uint8_t numberOfChars, uint16_t& currentAddress) {
    for (uint8_t i = 0; i < numberOfChars; i++) {
        memory.ecriture(currentAddress++, charNumber);
        _delay_ms(5);
    }
}

void SendMap::createMap(Memoire24CXXX& memory) {
    uint16_t address = 0x0000;

    multipleChar(memory, endLine, 1, address);

    //Line 1: "┌───────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
    multipleChar(memory, top_left_corner, 1, address);
    multipleChar(memory, horizontal_line, 99, address);
    multipleChar(memory, top_right_corner, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 2:   │                                                                                                   │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 99, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 3:   │                                                                                                   │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 99, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 4:   │                                                                                                   │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 99, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 5:   │   ┏━━━━━━━━━━━━━━━━━━━━━━━━┓                                                                      │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_top_left_corner, 1, address);
    multipleChar(memory, thick_horizontal_line, 23, address);
    multipleChar(memory, thick_top_right_corner, 1, address);
    multipleChar(memory, space, 71, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 6:   │   ┃                        ┃                                                                      │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 71, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 7:   │   ┃                        ┃         ╔════════════════════════════════════════════════════╗       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_top_left_corner, 1, address);
    multipleChar(memory, double_horizontal_line, 52, address);
    multipleChar(memory, double_top_right_corner, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 8:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 9:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 10:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 11:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 12:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 13:   │   ┃                                  ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 33, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 14:   │   ┃                             ═════╣                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 28, address);
    multipleChar(memory, double_horizontal_line, 5, address);
    multipleChar(memory, double_left_T, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 15:   │   ┃                                  ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 33, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 16:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 17:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 18:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 19:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 20:   │   ┃                        ┃         ║                                                    ║       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 52, address);
    multipleChar(memory, double_vertical_line, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 21:   │   ┃                        ┃         ╚════════════════════════════════════════════════════╝       │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 9, address);
    multipleChar(memory, double_bottom_left_corner, 1, address);
    multipleChar(memory, double_horizontal_line, 52, address);
    multipleChar(memory, double_bottom_right_corner, 1, address);
    multipleChar(memory, space, 8, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 22:   │   ┃                        ┃                                                                      │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 23, address);
    multipleChar(memory, thick_vertical_line, 1, address);
    multipleChar(memory, space, 71, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 23:   │   ┗━━━━━━━━━━━━━━━━━━━━━━━━┛                                                                      │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 3, address);
    multipleChar(memory, thick_bottom_left_corner, 1, address);
    multipleChar(memory, thick_horizontal_line, 23, address);
    multipleChar(memory, thick_bottom_right_corner, 1, address);
    multipleChar(memory, space, 71, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 24:   │                                                                                                   │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 99, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 25:   │                                                                                                   │\n
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, space, 99, address);
    multipleChar(memory, vertical_line, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 26:   └───────────────────────────────────────────────────────────────────────────────────────────────────┘\n
    multipleChar(memory, bottom_left_corner, 1, address);
    multipleChar(memory, horizontal_line, 99, address);
    multipleChar(memory, bottom_right_corner, 1, address);
    multipleChar(memory, endLine, 1, address);

    //Line 27:   NOM DU ROBOT: WALL-P\n"};
        

}

void SendMap::addSegments(Memoire24CXXX memory, Segment* list, uint8_t nSegments) {
    Segment segment;
    uint16_t address;

    for (uint8_t i = 0; i < nSegments; i++) {
        segment = list[i];
        if (segment.size == 0) {}
        else if (!segment.isDown) {
            if (segment.position > 45) {
                segment.position = 45;
            }
            address = 652 + segment.position;
            memory.ecriture(address, double_down_T);
            _delay_ms(5);
            for (uint8_t i = 0; i < segment.size; i++) {
                address += 102;
                memory.ecriture(address, double_vertical_line);
                _delay_ms(5);
            }
        }
        else {
            if (segment.position > 45) {
                segment.position = 45;
            }
            address = 2132 - segment.position;
            memory.ecriture(address, double_up_T);
            _delay_ms(5);
            for (uint8_t i = 0; i < segment.size; i++) {
                address -= 102;
                memory.ecriture(address, double_vertical_line);
                _delay_ms(5);
            }
        }
    }
}

void SendMap::addRobot(Memoire24CXXX memory, uint8_t position, bool facingDown) {
    uint16_t address;
    if (!facingDown) {
        address = 424 + 102 * position;
        multipleChar(memory, underscore, 3, address);
        address += 98;
        multipleChar(memory, diagonal_right, 1, address);
        multipleChar(memory, space, 3, address);
        multipleChar(memory, diagonal_left, 1, address);
        address += 96;
        multipleChar(memory, vertical_line, 1, address);
        multipleChar(memory, space, 5, address);
        multipleChar(memory, vertical_line, 1, address);
        address += 95;
        multipleChar(memory, wheel, 1, address);
        multipleChar(memory, space, 4, address);
        multipleChar(memory, wheel, 1, address);
        address += 97;
        multipleChar(memory, diagonal_left, 1, address);
        multipleChar(memory, underscore, 3, address);
        multipleChar(memory, diagonal_right, 1, address);
    }
    else {
        address = 424 + 102 * (13 - position);
        multipleChar(memory, underscore, 3, address);
        address += 98;
        multipleChar(memory, diagonal_right, 1, address);
        multipleChar(memory, space, 3, address);
        multipleChar(memory, diagonal_left, 1, address);
        address += 96;
        multipleChar(memory, wheel, 1, address);
        multipleChar(memory, space, 4, address);
        multipleChar(memory, wheel, 1, address);
        address += 96;
        multipleChar(memory, vertical_line, 1, address);
        multipleChar(memory, space, 5, address);
        multipleChar(memory, vertical_line, 1, address);
        address += 96;
        multipleChar(memory, diagonal_left, 1, address);
        multipleChar(memory, underscore, 3, address);
        multipleChar(memory, diagonal_right, 1, address);
    }
}

void SendMap::printMap(Memoire24CXXX& memory, Robot robot, bool isRobot1) {
    UART uart;
    uart.initialisationUART();
    uint8_t charRead;
    for (uint16_t i = 0; i < 2653; i++) {
        if ( i == (i >> 3) << 3) {
            robot.led.green();
        }
        else if ( i != (i >> 3) << 3 && i == (i >> 2) << 2 ) {
            robot.led.black();
        }
        memory.lecture(i, &charRead);
        uart.transmissionUARTstring(listCharacters[(uint8_t)charRead]);
        _delay_ms(25);
    }
    if (isRobot1)
        uart.transmissionUARTstring("NOM DU ROBOT: WALL-P\n");
}
