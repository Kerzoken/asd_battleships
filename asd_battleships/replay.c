#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "battleships.h"

int add_replay()
{
	FILE* file;
	file = fopen("replay.txt", "a");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return ERROR_OPEN_FILE;
	}

	fprintf(file, "test\n");
	fclose(file);

	return 0;
}

int read_replay()
{
	FILE* file;
	file = fopen("replay.txt", "r");

	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return ERROR_OPEN_FILE;
	}

	char line[100];
	while (fgets(line, 100, file) != NULL)
	{
		printf("%s", line);
	}

	fclose(file);
	return 0;
}