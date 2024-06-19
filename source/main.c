#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "recursive_search.h"
#include "read_data.h"
#include "file_utils.h"

int custom_copy_file(char *file_path) {
	char *output_dir = "test/out";
	copy_file(file_path, output_dir);
	return 0;
}

int get_files(int argc, char *argv[]) {
	//silences pedantic warnings, remove later
	printf("received %d args\n", argc);
	
	/*
	FILE *file = fopen(argv[1], "r");
	if ( file != NULL) {
		printf("Printing contents of: %s\n", argv[1]);
		print_file_contents(file);
		fclose(file);
	}
	else {
		printf("%s not found\n", argv[1]);
	}
	*/

	recursive_search(".", argv[1], custom_copy_file);
	//copy_file("test/names.csv", ".");
	return 0;
}

int main(int argc, char *argv[]){

	if (argc != 2) {
		printf("usage: getFiles <regex>\n");
		return 1;
	}
	get_files(argc, argv);
	return 0;
}
