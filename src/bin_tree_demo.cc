#include <iostream>
#include "base.h"
#include "gen_algs.h"

int main(void) {
  mazes::grid *gptr = nullptr;
  gptr = new mazes::grid(15,15);
  mazes::BinaryTree(gptr);
  std::cout << gptr->to_string();
  delete gptr;
}
