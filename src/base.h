#include <vector>
#include <unordered_map>
#include <map>
#include <set>

namespace mazes {
  class cell {
    // A cell is the fundamental unit of the maze, this represents one 'room' in
    // the labyrinth. Each cell has a concept of it's neighbours: via the
    // concept of links.
  public:
    cell(const int& row, const int& col); 
    void link(cell* other, const bool& bidirectional=false);
    void unlink(cell* other, const bool& bidirectional=false);
    // is this cell linked to the other?
    bool is_linked(cell* other);
    std::set<cell*> get_links() {return links_;};
    // return neighbours (n,s,e,w)
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
    // a cartesian collection of cells, this is our world
  public:
    grid(int rows, int columns); 
    cell* operator()(int i, int j){ return get_cell_at_loc(i,j);};
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
}

