#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_CHAR_LIMIT 1024
#define KEY_COLUMN_NAME "key"
#define CSV_DELIMITER ","

int find_key_index(char *line, char *key_name){
	char *token;
	token = strtok(line, CSV_DELIMITER);
	for(int i = 0; token; i++) {
		// newline char disrupts check on last column header
		token[strcspn( token, "\n")] = 0;
		if (!strcmp(token, key_name))
			return i;
		token = strtok(NULL, CSV_DELIMITER);
	}
	return -1;
}

void print_file_contents(FILE *file) {
	char line[ROW_CHAR_LIMIT];
	
	// parse headings for index of key column
	fgets(line, ROW_CHAR_LIMIT, file);
	int key_column_index = find_key_index(line, KEY_COLUMN_NAME);
	printf("index of 'key' column: %d\n", key_column_index);
	if (key_column_index == -1) {
		printf(
			".csv file does not contain a '%s' column, exiting...\n",
			KEY_COLUMN_NAME
		);
		exit(1);
	}
	
	while( fgets(line,ROW_CHAR_LIMIT,file) ) {
		printf("%s", line);
	}
	return;
}


