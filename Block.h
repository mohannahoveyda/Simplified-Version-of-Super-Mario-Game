#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
class Block{
private:
  int x;
  int y;
  int size=50;
public:
  int get_x();
  int get_y();
  int get_size();
  void set_x(int ix);
  void set_y(int iy);
  void set_size(int isize);
};
#endif
