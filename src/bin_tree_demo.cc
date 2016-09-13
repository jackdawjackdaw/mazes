#include <iostream>
#include "base.h"
#include "gen_algs.h"

int main(void) {
  mazes::grid *gptr = new mazes::grid(20,20);
  mazes::binary_tree_generator gen;
  gen.gen_maze(gptr);
  std::cout << gptr->to_string();
  delete gptr;
}
