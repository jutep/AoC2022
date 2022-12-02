#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day1.h"

int* top_three_snack_elves(char** input_arr, int m, int n) {
  char* line = (char*) malloc ((n+1)*sizeof(char));
  int cnt = 0;
  int* max= malloc(sizeof(int)*3);
  max[0] = -1;
  max[1] = -1;
  max[2] = -1;
  for (int i = 0; i < m; i++) {
    line = input_arr[i];
    // this is how we find a new group, group has \n\n
    if (!strcmp("\n", line)) {
        cnt = 0;
    } else {
      int val = atoi(line);
      cnt += val;
      if (max[0] < cnt) {
        max[2] = max[1];
        max[1] = max[0];
        max[0] = cnt;
      }else if (max[1] < cnt) {
        max[2] = max[1];
        max[1] = cnt;
      } else if (max[2] < cnt)
        max[2] = cnt;
    }
  }
  return max;
}

char* day1_part1(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int* max = malloc(3);
  max = top_three_snack_elves(input_arr, m, n);
  // build solution
  sprintf(solution, "%d", max[0]);
  free(max);
  return solution;
}

char* day1_part2(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int* max = malloc(3);
  max = top_three_snack_elves(input_arr, m, n);
  // build solution
  sprintf(solution, "%d", max[0]+max[1]+max[2]);
  free(max);
  return solution;
}

