#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYER_NUM 4
#define BOARD_NUM 60

#define TRUE 1
#define FALSE 0
#define ERROR -1

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
}BOARD;

typedef struct player{
  int id;
  char name[NAME_SIZE];
  int dice;
  int real_p;
  int study_p;
  int pl_sta;
  int pl_num;
  int board_cnt;
  struct player *p_next;
}PLAYER;

void init(PLAYER *player, BOARD *board);
int load_board(BOARD *board);
void init_player(PLAYER *player);
PLAYER *decide_turn(PLAYER *player);
void turn(PLAYER *player, BOARD *board);
void calc_point(PLAYER *player, int real_p, int study_p);
void print_board_info(BOARD info_board);

int main(void)
{
  srand((unsigned)time(NULL));

  PLAYER player[PLAYER_NUM];
  PLAYER *p_head;
  BOARD board[BOARD_NUM];

  init(player, board);
  p_head = decide_turn(player);
  turn(p_head, board);
  return 0;
}

void init(PLAYER *player, BOARD *board)
{
  if(load_board(board) == ERROR)
    exit(0);
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

  return 0;
}

void init_player(PLAYER *player)
{
  int i;
  char tmp_str[64];
  char dummy;
  for(i = 0; i < PLAYER_NUM; i++) {
    player[i].id = i;
    printf("[Player%d]input your name: ", i+1);
    scanf("%s",tmp_str);
    scanf("%c",&dummy);
    strcpy(player[i].name, tmp_str);
    player[i].real_p = INIT_POINT;
    player[i].study_p = INIT_POINT;
    player[i].pl_sta = PL_ACTIVE;
    player[i].board_cnt = -1;
  }
}

PLAYER *decide_turn(PLAYER *player)
{
  int i,j;
  int tmp;
  char dummy;
  int dice[PLAYER_NUM];
  int turn[PLAYER_NUM];
  for(i = 0; i< PLAYER_NUM;i++) turn[i] = i;
  for(i = 0; i <PLAYER_NUM; i++) {
    printf("[%s] Please press enter",player[i].name);
    scanf("%c",&dummy);
    dice[i] = rand() % 6 + 1;
    printf("%d\n", dice[i]);
  }
  for (i = 0; i < PLAYER_NUM - 1; i++) {
    for (j = PLAYER_NUM - 1; j > i; j--) {
      if (dice[j - 1] < dice[j]) {
        tmp = dice[j];
        dice[j] = dice[j - 1];
        dice[j - 1]= tmp;
        tmp = turn[j];
        turn[j] = turn[j-1];
        turn[j-1] = tmp;
      }
    }
  }

  for(i = 0; i < PLAYER_NUM; i++) {
    printf("%d,%d\n",turn[i],dice[i]);
  }
  for(i = 0; i < PLAYER_NUM; i++){
    if(i != PLAYER_NUM-1){
      player[turn[i]].p_next = &player[turn[i+1]];
    }else{
      player[turn[i]].p_next = &player[turn[0]];
    }
  }

  return &player[turn[0]];
}

void turn(PLAYER *player, BOARD *board)
{
  int flg_cnt = 0;
  char dummy;
  while(flg_cnt != PLAYER_NUM) {
    if(player->pl_sta != PL_GOAL){
      printf("[%s]のターン\n",player->name);
      printf("sta-> リア充P:%d, 勉学P:%d\n", player->real_p, player->study_p);
      printf("[%s] Please type Enter",player->name);
      scanf("%c",&dummy);
      player->dice = rand()%6+1;
      player->board_cnt += player->dice;
      if(player->board_cnt >= BOARD_NUM) {
        printf("[%s]ゴール！\n",player->name);
        player->pl_sta = PL_GOAL;
        flg_cnt++;
      }else{
        print_board_info(board[player->board_cnt]);
        calc_point(player, board[player->board_cnt].real_p, board[player->board_cnt].study_p);
      }
    }
    player = player->p_next;
  }
}
void calc_point(PLAYER *player, int real_p, int study_p)
{
  player->real_p += real_p;
  player->study_p += study_p;
}

void print_board_info(BOARD info_board)
{
  printf("%s\n", info_board.name);
  printf("%s\n", info_board.about);
}
