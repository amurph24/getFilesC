#include <stdio.h>
#include "file_utils.h"
#include "recursive_search.h"

#define OUTPUT_DIR "out"

int validate_args(int argc,char *argv[]) {
	//TODO: validate args
	return 0;
}

int custom_copy_file(char *file_path) {
	char *output_dir = OUTPUT_DIR;
	copy_file(file_path, output_dir);
	return 0;
}

int get_files(int argc, char *argv[]) {
	if ( !mkdir_or_exists(OUTPUT_DIR) ) {
		printf("exiting...\n");
		return 1;
	}
	if (validate_args(argc, argv)) return 1;
	return recursive_search(".", argv[1], custom_copy_file);
}

