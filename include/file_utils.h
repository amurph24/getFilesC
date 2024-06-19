#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int is_directory(const char *path);
void build_clone_path(char* new_path, char* file_path, char* new_dir_path);
void copy_file(char* file_path, char* output_path);

#endif
