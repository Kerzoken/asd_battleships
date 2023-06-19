#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "battleships.h"

struct encrypted_message* encrypt(char* text, char* key);
char* decrypt(struct encrypted_message* msg, char* key);

int add_to_replay(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], char* password)
{
    FILE* file;
    file = fopen("replay.txt", "a");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return ERROR_OPEN_FILE;
    }

    char* s = malloc(sizeof(char) * VERTICAL_SIZE * HORIZONTAL_SIZE + 1);
    assert(s != NULL);

    for (int i = 0; i < VERTICAL_SIZE; i++) {
        for (int j = 0; j < HORIZONTAL_SIZE; j++) {
            s[i * HORIZONTAL_SIZE + j] = battlefield[i][j];
        }
    }
    s[VERTICAL_SIZE * HORIZONTAL_SIZE] = '\0';

    struct encrypted_message* msg;
    msg = encrypt(s, password);

    fwrite(msg->text, sizeof(char), msg->size, file);

    fclose(file);
    return 0;
}

int read_replay(char* password)
{
    FILE* file;
    file = fopen("replay.txt", "r");

    if (file == NULL) {
        printf("Failed to open file.\n");
        return ERROR_OPEN_FILE;
    }

    int player = 1;
    while (1) {
        char board[VERTICAL_SIZE * HORIZONTAL_SIZE + 1];

        fgets(board, HORIZONTAL_SIZE * VERTICAL_SIZE + 1, file);
        if (feof(file)) {
            break;
        }

        struct encrypted_message msg;
        msg.text = board;
        msg.size = HORIZONTAL_SIZE * VERTICAL_SIZE;


        printf("Player %d:\n", player);
        printBattlefield(decrypt(&msg, password));
        printf("\n\n");

        if (player == 1)
            player = 2;
        else
            player = 1;
    }
    printf("\n\n");

    fclose(file);
    return 0;
}