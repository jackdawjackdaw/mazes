#include "base.h"

#include <iostream>
#include <vector>
#include <map>

namespace mazes {
  cell::cell(int row, int col) {
    row_ = row;
    col_ = col;
    north_ = nullptr;
    south_ = nullptr;
    east_ = nullptr;
    west_ = nullptr;
  }

  void cell::link(cell& other, bool bidirectional) {
    // link this cell with the 'other'
    links_[other] = true;
    if (bidirectional) {
      other.link(*this, false);
    }
  }

  void cell::unlink(cell&other, bool bidirectional) {
    auto iter = links_.find(other);
    if (iter != links_.end()) {
      // undo the links
      links_.erase(other);
      if (bidirectional) {
        other.unlink(*this, false);
      }
    }
  }
  
  std::vector<cell*> cell::get_neighbours(void) {
    std::vector<cell*> res = {north_, sourth_, east_, west_};
    return res;
  }
  
  std::vector<cell&> cell:get_links(void) {
    std::vector<cell&> res; 
    for( auto it = links_.begin(); it != links_.end(); it++ ) {
      res.push_back(it->first;);
    }
    return res;
  }


  grid::grid(int rows, int columns) {
    rows_ = rows;
    cells_ = cells;
    cell_array_ = new 
    for (int i = 0; i < rows; i++) {
      cell_array
    }
  }
}
