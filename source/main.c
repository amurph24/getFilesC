#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define ROW_CHAR_LIMIT 1024
#define KEY_COLUMN_NAME "key"
#define CSV_DELIMITER ","
#define MAX_DEPTH 10

int findKeyIndex(char *line, char *keyname){
	char *token;
	token = strtok(line, CSV_DELIMITER);
	for(int i = 0; token; i++) {
		// newline char disrupts check on last column header
		token[strcspn( token, "\n")] = 0;
		if (!strcmp(token, keyname))
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

int recursive_search(char *path, char *key, int depth) {
	// validate path
	if (access(path, F_OK)) {
		printf("'%s' cannot be accessed\n", path);
		return 1;
	}
	
	DIR *dir = opendir(path);

	// path is a file
	if (!dir) {
		printf("%s\n", path);	
		return 0;
	}
	
	// path is a directory
	if (depth >= MAX_DEPTH)
		printf("'%s' exceeds max depth %d, cancelling search", path, MAX_DEPTH);

	char childPath[1024];
	char *selfDir = ".", *parentDir = "..";
	char slash = '/';

	struct dirent *dirChild;
	
	printf("%s\n", path);
	while ((dirChild = readdir(dir)) != NULL) {
		
		if ( !strcmp(dirChild->d_name, selfDir) ) continue;
		if ( !strcmp(dirChild->d_name, parentDir) ) continue;

		// get new path for recursive call	
		strcpy(childPath, path);
		strncat(childPath, &slash, 1);
		strcat(childPath, dirChild->d_name);

		//recursion
		recursive_search(childPath, key, depth + 1);
	}

	closedir(dir);
	return 0;
}


int getFiles(int argc, char *argv[]) {
	printf("Printing contents of: %s\n", argv[1]);

	FILE *file = fopen(argv[1], "r");
	printFileContents(file);
	fclose(file);

	recursive_search(".", "key", 0);

	printf("%d args\n", argc);
	return 0;
}

int main(int argc, char *argv[]){
	getFiles(argc, argv);
	return 0;
}
