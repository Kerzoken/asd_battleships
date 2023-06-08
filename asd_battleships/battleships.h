#pragma once

#define SUCCESS 0
#define ERROR_OPEN_FILE 1
#define ERROR_RUNTIME 2
#define ERROR_INVALID_CELL 3

#define HORIZONTAL_SIZE 10
#define VERTICAL_SIZE 10

#define false 0
#define true 1

struct encrypted_message
{
    char* text;
    int size;
};