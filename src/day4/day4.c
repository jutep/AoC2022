#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day4.h"

char* day4_part1(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0;

  for (int i = 0; i < m-1; i++) {
    int s1,e1,s2,e2;
    sscanf(input_arr[i], "%d-%d,%d-%d", &s1, &e1, &s2, &e2);
    if (   ((s1 >= s2) && (e1<= e2))
        || ((s1 <= s2) && (e1 >= e2)))
      sum++;
  }

  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}

char* day4_part2(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0; 
  
  for (int i = 0; i < m-1; i++) {
    int s1,e1,s2,e2;
    sscanf(input_arr[i], "%d-%d,%d-%d", &s1, &e1, &s2, &e2);
    if (   ((s1 >= s2) && (e1<= e2))
        || ((s1 <= s2) && (e1 >= e2)))
      sum++;
    //    s2 --- e2 
    // e1           s1   
    else if (!((e1 < s2) || (s1 > e2)))
      sum++;
  }

  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}
