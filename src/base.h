#ifndef INCLUDE_BASE_H_
#define INCLUDE_BASE_H_
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace mazes {
  class cell {
    // A cell is the fundamental unit of the maze, this represents one 'room' in
    // the labyrinth. Each cell has a concept of it's neighbours: via the
    // links.
  public:
    explicit cell(const int& row, const int& col);
    void link(cell* other, const bool& bidirectional=false);
    void unlink(cell* other, const bool& bidirectional=false);
    // is this cell linked to the other?
    bool is_linked(cell* other);
    std::set<cell*> get_links() {return links_;};
    // return neighbours (n,s,e,w)
    std::vector<cell*> get_neighbours();

    void set_north(cell* other){north_ = other;};
    void set_south(cell* other){south_ = other;};
    void set_east(cell* other){east_   = other;};
    void set_west(cell* other){west_   = other;};

    cell* get_north(void){return north_; };
    cell* get_south(void){return south_; };
    cell* get_east(void){return east_;};
    cell* get_west(void){return west_;};

    int get_row(void){return row_;};
    int get_col(void){return column_;};
    std::string to_s(void);

  private:
    // links
    std::set<cell*> links_;
    // where are we
    int row_;
    int column_;
    // neighbours
    cell* north_;
    cell* south_;
    cell* east_;
    cell* west_;
  };

  class grid {
    // a cartesian collection of cells, this is our world
  public:
    explicit grid(int rows, int columns);
    cell* operator()(int i, int j){ return get_cell_at_loc(i,j);};
    // return a random cell from the grid
    cell* random_cell(void);
    // question: how could we implement an 'each row' or 'each cell'
    // method, in ruby this would be a yield block
    void each_cell(const std::function<void (cell*)>& work_fn);
    typedef std::vector<cell>::iterator cell_vec_iter;
    void each_row(const std::function<void (cell_vec_iter, cell_vec_iter)>& work_fn);

    int get_rows(void){return rows_;};
    int get_columns(void){return columns_;};
    int get_size(void){return rows_*columns_;};

    std::string to_string(void);
  private:
    // allocs the cells in the grid
    void prepare_grid(void);
    // sets up cardinal ptrs for the cells
    void configure_cells(void);
    // Imposes boundary conditions, all cell accesses run through here
    cell* get_cell_at_loc(int row, int col);
    int rows_;
    int columns_;
    std::vector<cell> cell_array_;
  };

} // mazes

#endif //INCLUDE_BASE_H_
