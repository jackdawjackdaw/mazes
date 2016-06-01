#include "base.h"
#include "gen_algs.h"
#include <functional>
#include <vector>
#include <random>
#include <iostream>


namespace mazes {
  binary_tree_generator::binary_tree_generator() {
    // currently default seed, figure out a random one here
    rng_ = new std::default_random_engine(213);
  }

  binary_tree_generator::~binary_tree_generator() {
    delete rng_;
  }

  void binary_tree_generator::gen_maze(mazes::grid* in_grid) {
    in_grid->each_cell([this](mazes::cell* cptr){this->bin_tree_helper(cptr);});
  }

  void binary_tree_generator::bin_tree_helper(mazes::cell* cptr) {
    std::vector<mazes::cell*> neighbours;
    if (cptr->get_north()) {
      neighbours.push_back(cptr->get_north());
    }
    if (cptr->get_east()) {
      neighbours.push_back(cptr->get_east());
    }
    if (neighbours.size() > 0) {
      // pick one
      std::uniform_int_distribution<int> n_dist(0, neighbours.size()-1);
      int n_index = n_dist(*rng_);
      mazes::cell* other = neighbours[n_index];
      cptr->link(other, true);
    }
  }
  
} // mazes
