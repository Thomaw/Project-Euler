#include <stdio.h>

typedef unsigned int uint;

typedef enum {GRAY, RED, ORANGE} color;

struct point {
  uint price;
  uint cost;
  color state;
};

const uint SIZE = 80;

void set_point_state(struct point *prev, struct point *curr) {
  uint pres_cost = prev->cost + curr->price;
  switch(curr->state) {
  case GRAY:
    curr->cost = pres_cost;
    curr->state = RED;
    break;
  case RED:
    if(curr->cost > pres_cost)
      curr->cost = pres_cost;
    break;
  }
}

int main() {
  struct point mat[SIZE][SIZE];
  uint i,j,min_i,min_j,min_weight,max_weight,found_to_orange;
  max_weight = 0;
  for(i = 0; i < SIZE; i++) {
    for(j = 0; j < SIZE; j++) {
      if(j == SIZE - 1)
        scanf("%d",&(mat[i][j].price));
      else
        scanf("%d,",&(mat[i][j].price));
      mat[i][j].state = GRAY;
      max_weight += mat[i][j].price;
    }
    mat[i][0].state = ORANGE;
    mat[i][0].cost = mat[i][0].price;
  }
  found_to_orange = 1;
  while(found_to_orange) {
    for(i = 0; i < SIZE; i++)
      for(j = 0; j < SIZE; j++)
        if(mat[i][j].state == ORANGE) {
          if(i > 0)
            set_point_state(&mat[i][j], &mat[i - 1][j]);
          if(i < SIZE - 1)
            set_point_state(&mat[i][j], &mat[i + 1][j]);
          if(j < SIZE - 1)
            set_point_state(&mat[i][j], &mat[i][j + 1]);
        }
    min_weight = max_weight;
    found_to_orange = 0;
    for(i = 0; i < SIZE; i++)
      for(j = 0; j < SIZE; j++)
        if(mat[i][j].state == RED && mat[i][j].cost < min_weight) {
          min_i = i;
          min_j = j;
          min_weight = mat[i][j].cost;
          found_to_orange = 1;
        }
    if(found_to_orange)
      mat[min_i][min_j].state = ORANGE;
  }

  min_weight = mat[0][SIZE - 1].cost;
  for(i = 1; i < SIZE; i++)
    if(min_weight > mat[i][SIZE - 1].cost)
      min_weight = mat[i][SIZE - 1].cost;

  printf("%d\n",min_weight);
  return 0;
}