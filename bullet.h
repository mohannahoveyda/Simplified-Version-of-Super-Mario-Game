#ifndef BULLET_H
#define BULLET_H
#include <iostream>
class bullet{
private:
  int x;
  int y;
  int vX;
  int size=20;
  bool enable=true;
public:
  int  get_x();
  int get_y();
  int get_size();
  void set_x(int ix);
  void set_vX(int ix);
  void set_y(int iy);
  void set_size(int isize);
  void disable();
  bool is_enable();
  void move();
  void collide(int ix,int iy, int s);
};
#endif
