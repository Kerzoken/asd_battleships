#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;

#define SUCCESS 0
#define ERROR_OPEN_FILE 1
#define ERROR_RUNTIME 2
#define ERROR_INVALID_CELL 3

#define HORIZONTAL_SIZE 10
#define VERTICAL_SIZE 10

#define false 0
#define true 1

int stoi(char* s) { return s[0] - 'A'; }

bool isValidPlacement(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE],
    int x, int y, int size, char direction) {
    if (direction == 'H') {
        for (int i = x - 1; i < x + size + 1; i++) {
            if ((y - 1 >= 0 && battlefield[y - 1][i] == 'X') ||
                (y - 0 >= 0 && battlefield[y - 0][i] == 'X') ||
                (y + 1 <= 9 && battlefield[y + 1][i] == 'X')) {
                return false;
            }
        }
    }
    else {
        for (int i = y - 1; i < y + size + 1; i++) {
            if ((x - 1 >= 0 && battlefield[i][x - 1] == 'X') ||
                (x - 0 >= 0 && battlefield[i][x - 0] == 'X') ||
                (x + 1 <= 9 && battlefield[i][x + 1] == 'X')) {
                return false;
            }
        }
    }
    return true;
}

int fillBattlefield(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], char* ship) {
    int col = stoi(strtok(ship, "-"));
    int row = atoi(strtok(NULL, "-")) - 1;
    int size = atoi(strtok(NULL, "-"));
    char* direction = strtok(NULL, "-");

    if (col < 0 || row < 0) {
        fprintf(stderr, "Invalid position.\n");
        return ERROR_RUNTIME;
    }

    if (*direction == 'H') {
        if (col + size > 10) {
            fprintf(stderr, "Invalid position.\n");
            return ERROR_RUNTIME;
        }

        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = col; i < col + size; i++) {
                battlefield[row][i] = 'X';
            }
        }
        else {
            fprintf(stderr, "Ship nearby.");
            return ERROR_RUNTIME;
        }
    }
    else if (*direction == 'V') {
        if (row + size > 10) {
            fprintf(stderr, "Invalid position.\n");
            return ERROR_RUNTIME;
        }

        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = col; i < col + size; i++) {
                battlefield[row][i] = 'X';
            }
        }
        else {
            fprintf(stderr, "Ship nearby.");
            return ERROR_RUNTIME;
        }
    }
    else {
        fprintf(stderr, "Invalid direction.");
        return ERROR_RUNTIME;
    }
}

void printBattlefield(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE]) {
    for (int i = 0; i < VERTICAL_SIZE; i++) {
        for (int j = 0; j < HORIZONTAL_SIZE; j++) {
            printf("%c", battlefield[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE];
    memset(battlefield, 'O', HORIZONTAL_SIZE * VERTICAL_SIZE);

    FILE* file;
    file = fopen("ships.conf", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return ERROR_OPEN_FILE;
    }

    char line[32];
    while (fgets(line, 32, file) != NULL) {
        fillBattlefield(battlefield, line);
    }

    printBattlefield(battlefield);
    fclose(file);

    return SUCCESS;
}