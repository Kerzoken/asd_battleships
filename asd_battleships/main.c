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

char ERROR_MSG[256];

int stoi(char* s) { return s[0] - 'A'; }

bool isValidPlacement(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE],
    int x, int y, int size, char direction) {
    if (direction == 'H') {
        for (int i = x - 1; i < x + size + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((y - 1 >= 0 && battlefield[y - 1][i] == 'X') ||
                (y - 0 >= 0 && battlefield[y - 0][i] == 'X') ||
                (y + 1 <= 9 && battlefield[y + 1][i] == 'X')) {
                return false;
            }
        }
    }
    else {
        for (int i = y - 1; i < y + size + 1; i++) {
            if (i < 0 || i > 9) continue;
            if ((x - 1 >= 0 && battlefield[i][x - 1] == 'X') ||
                (x - 0 >= 0 && battlefield[i][x - 0] == 'X') ||
                (x + 1 <= 9 && battlefield[i][x + 1] == 'X')) {
                return false;
            }
        }
    }
    return true;
}

bool isShipAvailable(int* battleships, char* ship) {
    char* temp = strdup(ship);
    int col = stoi(strtok(temp, "-"));
    int row = atoi(strtok(NULL, "-"));
    int size = atoi(strtok(NULL, "-"));
    free(temp);

    switch (size) {
    case 2:
        if (battleships[0] == 3) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
    case 3:
        if (battleships[1] == 3) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
    case 4:
        if (battleships[2] == 2) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
    case 6:
        if (battleships[3] == 1) {
            strcpy(ERROR_MSG, "There are no ships with this size available!");
            return false;
        }
    }

    return true;
}

