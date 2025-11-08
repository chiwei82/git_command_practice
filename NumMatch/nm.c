#include "nm.h"

bool solve(int seed)
{
   boards main_board;
   boards *head = &main_board;
   board first_b = randfill(seed);

   // init first board
   main_board.f = 0;
   main_board.end = 1;
   main_board.arr_val[0] = first_b;
   // mother pointer points to first board
   do {
      // mother_board pointed to where f is
      board *mother_board = &main_board.arr_val[main_board.f];
      for (int j=0; j<BOARD_H; j++){
         for(int i=0; i<BOARD_W; i++){
            // loop and find possible num_2
            take_and_cpy(head, mother_board, j, i);
         }
      }
      main_board.f++;
   } while ( main_board.f != main_board.end );

   for (int i=0; i<main_board.f; i++){
      for (int j=0; j<BOARD_H; j++){
         for (int k=0; k<BOARD_W; k++){
            printf("%d ", main_board.arr_val[i].mat[j][k]);
         }
         printf("\n");
      }
      printf("\n");
   }

   // check if all paired
   for (int j=0; j<BOARD_H; j++){
      for(int i=0; i<BOARD_W; i++){
         if (main_board.arr_val[main_board.f-1].mat[j][i] != PAIRED){
            return false;
         }
      }
   }
   return true;
}

bool take(board* p, pair z)
{
   // x means i, y menas j ; called by mat[j][i]
   int x1 = z.x1, x2 = z.x2, y1 = z.y1, y2 = z.y2;
   int num_1 = p->mat[y1][x1], num_2 = p->mat[y2][x2];
   
   bool is_same = (num_1 == num_2 && num_1 != PAIRED && num_2 != PAIRED);
   bool is_ten = (num_1 + num_2 == PAIRED_SUM);
   bool is_straight = checkStraight(p, z);
   bool is_touching = checkTouching(z);

   // if it's same      or  it's sum to ten
   //    and
   //    it's touching  or  it's straight
   if ((is_same || is_ten) && (is_straight || is_touching)){
      p->mat[y1][x1] = PAIRED;
      p->mat[y2][x2] = PAIRED;
      return true;
   }
   return false;
}

board randfill(int n)
{
   srand(n);
   board b;
   for(int j=0; j<BOARD_H; j++){
      for(int i=0; i<BOARD_W; i++){
         b.mat[j][i] = rand()%9 + 1;
      }
   }
   return b;
}

void test(void)
{
   // fake board
   board b = {
      .mat = {
         {1, 8,      8, 6, 6},
         {6, 2, PAIRED, 2, 5},
         {3, 2, PAIRED, 9, 5},
         {3, 4,      4, 4, 8}
      }
   };
   
   // check touched
   assert(checkTouching((pair){1,0,2,0}));  // (0,1) (0,2)
   assert(checkTouching((pair){1,1,1,2}));  // (1,1) (2,1)
   assert(checkTouching((pair){3,0,2,1}));  // (0,3) (1,2)
   assert(checkTouching((pair){2,1,3,0}));  // (1,2) (0,3)
   assert(!checkTouching((pair){0,2,2,2})); // (2,0) (2,2)

   /*check straight*/
   // note pair is x1, y1 -> in matrix it should be (y, x)
   // checkLinear
   assert(checkLinear((pair){1,0,2,0})); // (0,1) to (0,2)
   assert(checkLinear((pair){1,1,1,2})); // (1,1) to (2,1)
   assert(checkLinear((pair){2,2,0,2})); // (2,2) to (2,0)
   // checkNoBetween
   assert(checkNoBetween(&b, (pair){1,1,2,0}));  // (0,2) to (1,1)
   assert(checkNoBetween(&b, (pair){2,0,2,3}));  // (0,2) to (3,2)
   assert(!checkNoBetween(&b, (pair){3,0,3,3})); // (0,3) to (3,3)
   assert(checkNoBetween(&b, (pair){1,1,3,1}));  // (1,1) to (1,3)
   assert(!checkNoBetween(&b, (pair){4,0,1,3})); // (0,4) to (3,1)
   //checkStraight
   assert(checkStraight(&b, (pair){1,0,2,0}));  // (0,1) to (0,2)
   assert(checkStraight(&b, (pair){1,1,1,2}));  // (1,1) to (2,1)
   assert(!checkStraight(&b, (pair){2,2,0,2})); // (2,2) paired to (2,0)
   assert(checkStraight(&b, (pair){3,0,2,1}));  // (0,3) to (1,2) paired
   //solve
   assert(!solve(6)); // (0,1) to (0,2)
   
}

