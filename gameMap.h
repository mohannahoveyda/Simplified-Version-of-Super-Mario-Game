#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "/home/mohanna/src/rsdl.hpp"
#include "Mario.h"
#include "littleGomba.h"
#include "koopaTroopa.h"
#include "Block.h"
#include "pipe.h"
#include "regularBrick.h"
#include "extraordinaryBrick.h"
#include "prize.h"
#include "bullet.h"
#include "flag.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class gameMap{
private:
  Mario mario;
  int cameraX=0;
  bool won=false;
  flag finishflag;
  vector <littleGomba> littleGombas;
  vector <koopaTroopa> koopaTroopas;
  vector <Block> earthlyBlocks;
  vector <Block> regularBlocks;
  vector <pipe> pipes;
  vector <regularBrick> regularBricks;
  vector <extraordinaryBrick> extraordinaryBricks;
  vector <prize> prizes;
  vector <bullet> bullets;
public:
  bool get_won();
 void add_Block(int x,int y,int st);
 void add_regularBrick(int x,int y);
 void add_exBrick(int x,int y,string cont);
 void add_pipe(int x,int y,int l);
 void add_littleGomba(int x,int y);
 void add_koopaTroopa(int x,int y);
  Mario get_mario();
  void Set_Mario_place(int x, int y);
  void marioBounce();

  void set_mario_speed(int x, int y);
  void set_mario_face(int f);
  void set_flag_place(int x,int y, int l);
  void refreshbricks();
  void reset_exbricks();
  void shoot();
  void physics_check();
  void move_enemies();
  void move_bullets();
  void dinamik();
  //Draw functions
  //Draw Functions of obstacles
  void draw_earthlyBlock(Window *myWindow);
  void draw_regularBlock(Window *myWindow);
  void draw_regularBrick(Window *myWindow);
  void draw_extraordineryBrick(Window *myWindow);
  void draw_pipes(Window *myWindow);
  void draw_flag(Window *myWindow);
  void draw_prizes(Window *myWindow);
  void draw_bullets(Window *myWindow);
  //Draw Functions of ennemies
  void draw_littleGomba(Window *myWindow);
  void draw_koopaTroopas(Window *myWindow);
  void draw_panel(Window *myWindow);
  void draw_bgPicture(Window *myWindow);
  void draw_mario(Window *myWindow);
  void loose();
  void draw_all(Window *myWindow);
  void finalshow(Window *myWindow);
};
#endif
