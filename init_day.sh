#!/bin/sh

workingdir="${PWD}"

# create dir and files
mkdir "$workingdir/src/day$1"
touch "$workingdir/src/day$1/day$1.c"
touch "$workingdir/src/include/day$1.h"
touch "$workingdir/lib/input_day$1.txt"

# add boilerplate to files
echo "
#include <stdio.h>
#include <stdlib.h>

#include \"../include/day4.h\"

char* day$1_part1(char** input_arr, int num_l, int l_size) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0; 

  // build solution
  sprintf(solution, \"%d\", sum);
  return solution;
}

char* day$1_part2(char** input_arr, int num_l, int l_size) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0; 

  // build solution
  sprintf(solution, \"%d\", sum);
  return solution;
}" >> "$workingdir/src/day$1/day$1.c"
echo "
#ifndef DAY$1_H
#define DAY$1_H

char* day$1_part1(char** input_arr, int num_l, int l_size);
char* day$1_part2(char** input_arr, int num_l, int l_size);

#endif /* DAY$1_H */" >> "$workingdir/src/include/day$1.h"
echo "#input from https://adventofcode.com/2022/day/$1\n 
#put into this file and remove this comment afterwards" >> "$workingdir/lib/input_day$1.txt"

# add input and change the needed lines to work
vim "$workingdir/lib/input_day$1.txt"
vim "$workingdir/src/main.c"
vim "$workingdir/src/helpers/menu.c"
