#pragma once

#define SUCCESS 0
#define ERROR_OPEN_FILE 1
#define ERROR_RUNTIME 2
#define ERROR_INVALID_CELL 3

#define HORIZONTAL_SIZE 10
#define VERTICAL_SIZE 10

#define false 0
#define true 1

#define INITIAL_VECTOR "EYXoOfAaEgiTFOeaXEniD5nj83QtiKtt"

#define DIRECTION_LEFT 'L'
#define DIRECTION_RIGHT 'R'
#define DIRECTION_UP 'U'
#define DIRECTION_DOWN 'D'

#define EMPTY_SPACE '_'
#define SHIP_SPACE 'S'
#define HIT_SHIP_SPACE 'H'
#define HIT_EMPTY_SPACE 'O'

#define REPLAY_FILE "replay.txt"

#define BATTLESHIP_2_COUNT 4
#define BATTLESHIP_3_COUNT 3
#define BATTLESHIP_4_COUNT 2
#define BATTLESHIP_6_COUNT 1

struct encrypted_message
{
    char* text;
    int size;
};