int fillBattlefield(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships, char* ship) {
    char* temp = strdup(ship);
    int col = stoi(strtok(temp, "-"));
    int row = atoi(strtok(NULL, "-")) - 1;
    int size = atoi(strtok(NULL, "-"));
    char* direction = strtok(NULL, "-");

    if (col < 0 || row < 0) {
        fprintf(stderr, "Invalid position.\n");
        return ERROR_RUNTIME;
    }

    if (*direction == 'H') {
        if (col + size > 10) {
            strcpy(ERROR_MSG, "Invalid position.");
            return ERROR_RUNTIME;
        }
        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = col; i < col + size; i++) {
                battlefield[row][i] = 'X';
            }
        }
        else {
            strcpy(ERROR_MSG, "Ship nearby.");
            return ERROR_RUNTIME;
        }

    }
    else if (*direction == 'V') {
        if (row + size > 10) {
            strcpy(ERROR_MSG, "Invalid position.");
            return ERROR_RUNTIME;
        }
        if (isValidPlacement(battlefield, col, row, size, *direction)) {
            for (int i = row; i < row + size; i++) {
                battlefield[i][col] = 'X';
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

void add_ship(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships)
{
    printf("These are the different kinds of ships you can choose from:\n");
    printf("Four ships of lenght 2\n");
    printf("Tree ships of lenght 3\n");
    printf("Two ships of lenght 4\n");
    printf("One ship of lenght 6\n");
    printf("These are the directions the ships can be placed in:\n");
    printf("H - horizontal\n");
    printf("V - vertical\n");
    printf("Enter ship in this format: COL-ROW-SIZE-DIRECTION\n");

    char line[32];
    scanf("%s", line);

    if (isShipAvailable(battleships, line)) {
        if (fillBattlefield(battlefield, battleships, line) != SUCCESS) {
            printf("%s\n", ERROR_MSG);
        }
    }
    else {
        printf("%s\n", ERROR_MSG);
    }
}

void add_ships_from_file(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships)
{
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
        fillBattlefield(battlefield, battleships, line);
    }

    printBattlefield(battlefield);
    fclose(file);
}

void deleteShip(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships, char* ship) {
    char* temp = strdup(ship);
    int col = stoi(strtok(temp, "-"));
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
            battlefield[row][i] = 'O';
        }
    }
    else if (*direction == 'V') {
        if (row + size > 10) {
            strcpy(ERROR_MSG, "Invalid position.");
            return;
        }
        for (int i = row; i < row + size; i++) {
            battlefield[i][col] = 'O';
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
    for (int i = 0; i < VERTICAL_SIZE; i++) {
        for (int j = 0; j < HORIZONTAL_SIZE; j++) {
            printf("%c", battlefield[i][j]);
        }
        printf("\n");
    }
}

bool isHit(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int col, int row) {
    return battlefield[row][col] == 'X';
}

bool parseCoordinates(const char* input, int* col, int* row) {
    if (strlen(input) < 3) {
        return false;
    }

    *col = input[0] - 'A';
    *row = atoi(input + 2) - 1;

    return *col >= 0 && *row >= 0 && *col < HORIZONTAL_SIZE&&* row < VERTICAL_SIZE;
}

void edit_position(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships)
{
    printf("Enter ship to edit in this format: COL-ROW-SIZE-DIRECTION\n");

    char line[32];
    scanf("%s", line);

    deleteShip(battlefield, battleships, line);

    printf("Enter new ship in this format: COL-ROW-SIZE-DIRECTION\n");

    scanf("%s", line);

    if (isShipAvailable(battleships, line)) {
        if (fillBattlefield(battlefield, battleships, line) != SUCCESS) {
            printf("%s\n", ERROR_MSG);
        }
    }
    else {
        printf("%s\n", ERROR_MSG);
    }
}

void battle(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE])
{
    int totalShots = 0;
    int totalHits = 0;

    while (true) {
        printBattlefield(battlefield);

        char input[256];
        printf("\nEnter coordinates to fire: ");
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "quit\n") == 0) {
            printf("Quitting...\n");
            return 0;
        }

        int col, row;
        if (!parseCoordinates(input, &col, &row)) {
            printf("Invalid coordinates!\n");
            continue;
        }

        if (col < 0 || row < 0 || col >= HORIZONTAL_SIZE || row >= VERTICAL_SIZE) {
            printf("Invalid coordinates!\n");
            continue;
        }

        totalShots++;

        if (isHit(battlefield, col, row)) {
            printf("Hit!\n");
            battlefield[row][col] = 'H';
            totalHits++;
        }
        else {
            printf("Miss!\n");
            battlefield[row][col] = 'M';
        }

        if (totalHits == 15) {
            printf("\nYou sunk all the battleships! Game over!\n");
            break;
        }
    }
}

int main(void) {
    int battleships[] = { 0, 0, 0, 0 };

    char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE];
    memset(battlefield, 'O', HORIZONTAL_SIZE * VERTICAL_SIZE);

    int m = 0;
    do {
        printf("Choose game mode:\n");
        printf("1.Singleplayer\n");
        printf("2.Multiplayer\n");
    } while (m != 1 && m != 2);
    
    if (m == 1) {
        singleplayer(battleships, battlefield);
    }

    int n = 0;
    do {
        printf("Load ships:\n");
        printf("\t1) 1.From file\n");
        printf("\t2) 2.From console\n");
        scanf("%d", &n);
    } while (n != 1 && n != 2);

    if (n == 1) {
        add_ships_from_file(battlefield, battleships);
    }

    int cmd;
    do {
        printf("Menu:\n");
        printf("\t1) Add ship\n");
        printf("\t2) Edit position\n");
        printf("\t3) Print board\n");
        printf("\t4) Start the battle\n");

        scanf("%d", &cmd);

        switch (cmd) {
        case 1: {
            add_ship(battlefield, battleships);
            break;
        }
        case 2: {
            edit_position(battlefield, battleships);
            break;
        }
        case 3: {
            printBattlefield(battlefield);
            break;
        }
        case 4: {
            battle(battlefield);
            break;
        }
        }
    } while (cmd != 4);

    return SUCCESS;
}
