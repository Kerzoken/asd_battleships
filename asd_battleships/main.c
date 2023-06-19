#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battleships.h"

#include <time.h>

typedef int bool;

char ERROR_MSG[256];

int add_to_replay(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], char* password);
int read_replay(char* password);

bool isValidPlacement(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE],
    int x, int y, int size, char direction) {
    if (direction == 'H' || direction == DIRECTION_RIGHT) {
        for (int i = x - 1; i < x + size + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((y - 1 >= 0 && battlefield[y - 1][i] == SHIP_SPACE) ||
                (battlefield[y][i] == SHIP_SPACE) ||
                (y + 1 <= 9 && battlefield[y + 1][i] == SHIP_SPACE)) {
                return false;
            }
        }
    }
    else if (direction == DIRECTION_LEFT) {
        for (int i = x - size - 1; i < x + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((y - 1 >= 0 && battlefield[y - 1][i] == SHIP_SPACE) ||
                (battlefield[y][i] == SHIP_SPACE) ||
                (y + 1 <= 9 && battlefield[y + 1][i] == SHIP_SPACE)) {
                return false;
            }
        }
    }
    else if (direction == 'V' || direction == DIRECTION_DOWN) {
        for (int i = y - 1; i < y + size + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((x - 1 >= 0 && battlefield[i][x - 1] == SHIP_SPACE) ||
                (battlefield[i][x] == SHIP_SPACE) ||
                (x + 1 <= 9 && battlefield[i][x + 1] == SHIP_SPACE)) {
                return false;
            }
        }
    }
    else if (direction == 'V' || direction == DIRECTION_UP) {
        for (int i = y - size - 1; i < y + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((x - 1 >= 0 && battlefield[i][x - 1] == SHIP_SPACE) ||
                (battlefield[i][x] == SHIP_SPACE) ||
                (x + 1 <= 9 && battlefield[i][x + 1] == SHIP_SPACE)) {
                return false;
            }
        }
    }
    return true;
}

bool isShipAvailable(int* battleships, char* ship) {
    char* temp = _strdup(ship);
    int col = *strtok(temp, "-") - 'A';
    int row = atoi(strtok(NULL, "-")) - 1;
    int size = atoi(strtok(NULL, "-"));
    free(temp);

    switch (size) {
    case 2:
        if (battleships[0] == BATTLESHIP_2_COUNT) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
        break;
    case 3:
        if (battleships[1] == BATTLESHIP_3_COUNT) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
        break;
    case 4:
        if (battleships[2] == BATTLESHIP_4_COUNT) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
        break;
    case 6:
        if (battleships[3] == BATTLESHIP_6_COUNT) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
        break;
    default:
        strcpy(ERROR_MSG, "There are no ships with this size available! Choose from 2, 3, 4 and 6!");
        return false;
    }

    return true;
}

int fillBattlefield(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships, char* ship) {
    char* temp = _strdup(ship);
    int col = *strtok(temp, "-") - 'A';
    int row = atoi(strtok(NULL, "-")) - 1;
    int size = atoi(strtok(NULL, "-"));
    char* direction = strtok(NULL, "-");


    if (col < 0 || row < 0) {
        fprintf(stderr, "Invalid position.\n");
        return ERROR_RUNTIME;
    }

    if (*direction == 'H') {
        if (col + size > HORIZONTAL_SIZE) {
            strcpy(ERROR_MSG, "Invalid position.");
            return ERROR_RUNTIME;
        }
        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = col; i < col + size; i++) {
                battlefield[row][i] = SHIP_SPACE;
            }
        }
        else {
            strcpy(ERROR_MSG, "Ship nearby.");
            return ERROR_RUNTIME;
        }

    }
    else if (*direction == 'V') {
        if (row + size > VERTICAL_SIZE) {
            strcpy(ERROR_MSG, "Invalid position.");
            return ERROR_RUNTIME;
        }
        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = row; i < row + size; i++) {
                battlefield[i][col] = SHIP_SPACE;
            }
        }
        else {
            strcpy(ERROR_MSG, "Ship nearby.");
            return ERROR_RUNTIME;
        }

    }
    else {
        strcpy(ERROR_MSG, "Invalid direction.");
        return ERROR_RUNTIME;
    }

    int i = 0;
    if (size == 2) {
        i = 0;
    }
    else if (size == 3) {
        i = 1;
    }
    else if (size == 4) {
        i = 2;
    }
    else if (size == 6) {
        i = 3;
    }

    battleships[i]++;

    free(temp);

    return SUCCESS;
}


