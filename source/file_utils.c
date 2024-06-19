#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int is_directory(const char *path) {
	struct stat statbuf;
	if ( stat(path, &statbuf) != 0 ) {
		return 0;
	}
	return S_ISDIR(statbuf.st_mode);
}

/*
`build_clone_path` takes the name of the file located at `file_path`,
and appends it to the `new_dir_path` delimited by a '/', stored in `new_path`.
The caller is responsible for allocating sufficient memory to `new_path`

Input:  A char pointer to hold the new string `new_path`,
	the path to find the original `file_path`,
	the path of the new directory `new_dir_path`
Output: nothing
*/
void build_clone_path(char* new_path, char* file_path, char* new_dir_path) {
	char *token = strrchr(file_path, '/') + 1;
	strcpy(new_path, new_dir_path);
	strcat(new_path, "/");
	strcat(new_path, token);
	return;
}

/*
`copy_file` copies a file specified by `file_path` into the directory path `output_path`

Input:  The path to the target file `file_path`, 
	the path to the target directory `output_path`
Output: nothing TODO: implement error checking and return values for this function
*/
void copy_file(char* file_path, char* output_path) {
	// build new path for clone file
	int clone_file_path_length = strlen(file_path) + 1 + strlen(output_path) + 1;
	char *clone_path = (char*)malloc(clone_file_path_length * sizeof(char));
	build_clone_path(clone_path, file_path, output_path);

	// open file streams
	FILE *original_file, *clone_file;
	original_file = fopen(file_path, "rb");
	clone_file = fopen(clone_path, "ab");
	
	if (clone_file == NULL || original_file == NULL) {
		printf(
			"failed to read %s into new file: %s,\nexiting...\n",
			file_path,
			clone_path
		);
		return;
	}
	
	// copy file contents
	int buffer;
	while ( (buffer = fgetc(original_file)) != EOF ) {
		fprintf(clone_file, "%c", buffer);
	}

	fclose(original_file);
	fclose(clone_file);
	free(clone_path);
	return;
}
