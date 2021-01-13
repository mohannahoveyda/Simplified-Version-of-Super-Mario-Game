#include "extraordinaryBrick.h"

  int  extraordinaryBrick::get_x(){return x;}
  int extraordinaryBrick::get_y(){return y-counter;}
  int extraordinaryBrick::get_size(){return size;}
  string extraordinaryBrick::get_content(){return content;}
  bool extraordinaryBrick::get_isUesd(){return isUsed;}
  void extraordinaryBrick::set_x(int ix){x=ix;}
  void extraordinaryBrick::set_y(int iy){y=iy;}
  void extraordinaryBrick::set_size(int isize){size=isize;}
  void extraordinaryBrick::set_content(string cont){content=cont;}
  void extraordinaryBrick::set_isUsed(bool b){isUsed=b; }
  void extraordinaryBrick::goup(){
    counter=10;
    isup=true;
  }
  int extraordinaryBrick::get_anim(){return (timer/3)%3;}
  void extraordinaryBrick::refresh(){
    if(timer>10000){
      timer=0;
    }
    timer++;
    if(isup){
      if(counter>0){
        counter-=5;
      }else{
        counter=0;
        isup=false;
      }
    }
  }
