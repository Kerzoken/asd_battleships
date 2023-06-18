#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;

#include "battleships.h"

char ERROR_MSG[256];

unsigned int random(unsigned int min, unsigned int max) {
	return min + rand() % (max - min + 1);
}


void singleplayer(char playerBattlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], int* battleships)
{
	char robotBattlefield[HORIZONTAL_SIZE][VERTICAL_SIZE];
	memset(robotBattlefield, 'O', HORIZONTAL_SIZE * VERTICAL_SIZE);

    // add robot ships
    for (size_t i = 0; i < 10; i++) {
		int x = random(0, 9);
		int y = random(0, 9);
		int size = random(2, 6);
		char direction = random(0, 1) == 0 ? 'H' : 'V';

		if (isValidPlacement(robotBattlefield, x, y, size, direction)) {
			for (int j = 0; j < size; j++) {
				robotBattlefield[y + (direction == 'V' ? j : 0)][x + (direction == 'H' ? j : 0)] = 'X';
			}
		}
		else {
			i--;
		}
	}

    // add player ships
	char ship[10];
	int a = 0;
	while (a != 1 && a != 2) {
		printf("Choose one of the following: \n");
		printf("1. Ready configuration\n");
		printf("2. Custom configuration\n");
		scanf("%d", &a);
	}
	

    if (a == 1) {
        add_ship_from_file(playerBattlefield, battleships);
    }

	
		////korabi s duljina 2
		//for (size_t i = 0; i < 4; i++) {
		//	printf("Enter a ship of length 2: ");
		//	scanf("%s", ship);

		//	if (fillBattlefield(playerBattlefield, ship) == ERROR_RUNTIME) {
		//		i--;
		//	}
		//}
		////korabi s duljina 3
		//for (size_t i = 0; i < 3; i++) {
		//	printf("Enter a ship of length 3: ");
		//	scanf("%s", ship);

		//	if (fillBattlefield(playerBattlefield, ship) == ERROR_RUNTIME) {
		//		i--;
		//	}
		//}

		////korabi s duljina 4
		//for (size_t i = 0; i < 2; i++) {
		//	printf("Enter a ship of length 4: ");
		//	scanf("%s", ship);

		//	if (fillBattlefield(playerBattlefield, ship) == ERROR_RUNTIME) {
		//		i--;
		//	}
		//}

		////korabi s duljina 6
		//do {
		//	printf("Enter a ship of length 6: ");
		//	scanf("%s", ship);
		//} while (fillBattlefield(playerBattlefield, ship) == ERROR_RUNTIME);

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
            add_ship(playerBattlefield, battleships);
            break;
        }
        case 2: {
            edit_position(playerBattlefield);
            break;
        }
        case 3: {
            printBattlefield(playerBattlefield);
            break;
        }
        case 4: {
			battle(playerBattlefield);
			break;
        }
        }
    } while (cmd != 4);
}