#pragma once

#define BOARDS_MAX 100000
#define BOARD_H 4
#define BOARD_W 5
#define PAIRED -1
#define PAIRED_SUM 10
#define EIGHT_DIRS 8
#define DIMENSION 2
#define MAX_CACHE 100000

/* Put other #includes here,
   your struct board, helper function
   prototypes etc.
*/
struct board {
   int mat[BOARD_H][BOARD_W];
   int depth;
};
typedef struct board board;

struct boards {
   board b_arr[BOARDS_MAX];
   long f;   // where mother board is
   long end; // where child board can be inserted
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

typedef unsigned long ul;

int abs_val(int x);
bool inbound(int j, int i);
bool checkLinear(pair z);
bool checkNoBetween(board* p, pair z);
bool checkStraight(board* p, pair z);
bool checkTouching(pair z);
bool take_check(board* p, pair z);
bool dfs(board *p, ul cache[], int *cache_count);
bool seen_before(ul h, ul visited[], int visited_count);
void add_seen(ul h, ul visited[], int *visited_count);
ul hash_board(const board *p);
eight_dirs dir_init(void);
position_list find_pos(board *b, int j, int i);
