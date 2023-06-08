#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;

#include "battleships.h"

void singleplayer()
{
	char playerBattlefield[HORIZONTAL_SIZE][VERTICAL_SIZE];
	char robotBattlefield[HORIZONTAL_SIZE][VERTICAL_SIZE];
	memset(playerBattlefield, 'O', HORIZONTAL_SIZE * VERTICAL_SIZE);
	memset(robotBattlefield, 'O', HORIZONTAL_SIZE * VERTICAL_SIZE);

    // init player battlefield
    // init robot battlefield

    // player ships slagame
    // robot ships

    while (!isGameOver(playerBattlefield) && !isGameOver(robotBattlefield)) {
        // print player battlefield
        printBattlefield(playerBattlefield);

        // player's turn
        // get player move 
        // isValidPlacement

        // update robot battlefield
        // robot's turn
        // robot_play(playerBattlefield);

        // update player battlefield
    }

    if (isGameOver(playerBattlefield)) {
        printf("You win!\n");
    }
    else {
        printf("You lose!\n");
    }
}