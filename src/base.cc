#include "base.h"

#include <iostream>
#include <map>
#include <vector>

namespace mazes {
  cell::cell(const int& row, const int& col) {
    row_ = row;
    column_ = col;
    north_ = nullptr;
    south_ = nullptr;
    east_ = nullptr;
    west_ = nullptr;
  }

  void cell::link(cell* other, const bool& bidirectional) {
    // link this cell with the 'other'
    if (!other) {
      return;
    }
    links_.insert(other);
    if (bidirectional) {
      other->link(this, false);
    }
  }

  void cell::unlink(cell* other, const bool& bidirectional) {
    if (!other) {
      return;
    }
    auto iter = links_.find(other);
    if (iter != links_.end()) {
      // undo the links
      links_.erase(other);
      if (bidirectional) {
        other->unlink(this, false);
      }
    }
  }
  
  bool cell::is_linked(cell* other) {
    if (!other) {
      return false;
    }
    auto iter = links_.find(other);
    if (iter != links_.end()){
      return true;
    }
    return false;
  }

  std::set<cell*> cell::get_links(void) {
    return links_;
  }

  std::vector<cell*> cell::get_neighbours(void) {
    std::vector<cell*> res = {north_, south_, east_, west_};
    return res;
  }
  
  // grid stuff
  grid::grid(int rows, int columns) {
    rows_ = rows;
    columns_ = columns;
    prepare_grid();
    configure_cells();
  }

  cell* grid::get_cell_at_loc(int row, int col) {
    // but what about array bounds?
    if( row < rows_ && col < columns_ ) {
      return (&(cell_array_[row*columns_+col]));
    } 
    return nullptr;
  }
  
  void grid::prepare_grid(void) {
    // allocate the cell array
    for (int i = 0; i < rows_; i++) {
      for(int j = 0; j < columns_; j++) {
        cell_array_.emplace_back(i,j);
      }
    }
  }
  
  void grid::configure_cells(void) {
    for (int i = 0; i< rows_; i++) {
      for (int j = 0; j< columns_; j++) {
        cell* cell_ptr = get_cell_at_loc(i, j);
        cell_ptr->set_north(get_cell_at_loc(i+1, j));
        cell_ptr->set_south(get_cell_at_loc(i-1, j));
        cell_ptr->set_east(get_cell_at_loc(i, j+1));
        cell_ptr->set_west(get_cell_at_loc(i, j-1));
      }
    }
  }
    
}
