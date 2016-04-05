#include <iostream>
#include "base.h"
#include "gen_algs.h"

int main(void) {
  mazes::grid test_grid(5,5);
  mazes::BinaryTree(&test_grid);
  std::cout << test_grid.to_string();
}
