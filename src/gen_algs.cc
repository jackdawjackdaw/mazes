#include "base.h"
#include <vector>
#include <random>
#include <iostream>

// TODO(chris): make this into a strategy pattern
// Store the RNG as internal state and init it each time
// TODO(chris): figure out how to test this, does it even work?

namespace {
  std::default_random_engine rando(1); // stupid seed but that's ok for now

  void bin_tree_helper(mazes::cell* cptr) {
    std::vector<mazes::cell*> neighbours;
    if (cptr->get_north()) {
      neighbours.push_back(cptr->get_north());
    }
    if (cptr->get_east()) {
      neighbours.push_back(cptr->get_east());
    }
    //std::cout << cptr->to_s() << ":" << neighbours.size();

    if (neighbours.size() > 0) {
      // pick one
      std::uniform_int_distribution<int> n_dist(0, neighbours.size()-1);
      int n_index = n_dist(rando);
      //std::cout << " idx: " << n_index;
      mazes::cell* other = neighbours[n_index];
      //std::cout << " other: " << other->to_s();
      cptr->link(other, true);
    }
    //std::cout << std::endl;
  }
} // end anonymous namespace

namespace mazes {
  void BinaryTree(grid* in_grid) {
    in_grid->each_cell(bin_tree_helper);
  }
} // mazes
