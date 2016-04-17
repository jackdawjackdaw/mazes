#include "base.h"
#include <functional>
#include "gtest/gtest.h"

TEST(TrivialTest, True) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCell, TestLoc) {
  mazes::cell first_cell(1,2);
  
  EXPECT_EQ(first_cell.get_row(), 1);
  EXPECT_EQ(first_cell.get_col(), 2);
}

TEST(TestCell, SimpleLinking) {
  mazes::cell first_cell(1,2);
  mazes::cell second_cell(2,3);

  // at the start neither cell is linked
  EXPECT_FALSE(first_cell.is_linked(&second_cell));
  EXPECT_FALSE(second_cell.is_linked(&first_cell));

  // link 1->2 but don't do it bidirectionally
  first_cell.link(&second_cell);
  EXPECT_TRUE(first_cell.is_linked(&second_cell));
  EXPECT_FALSE(second_cell.is_linked(&first_cell));

  // now link 2 back to 1
  second_cell.link(&first_cell);
  EXPECT_TRUE(first_cell.is_linked(&second_cell));
  EXPECT_TRUE(second_cell.is_linked(&first_cell));

  // undo link, both ways
  first_cell.unlink(&second_cell, true);
  EXPECT_FALSE(first_cell.is_linked(&second_cell));
  EXPECT_FALSE(second_cell.is_linked(&first_cell));

  // now test bidirectional linking 1<->2
  first_cell.link(&second_cell, true);
  EXPECT_TRUE(first_cell.is_linked(&second_cell));
  EXPECT_TRUE(second_cell.is_linked(&first_cell));

  // and unlink one way, 1<-2
  first_cell.unlink(&second_cell);
  EXPECT_FALSE(first_cell.is_linked(&second_cell));
  EXPECT_TRUE(second_cell.is_linked(&first_cell));
}

TEST(TestCell, MoreLinking) {
  mazes::cell first_cell(1,2);
  mazes::cell second_cell(2,3);

  // double link should be fine
  first_cell.link(&second_cell);
  EXPECT_TRUE(first_cell.is_linked(&second_cell));  
  first_cell.link(&second_cell);
  EXPECT_TRUE(first_cell.is_linked(&second_cell));
}

TEST(TestCell, GetLinks) {
  mazes::cell first_cell(1,2);
  mazes::cell second_cell(2,3);
  mazes::cell third_cell(3,3);
  
  auto links = first_cell.get_links();
  EXPECT_TRUE(links.empty());

  first_cell.link(&second_cell, true);
  first_cell.link(&third_cell, true);

  links =  first_cell.get_links();
  EXPECT_EQ(links.size(), 2);
  
  auto iter = links.find(&second_cell);
  EXPECT_TRUE((iter != links.end()));
  iter = links.find(&third_cell);
  EXPECT_TRUE((iter != links.end()));
}

TEST(TestGrid, TestInit) {
  mazes::grid the_grid(4,4);
  mazes::cell* cptr = the_grid(2,2);
  mazes::cell* cother;
  
  EXPECT_EQ(cptr->get_north(), the_grid(3,2));
  EXPECT_EQ(cptr->get_south(), the_grid(1,2));
  EXPECT_EQ(cptr->get_east(), the_grid(2,3));
  EXPECT_EQ(cptr->get_west(), the_grid(2,1));

  cother = cptr->get_north();
  EXPECT_EQ(cother->get_row(), 3);
  cother = cptr->get_south();
  EXPECT_EQ(cother->get_row(), 1);
  cother = cptr->get_east();
  EXPECT_EQ(cother->get_col(), 3);
  cother = cptr->get_west();
  EXPECT_EQ(cother->get_col(), 1);

}

TEST(TestGrid, TestBoundary) {
  mazes::grid the_grid(4,4);
  // top right (north east) corner 
  mazes::cell* cptr = the_grid(3,3);
  EXPECT_EQ(cptr->get_north(), nullptr);
  EXPECT_EQ(cptr->get_east(), nullptr);
  EXPECT_NE(cptr->get_west(), nullptr);
  EXPECT_NE(cptr->get_south(), nullptr);

  // bottom right corner (south east)
  cptr = the_grid(0,3);
  EXPECT_NE(cptr->get_north(), nullptr);
  EXPECT_EQ(cptr->get_east(), nullptr);
  EXPECT_NE(cptr->get_west(), nullptr);
  EXPECT_EQ(cptr->get_south(), nullptr);

  // bottom left corner (south west)
  cptr = the_grid(0,0);
  EXPECT_NE(cptr->get_north(), nullptr);
  EXPECT_NE(cptr->get_east(), nullptr);
  EXPECT_EQ(cptr->get_west(), nullptr);
  EXPECT_EQ(cptr->get_south(), nullptr);

  // top left corner (north west)
  cptr = the_grid(3,0);
  EXPECT_EQ(cptr->get_north(), nullptr);
  EXPECT_NE(cptr->get_east(), nullptr);
  EXPECT_EQ(cptr->get_west(), nullptr);
  EXPECT_NE(cptr->get_south(), nullptr);

  cptr = the_grid(4,5);
  EXPECT_EQ(cptr, nullptr);
}

TEST(TestGrid, TestRandom) {
  mazes::grid the_grid(4,4);
  mazes::cell* cptr = the_grid.random_cell();
  EXPECT_TRUE(cptr != nullptr);
}

void print_cell(mazes::cell* cptr) {
  std::cout << cptr->to_s() << std::endl;
}

typedef std::vector<mazes::cell>::iterator cell_vec_iter;
void print_row(cell_vec_iter start, cell_vec_iter end) {
  cell_vec_iter curr;
  for (curr = start; curr != end; ++curr) {
    print_cell(&(*curr));
  }
  std::cout << std::endl;
}

TEST(TestGrid, TestEach) {
  mazes::grid the_grid(4,4);
  the_grid.each_cell(print_cell);
  std::cout << std::endl;
  the_grid.each_row(print_row);  
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
