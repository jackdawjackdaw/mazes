#include "base.h"
#include <vector>
#include <random>
#include <iostream>

namespace {
  std::default_random_engine rando(123); // stupid seed but that's ok for now

  void bin_tree_helper(mazes::cell* cptr) {
    std::vector<mazes::cell*> neighbours;
    if (cptr->get_north()) {
      neighbours.push_back(cptr->get_north());
    }
    if (cptr->get_east()) {
      neighbours.push_back(cptr->get_east());
    }

    if(neighbours.size() > 0) {
      // pick one
      std::uniform_int_distribution<int> n_dist(0, neighbours.size()-1); 
      int n_index = n_dist(rando);
      cptr->link(neighbours[n_index], true);
    }
  }
} // end anonymous namespace

namespace mazes {
  void BinaryTree(grid* in_grid) {
    in_grid->each_cell(bin_tree_helper);
  }
} // mazes
