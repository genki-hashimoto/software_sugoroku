#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 16
#define EVE_SIZE 64

#define PL_ACTIVE 0
#define PL_GOAL 1

#define EVE_NONE -1


typedef struct board{
  int id;
  char name[NAME_SIZE];
  char about[EVE_SIZE];
  int real_p;
  int study_p;
  int eve_sta;
  int eve_num;
  struct board *next;
}BOARD;

typedef struct player{
  int id;
  char name[NAME_SIZE];
  int dice;
  int real_p;
  int study_p;
  int pl_sta;
  int pl_num;
  struct player *next;
  struct board *next;
}PLAYER;

int main(void)
{
  return 0;
}
