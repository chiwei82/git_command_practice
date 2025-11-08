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
   board arr_val[BOARDS_MAX];
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

bool inbound(int j, int i);
bool checkLinear(pair z);
bool checkNoBetween(board* p, pair z);
bool checkStraight(board* p, pair z);
bool checkTouching(pair z);
bool checkUnique(boards *main_board, board new_board);
int abs_val(int x);
void board_copy(boards *main_board_head, board new_board);
eight_dirs dir_init(void);
position_list get_candinate(board *b, int j, int i);
board board_init(board *old_board, pair z);
