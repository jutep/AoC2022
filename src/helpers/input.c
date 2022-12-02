#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/input.h"

void get_needed_size(char* input_path, int* n, int* m) {
  FILE *fp;
  if (!(fp = fopen(input_path, "r"))) {
    printf("file does not exist\n");
    exit(EXIT_FAILURE);
  }

  char* line;
  size_t len = 0;
  ssize_t read;
  ssize_t max_line = 0;
  int cnt = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    if (read > max_line)
      max_line = read;
    cnt++;
  }

  *m = cnt;
  *n = (int) max_line;

  fclose(fp);
  if (line) 
    free(line);
}

void file_to_array(void* input_path, char** input_arr) {
  char* line;
  size_t len = 0;
  ssize_t read;
  int cnt = 0;

  FILE *fp;
  fp = fopen(input_path, "r"); 
  while ((read = getline(&line, &len, fp)) != -1) {
    char* field = input_arr[cnt];
    strcpy(field, line);
    printf("%s", field);
    cnt++;
  }
}


char** create_array(int *n, int *m) {
  char** input_arr = (char**)malloc((1+*m)*sizeof(char*));

  for (int i = 0; i < (*m+1); i++) {
    input_arr[i] = (char*)malloc((sizeof(char)*(*n+1)));
  }
  return input_arr;
}

void free_array(char** input_arr, int m) {
  for (int i = 0; i<m;i++)
    free(input_arr[i]);
  free(input_arr);
}
