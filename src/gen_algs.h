#include "base.h"
#include <random>
#include <functional>


namespace mazes {
  class binary_tree_generator{
  public:
    binary_tree_generator();
    virtual ~binary_tree_generator();
    void gen_maze(mazes::grid* in_grid);
    void bin_tree_helper(mazes::cell* cptr);
  protected:
    std::default_random_engine *rng_;
  };
}
