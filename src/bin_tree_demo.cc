#include <iostream>
#include "base.h"
#include "gen_algs.h"

int main(void) {
  mazes::grid *gptr = nullptr;
  gptr = new mazes::grid(20,20);
  //mazes::BinaryTree(gptr);
  mazes::binary_tree_generator gen;
  gen.gen_maze(gptr);
  std::cout << gptr->to_string();
  delete gptr;
}
