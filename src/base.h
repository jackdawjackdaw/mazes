#include <vector>
#include <unordered_map>
#include <map>
#include <set>

// who are you, and why

// protos seem like something I want to be using here,
// to serialize everything?
//
// message maze {
//   message cell {
//    ...
//   } 
//   repeated cell cell_list
// }
// 
// lets focus on the battle

// TODO(gluon): a more consistent api: pick pointers or references
namespace mazes {
  class cell {
    // A cell is the fundamental unit of the maze, this represents one 'room' in the
    // labyrinth. Each cell has a concept of it's neighbours: via the concept of links.
    // 
    // needs:
    // attr_reader: row, col
    // attr_accessor: north, south, east, west
    // 
  public:
    // syntax here
    cell(const int& row, const int& col); 
    void link(cell* other, const bool& bidirectional=false);
    void unlink(cell* other, const bool& bidirectional=false);
    // is this cell linked to the other?
    bool is_linked(cell* other);
    // return the links
    std::set<cell*> get_links();
    // return the neighbours
    std::vector<cell*> get_neighbours();
    
    // blurgh, c'mon dude, you can do better than this shit
    void set_north(cell* other){north_ = other;};
    void set_south(cell* other){south_ = other;};
    void set_east(cell* other){east_   = other;};
    void set_west(cell* other){west_   = other;};

    cell* get_north(void){return north_; };
    cell* get_south(void){return south_; };
    cell* get_east(void){return east_;};
    cell* get_west(void){return west_;};
    
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
    // a collection of cells, this is our world
    // needs:
    // - an actual collection of cells
    // - a way to link cells together
    // - something like an operator override on []
    // - a heart!
  public:
    grid(int rows, int columns); 
    
  private:
    // helper, allocs the cells in the grid
    void prepare_grid(void);
    // sets up cardinal ptrs for the cells
    void configure_cells(void);
    // this is where to impose boundary conditions, all cell accesses
    // should run through here,
    // todo(gluon): well ok, but pointer or reference or what man?
    // this can be aliased to [] later...
    cell* get_cell_at_loc(int row, int col);
    int rows_;
    int columns_;
    // our actual 2d array of cells, how to allocate this?
    std::vector<cell> cell_array_;
  };
}

