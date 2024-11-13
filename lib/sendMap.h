#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "memoire_24.h"
#include "segment.h"
#include "robot.h"

class SendMap {
public:
    void multipleChar(Memoire24CXXX& memory, uint8_t charNumber, uint8_t numberOfChars, uint16_t& currentAddress);

    void createMap(Memoire24CXXX& memory);

    void addSegments(Memoire24CXXX memory, Segment* liste, uint8_t nSegments = 6);

    void addRobot(Memoire24CXXX memory, uint8_t position, bool facingDown);

    void printMap(Memoire24CXXX& memory, Robot robot, bool isRobot1);

public:
    uint8_t top_left_corner = 0; // ┌
    uint8_t top_right_corner = 1; // ┐
    uint8_t bottom_left_corner = 2; // └
    uint8_t bottom_right_corner = 3; // ┘
    uint8_t horizontal_line = 4; // ─
    uint8_t vertical_line = 5; // │
    uint8_t thick_top_left_corner = 6; // ┏
    uint8_t thick_top_right_corner  = 7; // ┓
    uint8_t thick_bottom_left_corner  = 8; // ┗
    uint8_t thick_bottom_right_corner = 9; // ┛
    uint8_t thick_horizontal_line = 10; // ━
    uint8_t thick_vertical_line = 11; // ┃
    uint8_t double_top_left_corner = 12; // ╔
    uint8_t double_top_right_corner = 13; // ╗
    uint8_t double_bottom_left_corner = 14; // ╚
    uint8_t double_bottom_right_corner = 15; // ╝
    uint8_t double_horizontal_line = 16; // ═
    uint8_t double_vertical_line = 17; // ║
    uint8_t double_left_T = 18; // ╣
    uint8_t double_down_T = 19; // ╦
    uint8_t double_up_T = 20; // ╩
    uint8_t underscore = 21; // _
    uint8_t diagonal_right = 22; // ╱
    uint8_t diagonal_left = 23; // ╲
    uint8_t wheel = 24; // ▤
    uint8_t space = 25; // " "
    uint8_t endLine = 26; // \n

    char listCharacters[27][4] = {"┌", "┐", "└", "┘", "─", "│",
                                  "┏", "┓", "┗", "┛", "━", "┃",
                                  "╔", "╗", "╚", "╝", "═", "║", "╣", "╦", "╩",
                                  "_", "╱", "╲", "▤", " ", "\n"};
};