#ifndef INPUT_H
#define INPUT_H

void file_to_array(void* input_path, char** input_arr);
void get_needed_size(char* input_path, int* n, int* m);

char** create_array(int *n, int *m);
void free_array(char** input_arr, int m);

#endif