void deleteShip(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships, char* ship) {
    char* temp = _strdup(ship);
    int col = *strtok(temp, "-") - 'A';
    int row = atoi(strtok(NULL, "-")) - 1;
    int size = atoi(strtok(NULL, "-"));
    char* direction = strtok(NULL, "-");

    if (col < 0 || row < 0) {
        fprintf(stderr, "Invalid position.\n");
        return;
    }

    if (*direction == 'H') {
        if (col + size > 10) {
            strcpy(ERROR_MSG, "Invalid position.");
            return;
        }
        for (int i = col; i < col + size; i++) {
            battlefield[row][i] = EMPTY_SPACE;
        }
    }
    else if (*direction == 'V') {
        if (row + size > 10) {
            strcpy(ERROR_MSG, "Invalid position.");
            return;
        }
        for (int i = row; i < row + size; i++) {
            battlefield[i][col] = EMPTY_SPACE;
        }
    }
    else {
        strcpy(ERROR_MSG, "Invalid direction.");
        return;
    }

    int i = 0;
    if (size == 2) {
        i = 0;
    }
    else if (size == 3) {
        i = 1;
    }
    else if (size == 4) {
        i = 2;
    }
    else if (size == 6) {
        i = 3;
    }

    battleships[i]--;
    free(temp);
}

void printBattlefield(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE]) {
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < VERTICAL_SIZE; i++) {
        printf("%d ", i + 1);
        if (i < 9) {
            printf(" ");
        }
        for (int j = 0; j < HORIZONTAL_SIZE; j++) {
            printf("%c ", battlefield[i][j]);
        }
        printf("\n");
    }
}

bool isHit(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int col, int row) {
    return battlefield[row][col] == SHIP_SPACE;
}

bool parseCoordinates(char* input, int* col, int* row) {
    *col = input[0] - 'A';
    *row = atoi(input + 1) - 1;

    return *col >= 0 && *row >= 0 && *col < HORIZONTAL_SIZE && *row < VERTICAL_SIZE;
}

bool isShipSunk(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int col, int row, int* ship_size) {
    int size = 1;
    int i = 1;
    while (col + i < HORIZONTAL_SIZE && battlefield[row][col + i] != EMPTY_SPACE) {
        if (battlefield[row][col + i] == SHIP_SPACE)
            return false;
        size++;
        i++;
    }
    i = 1;
    while (col - i >= 0 && battlefield[row][col - i] != EMPTY_SPACE) {
        if (battlefield[row][col - i] == SHIP_SPACE)
            return false;
        size++;
        i++;
    }
    i = 1;
    while (row + i < VERTICAL_SIZE && battlefield[row + i][col] != EMPTY_SPACE) {
        if (battlefield[row + i][col] == SHIP_SPACE)
            return false;
        size++;
        i++;
    }
    i = 1;
    while (row - i >= 0 && battlefield[row - i][col] != EMPTY_SPACE) {
        if (battlefield[row - i][col] == SHIP_SPACE)
            return false;
        size++;
        i++;
    }
    *ship_size = size;
    return size == 2 || size == 3 || size == 4 || size == 6;
}

bool isGameOver(int* battleships) {
    return !battleships[0] && !battleships[1] && !battleships[2] && !battleships[3];
}

