#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER_NUM 4
#define BOARD_NUM 60

#define TRUE 1
#define FALSE 0

#define NAME_SIZE 16
#define EVE_SIZE 64
#define BOARD_STATUS_NUM 6

#define PL_ACTIVE 0
#define PL_GOAL 1
#define INIT_POINT 10

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
  struct player *p_next;
  struct board *b_next;
}PLAYER;

void init(PLAYER *player, BOARD *board);
int load_board(BOARD *board);
void init_player(PLAYER *player);
int decide_turn(PLAYER *player);
void turn(PLAYER *player, BOARD *board);
void calc_point(PLAYER *player, int real_p, int study_p);

int main(void)
{
  PLAYER player[PLAYER_NUM];
  BOARD board[BOARD_NUM];

  init(player, board);
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
  }else{
    puts("get file!");
  }

  for(i = 0;i < BOARD_NUM ; i++) {
    board[i].id = i;
    fgets(tmp_str, EVE_SIZE, fp);
    strcpy(board[i].name, tmp_str);
    fgets(tmp_str, EVE_SIZE, fp);
    strcpy(board[i].about, tmp_str);
    fgets(tmp_str, EVE_SIZE, fp);
    board[i].real_p = atoi(tmp_str);
    fgets(tmp_str, EVE_SIZE, fp);
    board[i].study_p = atoi(tmp_str);
    fgets(tmp_str, EVE_SIZE,fp);
    printf("id:%d\nname:%sabout:%sreal_p:%d\nstudy_p:%d\n\n",board[i].id, board[i].name, board[i].about, board[i].real_p, board[i].study_p);
  }
}

void init_player(PLAYER *player)
{
  int i;
  char tmp_str[64];
  for(i = 0; i < PLAYER_NUM; i++) {
    player[i].id = i;
    printf("input your name: ");
    scanf("%s",tmp_str);
    strcpy(player[i].name, tmp_str);
    player[i].real_p = INIT_POINT;
    player[i].study_p = INIT_POINT;
    player[i].pl_sta = PL_ACTIVE;
  }
}

int decide_turn(PLAYER *player)
{
  for(i = 0; i <PLAYER_NUM; i++) {
    
  }
}
void turn(PLAYER *player, BOARD *board)
{
}
void calc_point(PLAYER *player, int real_p, int study_p)
{
}
