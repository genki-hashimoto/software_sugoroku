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
#define DICE_MAX 6

#define EVE_NONE -1


typedef struct board{
  int id;
  char name[NAME_SIZE];
  char about[EVE_SIZE];
  int real_p;
  int study_p;
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

int throw_dice(int max);
void init(PLAYER *player, BOARD *board);
int load_board(BOARD *board);
void init_player(PLAYER *player);
PLAYER *decide_turn(PLAYER *player);
void turn(PLAYER *player, BOARD *board);
void calc_point(PLAYER *player, int real_p, int study_p);
void print_board_info(BOARD info_board);
void sort(int *array, int *p_num_array, int size);
void result(PLAYER *player);

int main(void)
{
  srand((unsigned)time(NULL));

  PLAYER player[PLAYER_NUM];
  PLAYER *p_head;
  BOARD board[BOARD_NUM];

  init(player, board);
  p_head = decide_turn(player);
  turn(p_head, board);

  result(player);
  return 0;
}

int throw_dice(int max)
{
  return rand() % max + 1;
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
    return ERROR;
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
  for(i = 0; i <PLAYER_NUM; i++) {
    printf("[%s] Please press enter",player[i].name);
    scanf("%c",&dummy);
    dice[i] = throw_dice(DICE_MAX);
    printf("%d\n", dice[i]);
  }

  sort(dice, turn, PLAYER_NUM);
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
      player->dice = throw_dice(DICE_MAX);
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

void sort(int *array, int *p_num_array, int size)
{
  int i,j;
  int tmp;

  for(i = 0; i< size;i++) p_num_array[i] = i;
  for (i = 0; i < PLAYER_NUM - 1; i++) {
    for (j = PLAYER_NUM - 1; j > i; j--) {
      if (array[j - 1] < array[j]) {
        tmp = array[j];
        array[j] = array[j - 1];
        array[j - 1]= tmp;
        tmp = p_num_array[j];
        p_num_array[j] = p_num_array[j-1];
        p_num_array[j-1] = tmp;
      }
    }
  }
}

void result(PLAYER *player) {
  int i = 0;
  int real_p[PLAYER_NUM], study_p[PLAYER_NUM],all_p[PLAYER_NUM];
  int real_ranking[PLAYER_NUM], study_ranking[PLAYER_NUM], all_ranking[PLAYER_NUM];

  for(i = 0; i < PLAYER_NUM; i++) {
    real_p[i] = player[i].real_p;
    study_p[i] = player[i].study_p;
    all_p[i] = real_p[i] + study_p[i];
  }
  sort(real_p, real_ranking, PLAYER_NUM);
  sort(study_p, study_ranking, PLAYER_NUM);
  sort(all_p, all_ranking, PLAYER_NUM);

  puts("リア充度ランキング");
  for(i = 0; i < PLAYER_NUM; i++) {
    printf("%d:%s, %dP\n",i+1, player[real_ranking[i]].name, player[real_ranking[i]].real_p);
  }
  puts("勉学励んだランキング");
  for(i = 0; i < PLAYER_NUM; i++) {
    printf("%d:%s, %dP\n",i+1, player[study_ranking[i]].name, player[study_ranking[i]].study_p);
  }
  puts("総合ランキング");
  for(i = 0; i < PLAYER_NUM; i++) {
    printf("%d:%s, %dP\n",i+1, player[all_ranking[i]].name, player[all_ranking[i]].real_p+player[all_ranking[i]].study_p);
  }

  puts("あなたの人生はどのような配分で進めていきますか？");
}
