#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define NAME_SIZE 16
#define EVE_SIZE 64
#define BOARD_STATUS_NUM 6

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

void init(PLAYER *player, BOARD * board);
int load_board(BOARD *board);
void init_player(PLAYER *player);

int main(void)
{
  return 0;
}

void init(PLAYER *player, BOARD *board)
{
  load_board(board);
  init_player(player);
}
int load_board(BOARD *board)
{
  FILE *fp;
  char *fname = "board.dat";
  char tmp_str[EVE_SIZE];
  int i;

  fp = fopen( fname, "r" );
  if( fp == NULL ){
    printf( "can't open %s\n", fname );
    return -1;
  }

  for(i = 0; ; i++) {
  }
}

void init_player(PLAYER *player);
