#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int is_directory(const char *path) {
	struct stat statbuf;
	if ( stat(path, &statbuf) != 0 ) {
		return 0;
	}
	return S_ISDIR(statbuf.st_mode);
}

int mkdir_or_exists(char *output_dir) {
	if (!mkdir(output_dir, 00700))
		return 1; // dir was created
	// dir wasn't created
	if (is_directory(output_dir))
		return 1;
	printf(	"file exists with the name '%s',\n"
		"an output directory with the same name cannot be created\n",
		output_dir);
	return 0;
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
	FILE *original_file;
	original_file = fopen(file_path, "rb");
	if ( original_file == NULL ) {
		printf("failed to read %s, cannot copy\n", file_path);
		return;
	}

	int clone_file;
	clone_file = open(	clone_path,
				O_CREAT | O_WRONLY | O_EXCL | O_APPEND,
				S_IRUSR | S_IWUSR);
	if (clone_file < 0) {
		printf("%s already exists, won't copy %s\n", clone_path, file_path);
		fclose(original_file);
		return;
	}
	
	// copy file contents
	char buffer;
	char *char_buffer = NULL;
	while ( (buffer = fgetc(original_file)) != EOF ) {
		char_buffer = &buffer;
		write(clone_file, char_buffer, 1);
	}
	printf("%s succesfully copied\n", file_path);

	fclose(original_file);
	close(clone_file);
	free(clone_path);
	return;
}
