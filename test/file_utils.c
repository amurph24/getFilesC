#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void build_clone_path(char* new_path, char* file_path, char* new_dir_path) {
	char *token = strrchr(file_path, '/') + 1;
	strcpy(new_path, new_dir_path);
	strcat(new_path, "/");
	strcat(new_path, token);
	return;
}

void copy_file(char* file_path, char* output_path) {
	// make space for clone file path
	int clone_file_path_length = strlen(file_path) + 1 + strlen(output_path) + 1;
	char *clone_path = (char*)malloc(clone_file_path_length * sizeof(char));
	build_clone_path(clone_path, file_path, output_path);

	FILE *original_file, *clone_file;
	original_file = fopen(file_path, "rb");
	clone_file = fopen(clone_path, "ab");
	
	if (clone_file == NULL || original_file == NULL) {
		printf("failed to read %s into new file: %s"
			"\n, exiting...\n", file_path, clone_path);
		return;
	}

	int buffer;
	while ( (buffer = fgetc(original_file)) != EOF ) {
		fprintf(clone_file, "%c", buffer);
	}

	fclose(original_file);
	fclose(clone_file);
	free(clone_path);
	return;
}

void main(int argc, char **argv) {
	copy_file(argv[1], argv[2]);
	return;
}
