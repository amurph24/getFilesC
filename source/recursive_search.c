#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_DEPTH 10


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
		recursive_search_helper(childPath, key, depth + 1);
	}

	closedir(dir);
	return 0;
}

int recursive_search(char *path, char *key) {
	return recursive_search_helper(path, key, 0);
}

