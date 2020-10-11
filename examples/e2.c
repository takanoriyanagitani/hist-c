#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <time.h>

#include <search.h>

int compare_i4(const void* pa, const void* pb){
  const int32_t* a = pa;
  const int32_t* b = pb;
  switch(*a == *b){
    case true: return 0;
    default:   return *a < *b ? -1 : 1;
  }
}

int main(int argc, char** argv){
  void* tree = NULL;

  const int32_t imax = 1 << 26;
  int32_t r = 0;

  int32_t** found  = NULL;
  int32_t*  insert = NULL;
  int32_t   search = 0;

  printf("%ld\n", time(NULL));
  for(int32_t i=0; i<imax; i++){
    r = random();
    search = r;
    found = tfind(&search, &tree, compare_i4);
    insert = NULL == found ? malloc(sizeof(int32_t)) : NULL;
    found = insert && NULL == found ? tsearch(insert, &tree, compare_i4) : found;
    switch(NULL == found){
      case true: continue;
      default:   break;
    }
    **found = r;
  }
  printf("%ld\n", time(NULL));
  tdestroy(tree, free);
  printf("%ld\n", time(NULL));

  return 0;
}
