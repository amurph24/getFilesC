#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW_CHAR_LIMIT 1024
#define KEY_COLUMN_NAME "key"
#define CSV_DELIMITER ","

int findKeyIndex(char *line, char *keyname){
	char *token;
	token = strtok(line, CSV_DELIMITER);
	for(int i = 0; token; i++) {
		// newline char disrupts check on last column header
		token[strcspn( token, "\n")] = 0;
		if (!strcmp(token, KEY_COLUMN_NAME))
			return i;
		token = strtok(NULL, CSV_DELIMITER);
	}
	return -1;
}

void printFileContents(FILE *file) {
	char line[ROW_CHAR_LIMIT];
	
	// parse headings for index of key column
	fgets(line, ROW_CHAR_LIMIT, file);
	int key_column_index = findKeyIndex(line, KEY_COLUMN_NAME);
	printf("index of 'key' column: %d\n", key_column_index);
	if (key_column_index == -1) {
		printf(".csv file does not contain a '%s' column, exiting...\n", KEY_COLUMN_NAME);
		exit(1);
	}
	
	while( fgets(line,ROW_CHAR_LIMIT,file) ) {
		printf("%s", line);
	}
	return;
}

int getFiles(int argc, char *argv[]) {
	printf("Printing contents of: %s\n", argv[1]);

	FILE *file = fopen(argv[1], "r");
	printFileContents(file);
	fclose(file);

	return 0;
}

int main(int argc, char *argv[]){
	getFiles(argc, argv);
	return 0;
}
