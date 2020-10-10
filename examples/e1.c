#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <search.h>

typedef struct {
  uint8_t age;
  uint8_t count;
} stat_t;

typedef stat_t* stat_p;

static int compare_u3(const uint8_t a, const uint8_t b){
  switch(a == b){
    case true: return 0;
    default:   return a < b ? -1 : 1;
  }
}
static int compare_age(const uint8_t a, const uint8_t b){ return compare_u3(a >> 4, b >> 4); }

static int compare_stat(const void* pa, const void* pb){
  const stat_t* sa = pa;
  const stat_t* sb = pb;
  return compare_age(sa->age, sb->age);
}

static void on_tree(const void* nodep, VISIT which, int depth){
  const stat_p* datapp = nodep;
  const stat_t* datap  = *datapp;
  const uint8_t age = datap->age;
  const uint8_t lb = age & 0xf0;
  const uint8_t ub = lb + 16 - 1;

  switch(which){
    case preorder:  break;
    case endorder:  break;
    case postorder:
    case leaf:
      printf("age: %2d-%d, count: %d\n", lb, ub, datap->count);
      break;
    default: break;
  }
}

int main(int argc, char** argv){
  uint8_t age[] = {
    78, 68,
    42, 40, 36, 35,
    27, 18,
    1,
  };

  stat_t   search = {0};
  stat_t** found  = NULL;
  void*    tree   = NULL;
  stat_t*  insert = NULL;

  for(uint8_t i=0; i<sizeof(age); i++){
    search.age = age[i];
    found = tfind(&search, &tree, compare_stat);
    insert = NULL == found ? malloc(sizeof(stat_t)) : NULL;
    found = insert && NULL == found ? tsearch(insert, &tree, compare_stat) : found;
    switch(NULL == found){
      case true: continue;
      default:   break;
    }
    (*found)->age = search.age;
    (*found)->count++;
  }
  twalk(tree, on_tree);
  tdestroy(tree, free);
  return 0;
}
