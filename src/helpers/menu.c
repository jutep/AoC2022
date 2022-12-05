#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/menu.h"

void menu_init() {
  printf("Welcome to AoC2022 solutions\n\n");
  printf("**** First Select the day and puzzle you want to get the solution to ****\n");
  printf("(11) day1 puzzle1\n");
  printf("(12) day1 puzzle2\n");
  printf("(21) day2 puzzle1\n");
  printf("(22) day2 puzzle2\n");
  printf("(31) day3 puzzle1\n");
  printf("(32) day3 puzzle2\n");
  printf("(41) day4 puzzle1\n");
  printf("(42) day4 puzzle2\n");
  printf("(51) day5 puzzle1\n");
  printf("(52) day5 puzzle2\n\n");
}

/*
 * Get the user input, create filepath to lib/input_day[x]_puzzle[x].txt
 * and return it.
 */
int menu_getinput() {
  char input[3] = "";
  int day_and_puzzle;

  printf("Choose an item: ");
  // look if we have a correct input
  if (fgets(input, 3, stdin) != NULL) {
    // convert to integer
    day_and_puzzle = atol(input);
  } else {
    printf("Wrong input\n");
    return -1;
  }
  // check existance of puzzle solution
  if (day_and_puzzle == 11 
      || day_and_puzzle == 12
      || day_and_puzzle == 21
      || day_and_puzzle == 22
      || day_and_puzzle == 31
      || day_and_puzzle == 32
      || day_and_puzzle == 41
      || day_and_puzzle == 42
      || day_and_puzzle == 51
      || day_and_puzzle == 52
      ) { return day_and_puzzle; }

  printf("puzzle does not exist!\n");
  return -1;
}

// param: base_dir is a string, that gets overwritten with the current
// working dir
// return pointer to string with the base project directory
// on error NULL
char * base_project_path(char * base_path) {
  if (getcwd(base_path, (sizeof(char)*1024)) == NULL) 
    return NULL;
  
  // CARE: Implicit assumption, that someone does not have 
  // AoC2022/.../AoC2022/ in their path
  char search_for[9] = "AoC2022";
  int cnt = 0;
  int path_end = 0;

  // loop finds absolute path until project base dir with AoC2022/
  for (int i = 0; i < 1024; i++) {
    if (*(base_path+i) == '\0') 
      return NULL;
    if ( (char)*(base_path+i) == search_for[cnt]) {
      cnt += 1;
      // found the AoC2022 substring
      if (cnt == 7) {
        path_end = i;
        break;
      }
    } else {
      cnt = 0;
    }
  }

  // pointer to last character / of the project dir path + 1 to get the
  // pointer to the terminating character
  char * end = base_path + path_end + 1;
  // overwrite whatever is there with terminating character
  *end = '\0';

  // now we should have base_dir_path
  return base_path;
}

// we know that input day and puzzle should exist in theory
char* menu_inputpath(int input_puzzle) {
  char * input_path;
  if ((input_path = malloc(sizeof(char)*1024))== NULL) {
    free(input_path);
    return NULL;
  }
  char * base_path;
  if ((base_path= malloc(sizeof(char)*1024))== NULL) {
    free(input_path);
    free(base_path);
    return NULL;
  }

  if (base_project_path(base_path) == NULL) {
    free(input_path);
    free(base_path);
    return NULL;
  }

  char rel_input_path[30];

  int day = input_puzzle / 10;

  if ((sprintf(rel_input_path, "/lib/input_day%d.txt", day)) < 0) {
    free(input_path);
    free(base_path);
    return NULL;
  }

  // build full path
  strcpy(input_path, base_path);
  strcat(input_path, rel_input_path);

  free(base_path);
  
  return input_path;
}