unsigned int random(unsigned int min, unsigned int max) {
    return min + rand() % (max - min + 1);
}

int main(void) {
    srand((unsigned)time(NULL));

    int gamemode;
    do {
        printf("Choose gamemode:\n");
        printf("\t1) Singleplayer\n");
        printf("\t2) Multiplayer\n");
        scanf("%d", &gamemode);
    } while (gamemode != 1 && gamemode != 2);

    int battleships1[] = { 0, 0, 0, 0 };

    char battlefield1[HORIZONTAL_SIZE][VERTICAL_SIZE];
    memset(battlefield1, EMPTY_SPACE, HORIZONTAL_SIZE * VERTICAL_SIZE);

    int n;

    do {
        printf("Load ships:\n");
        printf("\t1) From file\n");
        printf("\t2) From console\n");
        scanf("%d", &n);
    } while (n != 1 && n != 2);

    if (n == 1) {
        char filename[128];

        printf("Enter filename: ");
        scanf("%s", filename);

        FILE* file;
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Failed to open the file.\n");
            return ERROR_OPEN_FILE;
        }

        char line[32];
        while (fgets(line, 32, file) != NULL) {
            fillBattlefield(battlefield1, battleships1, line);
        }

        printBattlefield(battlefield1);
        fclose(file);
    }

    int cmd;
    do {
        printf("Menu:\n");
        printf("\t1) Add ship\n");
        printf("\t2) Edit position\n");
        printf("\t3) Print board\n");
        printf("\t4) Print replay\n");
        printf("\t5) Finish configuration for player 1\n");

        scanf("%d", &cmd);

        if (cmd == 5)
            if (battleships1[0] == BATTLESHIP_2_COUNT && battleships1[1] == BATTLESHIP_3_COUNT && battleships1[2] == BATTLESHIP_4_COUNT && battleships1[3] == BATTLESHIP_6_COUNT)
                break;
            else {
                printf("Not enough ships added!\n");
                continue;
            }

        switch (cmd) {
        case 1: {
            printf("Enter ship in this format: COL-ROW-SIZE-DIRECTION\n");

            char line[32];
            scanf("%s", line);

            if (isShipAvailable(battleships1, line)) {
                if (fillBattlefield(battlefield1, battleships1, line) != SUCCESS) {
                    printf("%s\n", ERROR_MSG);
                }
            }
            else {
                printf("%s\n", ERROR_MSG);
            }

            break;
        }
        case 2: {
            printf("Enter ship to edit in this format: COL-ROW-SIZE-DIRECTION\n");

            char line[32];
            scanf("%s", line);

            deleteShip(battlefield1, battleships1, line);

            printf("Enter new ship in this format: COL-ROW-SIZE-DIRECTION\n");

            scanf("%s", line);

            if (isShipAvailable(battleships1, line)) {
                if (fillBattlefield(battlefield1, battleships1, line) != SUCCESS) {
                    printf("%s\n", ERROR_MSG);
                }
            }
            else {
                printf("%s\n", ERROR_MSG);
            }

            break;
        }
        case 3: {
            printBattlefield(battlefield1);
            break;
        }
        case 4: {
            printf("Enter password: ");
            char password[64];
            scanf("%s", password);
            read_replay(password);
            break;
        }
        }

    } while (1);

    int battleships2[] = { 0, 0, 0, 0 };

    char battlefield2[HORIZONTAL_SIZE][VERTICAL_SIZE];
    memset(battlefield2, EMPTY_SPACE, HORIZONTAL_SIZE * VERTICAL_SIZE);

    if (gamemode == 1) {
        // SINGLEPLAYER
        for (int i = 0; i < BATTLESHIP_6_COUNT; i++) {
            int x = random(0, 9);
            int y = random(0, 9);
            int size = 6;
            char direction = random(0, 1) == 0 ? 'H' : 'V';

            if (((direction == 'H' && size + x <= HORIZONTAL_SIZE) || (direction == 'V' && size + y <= VERTICAL_SIZE)) && isValidPlacement(battlefield2, x, y, size, direction)) {
                for (int j = 0; j < size; j++) {
                    battlefield2[y + (direction == 'V' ? j : 0)][x + (direction == 'H' ? j : 0)] = SHIP_SPACE;
                }
            }
            else
                i--;
        }

        for (int i = 0; i < BATTLESHIP_4_COUNT; i++) {
            int x = random(0, 9);
            int y = random(0, 9);
            int size = 4;
            char direction = random(0, 1) == 0 ? 'H' : 'V';

            if (((direction == 'H' && size + x <= HORIZONTAL_SIZE) || (direction == 'V' && size + y <= VERTICAL_SIZE)) && isValidPlacement(battlefield2, x, y, size, direction)) {
                for (int j = 0; j < size; j++) {
                    battlefield2[y + (direction == 'V' ? j : 0)][x + (direction == 'H' ? j : 0)] = SHIP_SPACE;
                }
            }
            else
                i--;
        }

        for (int i = 0; i < BATTLESHIP_3_COUNT; i++) {
            int x = random(0, 9);
            int y = random(0, 9);
            int size = 3;
            char direction = random(0, 1) == 0 ? 'H' : 'V';

            if (((direction == 'H' && size + x <= HORIZONTAL_SIZE) || (direction == 'V' && size + y <= VERTICAL_SIZE)) && isValidPlacement(battlefield2, x, y, size, direction)) {
                for (int j = 0; j < size; j++) {
                    battlefield2[y + (direction == 'V' ? j : 0)][x + (direction == 'H' ? j : 0)] = SHIP_SPACE;
                }
            }
            else
                i--;
        }

        for (int i = 0; i < BATTLESHIP_2_COUNT; i++) {
            int x = random(0, 9);
            int y = random(0, 9);
            int size = 2;
            char direction = random(0, 1) == 0 ? 'H' : 'V';

            if (((direction == 'H' && size + x <= HORIZONTAL_SIZE) || (direction == 'V' && size + y <= VERTICAL_SIZE)) && isValidPlacement(battlefield2, x, y, size, direction)) {
                for (int j = 0; j < size; j++) {
                    battlefield2[y + (direction == 'V' ? j : 0)][x + (direction == 'H' ? j : 0)] = SHIP_SPACE;
                }
            }
            else
                i--;
        }

        battleships2[0] = BATTLESHIP_2_COUNT;
        battleships2[1] = BATTLESHIP_3_COUNT;
        battleships2[2] = BATTLESHIP_4_COUNT;
        battleships2[3] = BATTLESHIP_6_COUNT;
    }
    else {

        do {
            printf("Load ships:\n");
            printf("\t1) From file\n");
            printf("\t2) From console\n");
            scanf("%d", &n);
        } while (n != 1 && n != 2);

        if (n == 1) {
            char filename[128];

            printf("Enter filename: ");
            scanf("%s", filename);

            FILE* file;
            file = fopen(filename, "r");
            if (file == NULL) {
                printf("Failed to open the file.\n");
                return ERROR_OPEN_FILE;
            }

            char line[32];
            while (fgets(line, 32, file) != NULL) {
                fillBattlefield(battlefield2, battleships2, line);
            }

            printBattlefield(battlefield2);
            fclose(file);
        }

        int cmd;
        do {
            printf("Menu:\n");
            printf("\t1) Add ship\n");
            printf("\t2) Edit position\n");
            printf("\t3) Print board\n");
            printf("\t4) Finish configuration for player 2\n");

            scanf("%d", &cmd);

            if (cmd == 4)
                if (battleships2[0] == BATTLESHIP_2_COUNT && battleships2[1] == BATTLESHIP_3_COUNT && battleships2[2] == BATTLESHIP_4_COUNT && battleships2[3] == BATTLESHIP_6_COUNT)
                    break;
                else {
                    printf("Not enough ships added!\n");
                    continue;
                }

            switch (cmd) {
            case 1: {
                printf("Enter ship in this format: COL-ROW-SIZE-DIRECTION\n");

                char line[32];
                scanf("%s", line);

                if (isShipAvailable(battleships2, line)) {
                    if (fillBattlefield(battlefield2, battleships2, line) != SUCCESS) {
                        printf("%s\n", ERROR_MSG);
                    }
                }
                else {
                    printf("%s\n", ERROR_MSG);
                }

                break;
            }
            case 2: {
                printf("Enter ship to edit in this format: COL-ROW-SIZE-DIRECTION\n");

                char line[32];
                scanf("%s", line);

                deleteShip(battlefield2, battleships2, line);

                printf("Enter new ship in this format: COL-ROW-SIZE-DIRECTION\n");

                scanf("%s", line);

                if (isShipAvailable(battleships2, line)) {
                    if (fillBattlefield(battlefield2, battleships2, line) != SUCCESS) {
                        printf("%s\n", ERROR_MSG);
                    }
                }
                else {
                    printf("%s\n", ERROR_MSG);
                }

                break;
            }
            case 3: {
                printBattlefield(battlefield2);
                break;
            }

            }
        } while (1);
    }

    printf("GAME STARTS!\n\n");

    char fields[1000][HORIZONTAL_SIZE][VERTICAL_SIZE];
    int field_count = 0;

    int end = 0;

    char other_battlefield1[HORIZONTAL_SIZE][VERTICAL_SIZE], other_battlefield2[HORIZONTAL_SIZE][VERTICAL_SIZE];
    memset(other_battlefield1, EMPTY_SPACE, HORIZONTAL_SIZE * VERTICAL_SIZE);
    memset(other_battlefield2, EMPTY_SPACE, HORIZONTAL_SIZE * VERTICAL_SIZE);
    while (true) {
        printf("\nPLAYER 1\n");

        do {
            int a;
            do {
                printf("Menu:\n");
                printf("\t1) Show board analysis\n");
                printf("\t2) Shoot\n");
                printf("\t3) End Game\n");
                scanf("%d", &a);
            } while (a != 1 && a != 2 && a != 3);

            if (a == 1) {
                printf("\nMy board: \n");
                printBattlefield(battlefield1);
                printf("\nEnemy board: \n");
                printBattlefield(other_battlefield1);
            }
            else if (a == 2) {
                char input[32];
                printf("\nEnter coordinates to fire: ");
                scanf("%s", input);

                int col, row;
                if (!parseCoordinates(input, &col, &row)) {
                    printf("Invalid coordinates!\n");
                    continue;
                }

                if (battlefield2[row][col] == SHIP_SPACE) {
                    printf("Battleship hit!\n");
                    other_battlefield1[row][col] = SHIP_SPACE;
                    battlefield2[row][col] = HIT_SHIP_SPACE;

                    int size;
                    if (isShipSunk(battlefield2, col, row, &size)) {
                        printf("You sunk a battleship!\n");
                        if (size == 2) {
                            battleships2[0]--;
                        }
                        else if (size == 3) {
                            battleships2[1]--;
                        }
                        else if (size == 4) {
                            battleships2[2]--;
                        }
                        else if (size == 6) {
                            battleships2[3]--;
                        }
                    }

                    continue;
                }
                else {
                    printf("Nothing was hit.");
                    other_battlefield1[row][col] = HIT_EMPTY_SPACE;
                    if (battlefield2[row][col] == EMPTY_SPACE)
                        battlefield2[row][col] = HIT_EMPTY_SPACE;
                }

                memcpy(fields[field_count], battlefield1, HORIZONTAL_SIZE * VERTICAL_SIZE);
                field_count++;

                break;
            }
            else if (a == 3) {
                end = 1;
                break;
            }

            if (isGameOver(battleships2)) {
                end = 1;
                printf("\nGame Over! Player 1 Wins!\n");
                break;
            }
        } while (1);

        if (end)
            break;

        printf("\nPLAYER 2\n");

        do {
            if (gamemode == 1) {
                // SINGLEPLAYER
                int x = random(0, 9);
                int y = random(0, 9);

                if (battlefield1[y][x] == SHIP_SPACE) {
                    printf("Battleship hit!\n");
                    other_battlefield2[y][x] = SHIP_SPACE;
                    battlefield1[y][x] = HIT_SHIP_SPACE;
                    int size;
                    if (isShipSunk(battlefield1, x, y, &size)) {
                        printf("You sunk a battleship!\n");
                        if (size == 2) {
                            battleships1[0]--;
                        }
                        else if (size == 3) {
                            battleships1[1]--;
                        }
                        else if (size == 4) {
                            battleships1[2]--;
                        }
                        else if (size == 6) {
                            battleships1[3]--;
                        }
                    }

                    continue;
                }
                else {
                    printf("Nothing was hit.");
                    other_battlefield2[y][x] = HIT_EMPTY_SPACE;
                    if (battlefield1[y][x] == EMPTY_SPACE)
                        battlefield1[y][x] = HIT_EMPTY_SPACE;
                }
                printf("\n");
             
                break;
            }
            else if (gamemode == 2) {
                int a;
                do {
                    printf("Menu:\n");
                    printf("\t1) Show board analysis\n");
                    printf("\t2) Shoot\n");
                    scanf("%d", &a);
                } while (a != 1 && a != 2);

                if (a == 1) {
                    printf("\nMy board: \n");
                    printBattlefield(battlefield2);
                    printf("\nEnemy board: \n");
                    printBattlefield(other_battlefield2);
                }
                else if (a == 2) {
                    char input[32];
                    printf("\nEnter coordinates to fire: ");
                    scanf("%s", input);

                    int col, row;
                    if (!parseCoordinates(input, &col, &row)) {
                        printf("Invalid coordinates!\n");
                        continue;
                    }

                    if (battlefield1[row][col] == SHIP_SPACE) {
                        printf("Battleship hit!\n");
                        other_battlefield2[row][col] = SHIP_SPACE;
                        battlefield1[row][col] = HIT_SHIP_SPACE;

                        int size;
                        if (isShipSunk(battlefield1, col, row, &size)) {
                            printf("You sunk a battleship!\n");
                            if (size == 2) {
                                battleships1[0]--;
                            }
                            else if (size == 3) {
                                battleships1[1]--;
                            }
                            else if (size == 4) {
                                battleships1[2]--;
                            }
                            else if (size == 6) {
                                battleships1[3]--;
                            }
                        }

                        continue;
                    }
                    else {
                        printf("Nothing was hit.");
                        other_battlefield2[row][col] = HIT_EMPTY_SPACE;
                        if (battlefield1[row][col] == EMPTY_SPACE)
                            battlefield1[row][col] = HIT_EMPTY_SPACE;
                    }

                    memcpy(fields[field_count], battlefield2, HORIZONTAL_SIZE * VERTICAL_SIZE);
                    field_count++;

                    break;
                }

                if (isGameOver(battleships1)) {
                    end = 1;
                    printf("\nGame Over! Player 2 Wins!\n");
                    break;
                }
            }
        } while (1);
        if (end)
            break;
    }

    printf("Do you want to save the game in a replay?\n");
    printf("1. Yes\n");
    printf("2. No\n");

    do {
        scanf("%d", &n);
    } while (n != 1 && n != 2);

    if (n == 1) {
        printf("Enter password: ");

        char password[64];
        scanf("%s", password);

        fclose(fopen(REPLAY_FILE, "w"));

        for (int i = 0; i < field_count; i++) {
            add_to_replay(fields[i], password);
        }

        printf("Replay saved!\n");
    }

    return SUCCESS;
}