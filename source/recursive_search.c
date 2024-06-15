#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>

#define MAX_DEPTH 10
#define SELF_DIRECTORY "."
#define PARENT_DIRECTORY ".."

int compare_regex(char* regex_string, char *string) {
	regex_t regex;
	regcomp(&regex, regex_string, 0);
	return regexec(&regex, string, 0, NULL, 0);
}

int recursive_search_helper(char *path, char *key, int depth) {
	// validate path
	if (access(path, F_OK)) {
		printf("%s cannot be accessed\n", path);
		return 1;
	}
	
	if ( !compare_regex(key, path) ) {
		printf("%s matches key %s\n", path, key);
		return 0;
	}


	DIR *dir = opendir(path);

	// path is a file
	if (!dir) {
		return 0;
	}

	// path is a directory
	if (depth >= MAX_DEPTH) {
		printf("'%s' exceeds max depth %d, cancelling search\n", path, MAX_DEPTH);
		closedir(dir);
		return 1;
	}

	char *child_path = NULL;
	int child_path_length;
	struct dirent *dir_child;
	
	while ((dir_child = readdir(dir)) != NULL) {
		
		if ( !strcmp(dir_child->d_name, SELF_DIRECTORY) ) continue;
		if ( !strcmp(dir_child->d_name, PARENT_DIRECTORY) ) continue;
	
		// resize child_path 
		child_path_length = strlen(path) + 1 + strlen(dir_child->d_name) + 1;
		child_path = (char*)malloc(child_path_length * sizeof(char));

		// get new path for recursive call
		strcpy(child_path, path);
		strcat(child_path, "/");
		strcat(child_path, dir_child->d_name);

		//recursion
		recursive_search_helper(child_path, key, depth + 1);

		free(child_path);
	}

	closedir(dir);
	return 0;
}

int recursive_search(char *path, char *key) {
	return recursive_search_helper(path, key, 0);
}

