#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "battleships.h"

#define END_OF_REPLAY "----------"
#define END_OF_REPLAY_SIZE 10

int add_to_replay(char battlefield[HORIZONTAL_SIZE][VERTICAL_SIZE], char* password)
{
	FILE* file;
	file = fopen("replays.txt", "wa");
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

int end_replay() 
{
	FILE* file;
	file = fopen("replays.txt", "a");
	if (file == NULL) {
		printf("Failed to open file.\n");
		return ERROR_OPEN_FILE;
	}
	fprintf(file, END_OF_REPLAY);
	fclose(file);
	return 0;
}

int read_replay(char* password)
{
	FILE* file;
	file = fopen("replays.txt", "r");

	if (file == NULL) {
		printf("Failed to open file.\n");
		return ERROR_OPEN_FILE;
	}

	int i = 1;
	while (feof(file)) {
		printf("Game %d:\n", i);
		while (1) {
			// check for end of replay
			char tmp[END_OF_REPLAY_SIZE + 1];
			fgets(tmp, END_OF_REPLAY_SIZE, file);
			tmp[END_OF_REPLAY_SIZE] = '\0';

			if (!strcmp(tmp, END_OF_REPLAY))
				break;

			fseek(file, -END_OF_REPLAY_SIZE, SEEK_CUR);

			char line[VERTICAL_SIZE * HORIZONTAL_SIZE];
			fgets(line, HORIZONTAL_SIZE * VERTICAL_SIZE, file);

			struct encrypted_message msg;
			msg.text = line;
			msg.size = HORIZONTAL_SIZE * VERTICAL_SIZE;

			//char board[HORIZONTAL_SIZE][VERTICAL_SIZE] = decrypt(&msg, password);

			printBattlefield(decrypt(&msg, password));
			printf("\n\n");
		}
		printf("\n");
		i++;
	}
	fclose(file);
	return 0;
}