/* helper functions */
int abs_val(int x)
{
   if (x < 0){
      return -x;
   }
   return x;
}

bool inbound(int j, int i)
{
   return 0 <= j && j < BOARD_H && 0 <= i && i < BOARD_W;
}

eight_dirs dir_init(void)
{
   eight_dirs dir = {
      .j = {0, 1, 0, -1, 1, 1, -1, -1},
      .i = {1, 0, -1, 0, 1, -1, 1, -1}
   };
   return dir;
}

bool checkStraight(board* p, pair z)
{
   // T1: check it is reachable by just heading 8 directions
   // T2: check there is no any other number between
   bool is_linear = checkLinear(z);
   bool is_clear = true;
   if (is_linear){
      is_clear = checkNoBetween(p, z);
   }
   return is_linear && is_clear;
}

bool checkLinear(pair z)
{
   int x1 = z.x1, x2 = z.x2, y1 = z.y1, y2 = z.y2;
   int dx = x2 - x1, dy = y2 - y1;

   bool is_linear = false;
   bool is_vertical = (dy == 0 && dx != 0);
   bool is_horizontal = (dx == 0 && dy != 0);
   bool is_diagonal = (abs_val(dy) == abs_val(dx));
   if ( is_vertical || is_horizontal || is_diagonal){
      is_linear = true;
   }
   return is_linear;
}

bool checkNoBetween(board* p, pair z)
{
   int x1 = z.x1, x2 = z.x2, y1 = z.y1, y2 = z.y2;
   int dx = x2 - x1, dy = y2 - y1;
   int step_x = (dx > 0) ? 1 : (dx < 0 ? -1 : 0);
   int step_y = (dy > 0) ? 1 : (dy < 0 ? -1 : 0);
   
   bool is_clear = true;
   int j = y1 + step_y, i = x1 + step_x;
   while (inbound(j, i) && (j != y2 || i != x2)) {
      if (p->mat[j][i] != PAIRED){
         return false;
      }
      j += step_y;
      i += step_x;
   }
   return is_clear;
}

bool checkTouching(pair z)
{
   int x1 = z.x1, x2 = z.x2, y1 = z.y1, y2 = z.y2;
   // TODO: initialize directions
   eight_dirs dir = dir_init();
   // touching means adjacent
   bool is_adjacent = false;
   for (int i=0; i < EIGHT_DIRS; i++){
      int nj = y1 + dir.j[i];
      int ni = x1 + dir.i[i];
      if (inbound(nj, ni) && nj == y2 && ni == x2){
         is_adjacent = true;
      }
   }
   return is_adjacent;
}

void take_and_cpy(boards *head, board *mother_board, int j, int i){
   eight_dirs dir = dir_init();
   for (int range = 1; range <= BOARD_W ; range++){
      for (int nei=0; nei < EIGHT_DIRS; nei++){
         int nj = j + dir.j[nei] * range; 
         int ni = i + dir.i[nei] * range;
         board clean_board;
         board *cpy_b = &clean_board; 
         board_copy(mother_board, cpy_b);
         if (inbound(nj, ni) && take(cpy_b, (pair){i, j, ni, nj})){
            bool is_unique = checkUnique(head, cpy_b);
            if (is_unique) {
               board_copy(cpy_b, &head->arr_val[head->end]);
               head->end++;
            }
         }
      }
   }
}

void board_copy(board *old_board, board *new_board){
   for (int j=0; j<BOARD_H; j++){
      for (int i=0; i<BOARD_W; i++){
         new_board->mat[j][i] = old_board->mat[j][i];
      }
   }
}

bool checkUnique(boards *main_board_head, board *new_board) {
   for (int i = 0; i < main_board_head->end; i++) {
      bool identical = true;
      for (int j = 0; j < BOARD_H && identical; j++) {
         for (int k = 0; k < BOARD_W; k++) {
               if (main_board_head->arr_val[i].mat[j][k] != new_board->mat[j][k]) {
                  identical = false;
               }
         }
      }
      if (identical) {
         return false;
      }
   }
   return true;
}
