#ifndef FLAG_H
#define FLAG_H
#include <iostream>
class flag{
 int x;
 int y;
 int size=50;
 int lenght;
public:
 int get_x();
 int get_y();
 int get_size();
 int get_lenght();
 void set_x(int ix);
 void set_y(int iy);
 void set_size(int isize);
 void set_leght(int l);
};
#endif
