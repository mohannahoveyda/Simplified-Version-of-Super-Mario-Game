#ifndef EXTRAORDINARYBRICK_H
#define EXTRAORDINARYBRICK_H
#include <iostream>
using namespace std;
class extraordinaryBrick{
private:
  int x;
  int y;
  int size=50;
  int counter=0;
  bool isup=false;
  string content="coin";
  bool isUsed=false;
  int timer=0;
public:
  int  get_x();
  int get_y();
  int get_size();
  string get_content();
  bool get_isUesd();
  void set_x(int ix);
  void set_y(int iy);
  void set_size(int isize);
  void set_content(string cont);
  void set_isUsed(bool b);
  void goup();
  int get_anim();
  void refresh();
};
#endif
