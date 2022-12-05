
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day4.h"

char** build_ship_arr(char** ship_arr, char** input_arr) {
  
  // CARE: only works for this input data
  // we have tower size of 8 crates in the input data 
  
  char* line = malloc(sizeof(char) * 37);
  // for each line
  for (int i = 7; i >= 0; i--) {
    line = input_arr[i];
    // look if crate is on a stack and add it
    for (int j = 0; j < 9; j++) {
      char buffer[4];
      memcpy(buffer, &line[j*4], 3);
      buffer[3] = '\0';
      char crate;
      if (!(buffer[0] == ' ')) {
        sscanf(buffer, "[%c]", &crate);
        ship_arr[j][7-i] = crate;
        ship_arr[j][8-i] = '\0';
      }
    }
  }
  // WHY IS THIS A DOUBLE FREE????
  //free(line);

  return ship_arr;
}

void free_ship(char** ship) {
  for (int i =0; i < 9; i++) 
    free(ship[i]);
  free(ship);
}

char* day5_part1(char** input_arr, int num_l, int l_size) {
  char* solution = malloc(sizeof(char)*1024);
  // allocate ship
  char** ship = malloc(sizeof(char*)*9);
  for (int i = 0; i < 9; i++) {
    ship[i] = malloc(sizeof(char)*64);
  }
  // fill the ship arr
  build_ship_arr(ship, input_arr);

  // move the crates
  for (int i=10; i < num_l-1; i++) {
    int n_crates, s1, s2;
    sscanf(input_arr[i], "move %d from %d to %d", &n_crates, &s1, &s2);

    size_t l_s1 = strlen(ship[s1-1]);
    size_t l_s2 = strlen(ship[s2-1]);

    for (int i = 0; i < n_crates; i++) {
      char crate = ship[s1-1][l_s1-1];
      ship[s1-1][l_s1-1] = '\0'; // overwrite with null terminating byte
      ship[s2-1][l_s2] = crate;
      ship[s2-1][l_s2+1] = '\0';
      // change to according new stack size
      l_s1--;
      l_s2++;
    }
  }

  // build solution
  for (int i = 0; i < 9; i++) {
    size_t l = strlen(ship[i]);
    solution[i] = ship[i][l-1];
  }
  solution[9] = '\0';

  free_ship(ship);
  return solution;
}

char* day5_part2(char** input_arr, int num_l, int l_size) {
  char* solution = malloc(sizeof(char)*1024);
  // allocate ship
  char** ship = malloc(sizeof(char*)*9);
  for (int i = 0; i < 9; i++) {
    ship[i] = malloc(sizeof(char)*64);
  }
  // fill the ship arr
  build_ship_arr(ship, input_arr);

  // move the crates
  for (int i=10; i < num_l-1; i++) {
    int n_crates, s1, s2;
    sscanf(input_arr[i], "move %d from %d to %d", &n_crates, &s1, &s2);

    size_t l_s1 = strlen(ship[s1-1]);
    size_t l_s2 = strlen(ship[s2-1]);

    // only change to part one here!!!
    // go upwards in the string instead of backwards
    for (int i = n_crates; i > 0 ; i--) {
      char crate = ship[s1-1][l_s1-i];
      ship[s2-1][l_s2] = crate;
      ship[s2-1][l_s2+1] = '\0';
      // change to according new stack size
      l_s2++;
    }
    ship[s1-1][l_s1-n_crates] = '\0'; // overwrite with null terminating byte
  }

  // build solution
  for (int i = 0; i < 9; i++) {
    size_t l = strlen(ship[i]);
    solution[i] = ship[i][l-1];
  }
  solution[9] = '\0';

  free_ship(ship);
  return solution;
}
