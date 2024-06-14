#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW_CHAR_LIMIT 1024

void printFileContents(FILE *file) {
	char line[ROW_CHAR_LIMIT];
	while(fgets(line,ROW_CHAR_LIMIT,file)) {
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
