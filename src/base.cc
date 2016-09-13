#include "base.h"

#include <set>
#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <sstream>


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

  std::vector<cell*> cell::get_neighbours(void) {
    std::vector<cell*> res = {north_, south_, east_, west_};
    return res;
  }

  std::string cell::to_s(void) {
    std::ostringstream oss;
    oss << "(" << row_ << "," << column_ << ")";
    return oss.str();
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
    if( row < rows_ && row > -1 && col < columns_  && col > -1 ) {
      return (&(cell_array_[row*columns_+col]));
    }
    return nullptr;
  }

  cell* grid::random_cell(void) {
    // Seed with a real random value, if available
    //std::random_device r;
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(1234); // stupid seed but that's ok for now
    std::uniform_int_distribution<int> row_dist(0, rows_-1); // this is [a, b]
    std::uniform_int_distribution<int> col_dist(0, columns_-1);
    int rand_row = row_dist(e1);
    int rand_col = col_dist(e1);
    return get_cell_at_loc(rand_row, rand_col);
  }

  // do something to each cell
  void grid::each_cell(const std::function<void (cell*)>& work_fn) {
    for (int i = 0; i < rows_; i++) { // rows go south (0) to north (rows_-1)
      for(int j = 0; j < columns_; j++) { // cols go west (0) to east (cols_-1)
        work_fn(get_cell_at_loc(i, j));
      }
    }
  }

  typedef std::vector<cell>::iterator cell_vec_iter;

  void grid::each_row(const std::function<void (cell_vec_iter,
                                                cell_vec_iter)>& work_fn) {
    cell_vec_iter row_start, row_end;
    for (int i = 0; i < rows_; i++) {
      row_start = cell_array_.begin() + i*rows_;
      row_end = cell_array_.begin() + i*rows_ + columns_ ;
      work_fn(row_start, row_end);
    }
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

  std::string grid::to_string(void) {
    // There's really no need for this to be an ostringstream instead
    // of just a regular stringy string.
    std::ostringstream output;
    std::string top = "";
    std::string bottom = "";
    cell* cptr = nullptr;

    const std::string corner = "╬";
    const std::string rcorner = "╠"; // connects right only;
    const std::string lcorner = "╣"; // connects left only
    const std::string tcorner = "╦";
    const std::string bcorner = "╩";
    const std::string edge = "║";
    const std::string empty_edge = " ";
    const std::string empty_cell = "   ";
    const std::string cell_roof = "═══";

    output << corner;
    for (int i = 0; i < columns_; i++) {
      output << cell_roof << tcorner;
    }
    output << "\n";

    for (int i = rows_ - 1; i > -1; i--) {
      top = edge;
      bottom = rcorner;
      for(int j = 0; j < columns_; j++) {
        cptr = get_cell_at_loc(i, j);
        top += empty_cell;
        if (!cptr->is_linked(cptr->get_east()) || cptr->get_east() == nullptr) {
          top += edge;
        } else {
          top += empty_edge;
        }
        if (cptr->is_linked(cptr->get_south())) {
          bottom += empty_cell;
        } else {
          bottom += cell_roof;
        }
        if( j < columns_ - 1) {
          bottom += corner; // add a corner "+"
        } else {
          bottom += lcorner;
        }
      }
      output << top << "\n";
      output << bottom  << "\n";
    }
    return output.str();
  }
}  // mazes
