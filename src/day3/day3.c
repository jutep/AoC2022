#include <stdio.h>
#include <stdlib.h>

#include "../include/day3.h"

// a-z: priority 1-26
// A-Z: priority 27-52
int item_priority(char item) {
  if (item >= 97 && item <=122)
    return item - 96;
  else 
    return (item - 64) + 26;
}

int line_length(char* line) {
  int cnt = 0;
  while (line[cnt] != '\n' && line[cnt] != '\0') {
    cnt++;
  }
  return cnt;
}

// assumption: (#items_compart1 + #items_compart2) % 2 == 0
char** split_into_compartments(char* line, char** compartments) {
  int ll = line_length(line);

  for (int i = 0; i < ll; i++) {
    if (i < (ll/2)) {
      compartments[0][i] = line[i];
    } else {
      compartments[1][i-(ll/2)] = line[i];
    }
  }
  // null terminating strings
  compartments[0][ll/2] = '\0';
  compartments[1][ll/2] = '\0';
  return compartments;
}

// O(n^2) not soo good
char* selection_sort(char* comp) {
  int ll = line_length(comp);
  int cnt = 0;
  int min, ind;
  // iterate over the compartments string
  while (cnt < (ll-1)) {
    min = item_priority(comp[cnt]);
    ind = cnt;
    // find smallest item
    for (int i = cnt+1; i < (ll); i++) {
      if (item_priority(comp[i]) < min) {
        min = item_priority(comp[i]);
        ind = i;
      }
    }
    // switch current item with smallest 
    if (ind != cnt) {
      char tmp = comp[cnt];
      comp[cnt] = comp[ind];
      comp[ind] = tmp;
    }
    // continue with next index
    cnt++;
  }
  return comp;
}

// in future we can change to a better sort algo
void sort_compartments(char* comp1, char* comp2) {
  selection_sort(comp1);
  selection_sort(comp2);
}

char* sort_rucksack(char* rucksack) {
  return selection_sort(rucksack);
}

int itemtype_inspected(char itemtype, int* already_seen, int n) {
  if (already_seen) {
    int notseen = 1;
    for (int i = 0; i < n; i++) {
      if (already_seen[i] == itemtype) {
        notseen = 0;
        break;
      } 
      if (already_seen[i] == -1) 
        break;
    }
    if (notseen) 
      return itemtype;
    else 
      return 0;
  } else 
    return itemtype;
}

char find_overlapping_itemtype(char* comp1, char* comp2, int* already_seen, int n) {
  int ll1 = line_length(comp1);
  int ll2 = line_length(comp2);
  int ind1, ind2 = 0;

  // iterate over the compartments/ rucksacks
  while (ind1 < ll1 && ind2 < ll2) {
    if (comp1[ind1] == comp2[ind2]) {
      // check if we have already checked with third rucksack in
      // previous call of the function
      if (itemtype_inspected(comp1[ind1], already_seen, n))
        return comp1[ind1]; 
      else {
        // if already seen the itemtype skip it and look for next on 
        ind1++;
        ind2++;
      }
    }
    else {
      if (item_priority(comp1[ind1]) < item_priority(comp2[ind2])) 
        ind1++;
      else
        ind2++;
    }
  }

  return 0;
}

// assumption: input is good, every rucksack has an item type
// that is in both comparts
char* day3_part1(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0;

  char** compart = malloc(sizeof(char*)*2);
  compart[0] = malloc(sizeof(char)*1024);
  compart[1] = malloc(sizeof(char)*1024);

  // for each line split into compartments, sort, iterate over
  for (int i = 0; i < m-1; i++) {
    split_into_compartments(input_arr[i], compart);
    sort_compartments(compart[0], compart[1]);
    sum += item_priority(find_overlapping_itemtype(compart[0], 
                                                   compart[1], 
                                                   NULL, 0));
  }

  free(compart[0]);
  free(compart[1]);
  free(compart);

  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}

// to not have any values in the allocated memory that 
// have the same priority as any number
void fill_with_shit(int* already_seen, int n) {
  for (int i = 0; i < n; i++) {
    already_seen[i] = -1;
  }
}

char* day3_part2(char** input_arr, int m, int n) {
  char* solution = malloc(sizeof(char)*1024);
  int sum = 0; 

  // assume not more than 50 overlapping items
  int* already_seen = malloc(sizeof(int)*50);
  char* r1 = malloc(sizeof(char)*n);
  char* r2 = malloc(sizeof(char)*n);
  char* r3 = malloc(sizeof(char)*n);
  int ptr, found;
  char item;
  
  // take group of three elves, find common item for the first two
  // search if third one has it, if not add to list of allready 
  // inspected itemtypes and look for next itemtype in the first two
  // rucksacks
  for (int i=0; i < m-1; i+=3) {
    // initialize clean for new group of three rucksack
    ptr = 0;
    found = 0;
    fill_with_shit(already_seen, 50);

    r1 = sort_rucksack(input_arr[i]);
    r2 = sort_rucksack(input_arr[i+1]);
    r3 = sort_rucksack(input_arr[i+2]);

    // assumption we will find a type
    item = '0';
    while (!found) {
      item = find_overlapping_itemtype(r1, r2, already_seen, 50);
      for (int i = 0; i < line_length(r3); i++) {
        if (r3[i] == item) {
          found = 1;
          sum += item_priority(item);
          break;
        }
      }
      already_seen[ptr] = item;
      ptr++;
    }
  }

  free(already_seen);
  // I have no idea why this is double free, when I never free it before
  //free(r1);
  //free(r2);
  //free(r3);
  // build solution
  sprintf(solution, "%d", sum);
  return solution;
}
