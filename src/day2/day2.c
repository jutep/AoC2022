#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day2.h"

int eval_round(char* str) {
  int points = 0;

  // we have rock
  if (str[2]=='X') {
    points += 1;
    if (str[0] == 'A') // draw rock
      points +=3;
    else if (str[0] == 'C') // win sciccors
      points +=6;
  }
  // we have paper
  else if (str[2] == 'Y') {
    points += 2;
    if (str[0] == 'B') // draw paper
      points +=3;
    else if (str[0]=='A') // win rock
      points +=6;
  }
  // we have sciccors
  else if (str[2] == 'Z') {
    points += 3;
    if (str[0] == 'C') // draw sciccors
      points +=3;
    else if (str[0] == 'B') // win papaer
      points +=6;
  }

  return points;
}

char* day2_part1(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);

  int sum = 0;
  for (int i = 0; i < m; i++) {
    sum += eval_round(input_arr[i]);
  }

  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}

char* day2_part2(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  
  int sum = 0;
  
  for (int i = 0; i < m; i++) {
    // outcome should be
    char out = input_arr[i][2];
    char opponent_plays = input_arr[i][0];
    // we need to loose
    if (out == 'X') {
      switch (opponent_plays) {
        case 'A':
          input_arr[i][2] = 'Z';
          break;
        case 'B':
          input_arr[i][2] = 'X';
          break;
        case 'C':
          input_arr[i][2] = 'Y';
          break;
      }
    // we need to draw
    } else if (out == 'Y') {
      switch (opponent_plays) {
        case 'A':
          input_arr[i][2] = 'X';
          break;
        case 'B':
          input_arr[i][2] = 'Y';
          break;
        case 'C':
          input_arr[i][2] = 'Z';
          break;
      }
    // we need to loose
    } else {
      switch (opponent_plays) {
        case 'A':
          input_arr[i][2] = 'Y';
          break;
        case 'B':
          input_arr[i][2] = 'Z';
          break;
        case 'C':
          input_arr[i][2] = 'X';
          break;
      }
    }
    sum += eval_round(input_arr[i]);

  }

  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}
