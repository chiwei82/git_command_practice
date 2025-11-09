#pragma once

#define BOARDS_MAX 100000
#define BOARD_H 4
#define BOARD_W 5
#define PAIRED -1
#define PAIRED_SUM 10
#define EIGHT_DIRS 8
#define DIMENSION 2

/* Put other #includes here,
   your struct board, helper function
   prototypes etc.
*/
struct board {
   int mat[BOARD_H][BOARD_W];
};
typedef struct board board;

struct boards {
   board b_arr[BOARDS_MAX];
   long f;
   long end;
};
typedef struct boards boards;

struct eight_dirs {
   int j[EIGHT_DIRS];
   int i[EIGHT_DIRS];
};
typedef struct eight_dirs eight_dirs;

struct position_list {
   int pos_list[EIGHT_DIRS][DIMENSION];
   int count;
};
typedef struct position_list position_list;

int abs_val(int x);
bool inbound(int j, int i);
bool checkLinear(pair z);
bool checkNoBetween(board* p, pair z);
bool checkStraight(board* p, pair z);
bool checkTouching(pair z);
bool checkUnique(boards *head, board *new_board);
void board_copy(board *old_board, board *new_board);
void take_and_cpy(boards *head, board *mb, int j, int i);
eight_dirs dir_init(void);
