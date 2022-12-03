#include <stdio.h>
#include <stdlib.h>

#include "helpers/include/menu.h"
#include "helpers/include/input.h"


#include "include/day1.h"
#include "include/day2.h"
#include "include/day3.h"

char* solve(char** input_arr, int day, int part, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  switch (day) {
    case 1:
      if (part == 1)
        solution = day1_part1(input_arr, m, n);
      else
        solution = day1_part2(input_arr, m, n);
      break;
    case 2:
      if (part == 1)
        solution = day2_part1(input_arr, m, n);
      else
        solution = day2_part2(input_arr, m, n);
      break;
    case 3:
      if (part == 1)
        solution = day3_part1(input_arr, m, n);
      else
        solution = day3_part2(input_arr, m, n);
      break;
    
  }

  return solution;
}

int main(int argc, char** argv) {
  int day_and_part, day, part, n, m;
  char* input_filepath;
  char* solution;
  char** input_arr;

  menu_init();

  if ((day_and_part = menu_getinput()) == -1) 
    return -1;
  day = day_and_part/10;
  part = day_and_part%10;

  input_filepath = menu_inputpath(day_and_part);
  if (!input_filepath) {
    printf("Check if input file exists");
    return -1;
  }
  get_needed_size(input_filepath,&n,&m);
  input_arr = create_array(&n, &m);
  file_to_array(input_filepath, input_arr);

  solution = solve(input_arr, day, part, m, n);

  printf("Solution is: %s\n", solution);

  free_array(input_arr, m);
  free(input_filepath);
  free(solution);
  return 0;
}
