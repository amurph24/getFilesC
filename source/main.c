#include <stdio.h>
#include "get_files.h"

int main(int argc, char *argv[]){
	if (argc != 2) {
		printf("usage: getFiles <regex>\n");
		return 1;
	}
	get_files(argc, argv);
	return 0;
}
