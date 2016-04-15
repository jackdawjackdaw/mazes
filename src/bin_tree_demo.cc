#include <iostream>
#include "base.h"
#include "gen_algs.h"

int main(void) {

  mazes::grid *gptr = nullptr;
  for(int i = 0; i < 10; i++) {
    gptr = new mazes::grid(5,5);
    mazes::BinaryTree(gptr);
    std::cout << gptr->to_string_better();
    delete gptr;
  }
}
