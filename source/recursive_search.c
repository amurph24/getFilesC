#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_DEPTH 10
#define SELF_DIRECTORY "."
#define PARENT_DIRECTORY ".."

int recursive_search_helper(char *path, char *key, int depth) {
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
	if (depth >= MAX_DEPTH) {
		printf("'%s' exceeds max depth %d, cancelling search", path, MAX_DEPTH);
		closedir(dir);
		return 1;
	}

	char *childPath = NULL;
	int child_path_length;
	struct dirent *dirChild;
	
	printf("%s\n", path);
	while ((dirChild = readdir(dir)) != NULL) {
		
		if ( !strcmp(dirChild->d_name, SELF_DIRECTORY) ) continue;
		if ( !strcmp(dirChild->d_name, PARENT_DIRECTORY) ) continue;
	
		// resize childPath	
		child_path_length = strlen(path) + 1 + strlen(dirChild->d_name) + 1;
		childPath = (char*)malloc(child_path_length * sizeof(char));

		// get new path for recursive call
		strcpy(childPath, path);
		strcat(childPath, "/");
		strcat(childPath, dirChild->d_name);

		//recursion
		recursive_search_helper(childPath, key, depth + 1);

		free(childPath);
	}

	closedir(dir);
	return 0;
}

int recursive_search(char *path, char *key) {
	return recursive_search_helper(path, key, 0);
}

