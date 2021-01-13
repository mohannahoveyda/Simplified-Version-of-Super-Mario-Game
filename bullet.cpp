#include "bullet.h"

  int  bullet:: get_x(){return x;}
  int bullet:: get_y(){return y;}
  int bullet:: get_size(){return size;}
  void bullet:: set_x(int ix){x=ix;}
  void bullet:: set_vX(int ix){vX=ix;}
  void bullet:: set_y(int iy){y=iy;}
  void bullet:: set_size(int isize){size=isize;}
  void bullet:: disable(){enable=false;}
  bool bullet:: is_enable(){return enable;}
  void bullet:: move(){
    if(enable){
      x+=vX;
    }
  }
  void bullet:: collide(int ix,int iy, int s){
    if(y>1+iy-size && y<iy+s)
    {
      if( x>=ix+s && x+vX<=ix+s && vX<=0){
        enable=false;
      }
      if( x+size<=ix && x+size+vX>=ix && vX>=0){
        enable=false;
      }
    }
  }
