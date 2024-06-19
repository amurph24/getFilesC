#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>

#define MAX_DEPTH 10
#define SELF_DIRECTORY "."
#define PARENT_DIRECTORY ".."

/*
This function compares a regex string to an input string

input: regex and a string to check
output: 0 if a match is found, 1 if not
*/
int compare_regex(char* regex_string, char *string) {
	regex_t regex;
	regcomp(&regex, regex_string, 0);
	return regexec(&regex, string, 0, NULL, 0);
}

/*
recursive_search_helper is a helper for recursive_search,
it is recursively called to search for the key up to a max depth of MAX_DEPTH.

Input: a path to search for the regex key, and the depth of the current search.
Output: 0 if the function executes correctly, 1 if an error is encountered.
*/

int recursive_search_helper(char *path, char *key, int (*func)(char*), int depth) {
	// validate path
	if (access(path, F_OK)) {
		printf("%s cannot be accessed\n", path);
		return 1;
	}
	
	if ( !compare_regex(key, path) ) {
		(*func)(path);
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
		recursive_search_helper(child_path, key, func, depth + 1);

		free(child_path);
	}

	closedir(dir);
	return 0;
}

/*
recursive_search traverses a directory recursively,
searching for regex matches to a given key.

Input: a directory (path) to search, and a regex key to match file or directory paths.
Output: 0 if the function succesfully compares at least one file, 1 otherwise.

*/
int recursive_search(char *path, char *key, int (*func)(char*)) {
	return recursive_search_helper(path, key, func, 0);
}

