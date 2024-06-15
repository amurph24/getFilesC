#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "recursive_search.h"
#include "read_data.h"

int get_files(int argc, char *argv[]) {
	printf("Printing contents of: %s\n", argv[1]);

	FILE *file = fopen(argv[1], "r");
	print_file_contents(file);
	fclose(file);

	recursive_search(".", "key");

	printf("%d args\n", argc);
	return 0;
}

int main(int argc, char *argv[]){
	get_files(argc, argv);
	return 0;
}
