

#include "./src/rsdl.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 750
#define WINDOW_NAME "SUPER MARIO"

#include <fstream>
using namespace std;

int abs(int x){
  if(x<0){
    return -x;
  }else{
    return x;
  }
}
//Mario class
class Mario{
private:
  int face=1;
  // one is right
  //zero is left
  bool is_in_air=true;
  bool is_OnFire=false;
  string state="walking_right";
  int anim=0;
  int jump=90;
  int initX;
  int secX=0;
  int initY;
  int secY=0;
  int aX=0;
  int aY=10;
  int size=40;
  int coins=0;
  int joon=3;
  int shield_counter=0;
public:
  //getter
  int get_shield_counter(){return shield_counter;};
  bool canFire(){return is_OnFire;};
  int get_joon(){return joon;};
  int get_size(){return size;};
  int get_coins(){return coins;};
  int get_initX(){return initX;};
  int get_secX(){return secX;};
  int get_initY(){return initY;};
  int get_secY(){return secY;};
  int get_aX(){return aX;};
  int get_aY(){return aY;};
  int get_face(){return face;};
  int get_walking_number(){return (anim/1)%3 ;};
  string get_state(){return state;};
  bool get_IsInAir(){return is_in_air;};
  bool is_shieldless(){
    if(shield_counter>0){
      return false;
    }else{
      return true;
    }
  };
  bool mustbevisible(){
    if(is_shieldless()){
      if((shield_counter/10)%2==0){
        return true;
      }else{
        return false;
      }
    }else{
      return true;
    }
  }
  //setter
  void set_OnFire(bool b){is_OnFire=b;};
  void set_joon(int j){joon=j;};
  void set_size(int s){size=s;};
  void set_initX(int initialX){initX=initialX;};
  void set_secX(int secondaryX){ secX=secondaryX;};
  void set_initY(int initialY){initY=initialY;};
  void set_secY(int secondaryY){ secY=secondaryY;};
  void set_aX(int aInX){ aX=aInX;};
  void set_aY(int aInY){ aX=aInY;};
  void set_isInAir(bool isInAir){ is_in_air=isInAir;};
  void set_face(int f ){face=f;};
  void add_coin(){coins++;};
  void make_shield(){
    shield_counter=80;
  }
  int collide(int x,int y, int s){
    int jahat=-1;
    //0 is up
    //1 isdown
    //2isleft
    //3isright
    if(initY>1+y-size && 1+initY<y+s)
    {
      if(initX+size-x<=0 && initX+secX+size-x>=0  && secX>=0){
        jahat=2;
        initX=x-size;
        secX=-3;
      }
      else if( initX-(x+s)>=0 && initX+secX-(x+s)<=0  && secX<=0){
        jahat=3;
        initX=x+s;
        secX=3;
      }
     if(initX+size-x>0 && initX-(x+s)<0){
        if(face==1){
          jahat=2;
          initX=x-size;
          secX=0;
          face=0;
        }
        else if(face==0){
          jahat=3;
          initX=x+s;
          secX=0;
          face=1;
        }
      }

    }

    else if(initX>x-size && initX<x+s)
    {
      if(initY+size-y<=0 && initY+size+secY-y>=0  && secY>=0){
        jahat=0;
      }
      else if(  initY-(y+s)>=0 && initY+secY-(y+s)<=0  && secY<=0){
        jahat=1;
      }
    }
    return jahat;
  }
  bool canEat(int x,int y, int s){
    bool ret=false;
    if( initX<x+s && initX+size>x && initY<y+s && initY+size>y ){
      ret=true;
    }
    return ret;
  };
  void move(){
    if(shield_counter>0){
      shield_counter--;
    }
    secX+=aX;
    if(is_in_air){
      secY+=aY;
    }else{
      secY=0;
    }
    initX+=secX;
    initY+=secY;
    anim++;
  };
  void bounce(){
    if(is_in_air==false){
      secY=-jump;
      is_in_air=true;
    }
  };
  void littlebounce(){
    secY=-30;
    is_in_air=true;
  };
  void animation_check(){
    if (is_in_air==false) {
      if (secX<15 && secX>1 ) {
          state="sliding_right";
      }
      else if( secX>-15 && secX<-1){
        state="sliding_left";
      }
      else if(secX>15){
        state="walking_right";
      }
      else if(secX<-15){
        state="walking_left";
      }
        else{
          if (face==1) {
            state="standing_right";
          }
          else{
            state="standing_left";
          }
       }
    }
    else{
      if (face==1) {
      state="jumping_right";
      }
      else{
        state="jumping_left";
      }
    }
  }
  void friction(){
   if(!is_in_air){
    if (secX>0) {
      secX-=2;
    }
    else if (secX<0) {
      secX+=2;
    }
  }else{
    if (secX>0) {
      secX-=1;
    }
    else if (secX<0) {
      secX+=1;
    }
    }
  }
  //other member functions
};
//enemy classes
class littleGomba{
private:
  bool is_in_air=true;
  int x;
  int y;
  int vX=-10;
  int vY=0;
  int aY=10;
  int size=40;
  bool alive=true;
  bool visible=true;
  bool moving=false;
  int miny=10000;
  int dietimer=100;
  int walktimer=0;
public:
  //getter
  void compare(int iy){
    if(iy<miny){
      miny=iy;
    }
  };
  int get_minimumy(){return miny;};
  void set_minimumy(){miny=10000;};
  bool get_IsInAir(){return is_in_air;};
  int get_x(){return x;};
  int get_y(){return y;};
  int get_vY(){return vY;};
  int get_size(){return size;};
  bool Is_alive(){return alive;};
  bool Is_visible(){return visible;};
  bool Is_moving(){return moving;};
  int get_anim(){
    return (walktimer/3) %2;
  }
  ///setter
  void set_isInAir(bool b){is_in_air=b;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_vY(int ix){vY=ix;};
  void set_alive(bool b){alive=b;};
  void set_visible(bool b){visible=b;};
  void set_moving(bool b){moving=b;};
  /////////////
  int collide(int ix,int iy, int s){
    int jahat=-1;
    if(y>1+iy-size && y<iy+s)
    {
      if( x>=ix+s && x+vX<=ix+s && vX<=0){
        jahat=3;
        x=ix+s;
        vX=-vX;
      }
      if( x+size<=ix && x+size+vX>=ix && vX>=0){
        jahat=2;
        x=ix-size;
        vX=-vX;
      }
    }
    else if(x>ix-size && x<ix+s)
    {
      if(y+size<=iy && y+size+vY>=iy){
        jahat=0;
      }
    }
    return jahat;
  }
  bool canEat(int ix,int iy, int s){
    bool ret=false;
    if( x<ix+s && x+size>ix && y<iy+s && y+size>iy ){
      ret=true;
    }
    return ret;
  };
  void die(){
    alive=false;
    dietimer=100;
    vX=0;
    moving=false;
  };
  void move(){

    if(!alive ){
      dietimer-=5;
      if(dietimer<0){
        visible=false;
        dietimer=-10;
      }
    }
    if(moving){
      walktimer++;
      if(is_in_air){
        vY+=aY;
      }else{
        vY=0;
      }
      x+=vX;
      y+=vY;
    }
  };
};
class koopaTroopa{
private:
  bool is_in_air=true;
  int x;
  int y;
  int vX=-10;
  int vY=0;
  int aY=10;
  int size=40;
  bool alive=true;
  bool visible=true;
  bool moving=false;
  bool doodooda=false;
  int miny=10000;
  int dietimer=100;
  int walktimer=0;
public:
  //getter
  void compare(int iy){
    if(iy<miny){
      miny=iy;
    }
  };
  bool get_doodooda(){return doodooda;};
  int get_minimumy(){return miny;};
  void set_minimumy(){miny=10000;};
  bool get_IsInAir(){return is_in_air;};
  int get_x(){return x;};
  int get_y(){return y;};
  int get_vX(){return vX;};
  int get_vY(){return vY;};
  int get_size(){return size;};
  bool Is_alive(){return alive;};
  bool Is_visible(){return visible;};
  bool Is_moving(){return moving;};
  int get_anim(){
    return (walktimer/3) %2;
  }
  ///setter
  void set_doodooda(bool b){doodooda=b;};
  void set_isInAir(bool b){is_in_air=b;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_vX(int ix){vX=ix;};
  void set_vY(int ix){vY=ix;};
  void set_alive(bool b){alive=b;};
  void set_visible(bool b){visible=b;};
  void set_moving(bool b){moving=b;};
  /////////////
  int collide(int ix,int iy, int s){
    int jahat=-1;
    if(y>1+iy-size && y<iy+s)
    {
      if( x>=ix+s && x+vX<=ix+s && vX<=0){
        jahat=3;
        x=ix+s;
        vX=-vX;
      }
      if( x+size<=ix && x+size+vX>=ix && vX>=0){
        jahat=2;
        x=ix-size;
        vX=-vX;
      }
    }
    else if(x>ix-size && x<ix+s)
    {
      if(y+size<=iy && y+size+vY>=iy){
        jahat=0;
      }
    }
    return jahat;
  }
  bool canEat(int ix,int iy, int s){
    bool ret=false;
    if( x<ix+s && x+size>ix && y<iy+s && y+size>iy ){
      ret=true;
    }
    return ret;
  };
  void die(){
    alive=false;
    vX=0;
    dietimer=100;
    moving=false;
  };
  void die_doodooda(){
    alive=false;
    doodooda=true;
    vX=0;
    dietimer=100;
  };
  void move(){

    if(!alive && !doodooda ){
      dietimer-=5;
      if(dietimer<0){
        visible=false;
        dietimer=-10;
      }
    }
    if(moving){
      walktimer++;
      if(is_in_air){
        vY+=aY;
      }else{
        vY=0;
      }
      x+=vX;
      y+=vY;
    }
  };
};


//obstacle classes
class Block{
private:
  int x;
  int y;
  int size=50;
public:
  int  get_x(){return x;};
  int get_y(){return y;};
  int get_size(){return size;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
};

class pipe{
   int x;
  int y;
  int size=50;
  int lenght;
public:
  int  get_x(){return x;};
  int get_y(){return y;};
  int get_size(){return size;};
  int get_lenght(){return lenght;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
  void set_leght(int l){lenght=l;};
};

class regularBrick{
private:
  int x;
  int y;
  int size=50;
  int counter=0;
  bool isup=false;
  bool enable=true;
public:
  bool is_enable(){return enable;};
  int  get_x(){return x;};
  int get_y(){return y-counter;};
  int get_size(){return size;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
  void goup(){
    counter=10;
    isup=true;
  };
  void refresh(){
    if(isup){
      if(counter>0){
        counter-=5;
      }else{
        counter=0;
        isup=false;
      }
    }
  };
  void disable(){enable=false;};
};
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
  int  get_x(){return x;};
  int get_y(){return y-counter;};
  int get_size(){return size;};
  string get_content(){return content;};
  bool get_isUesd(){return isUsed;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
  void set_content(string cont){content=cont;};
  void set_isUsed(bool b){isUsed=b; };
  void goup(){
    counter=10;
    isup=true;
  };
  int get_anim(){return (timer/3)%3;}
  void refresh(){
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
  };
};//bricks contents classes

class prize{
private:
  int x;
  int y;
  int size=40;
  bool enable=true;
  string behave="coin";
public:
  int  get_x(){return x;};
  int get_y(){return y;};
  int get_size(){return size;};
  string get_behave(){return behave;};
  void set_x(int ix){x=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
  void set_behave(string b){behave=b;};
  void disable(){enable=false;};
  bool is_enable(){return enable;};
};
class bullet{
private:
  int x;
  int y;
  int vX;
  int size=20;
  bool enable=true;
public:
  int  get_x(){return x;};
  int get_y(){return y;};
  int get_size(){return size;};
  void set_x(int ix){x=ix;};
  void set_vX(int ix){vX=ix;};
  void set_y(int iy){y=iy;};
  void set_size(int isize){size=isize;};
  void disable(){enable=false;};
  bool is_enable(){return enable;};
  void move(){
    if(enable){
      x+=vX;
    }
  }
  void collide(int ix,int iy, int s){
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
};
class flag{
 int x;
 int y;
 int size=50;
 int lenght;
public:
 int get_x(){return x;};
 int get_y(){return y;};
 int get_size(){return size;};
 int get_lenght(){return lenght;};
 void set_x(int ix){x=ix;};
 void set_y(int iy){y=iy;};
 void set_size(int isize){size=isize;};
 void set_leght(int l){lenght=l;};
};

//Map class
class gameMap{
private:
  Mario mario;
  int cameraX=0;
  bool won=false;
  flag finishflag;
  vector<littleGomba> littleGombas;
  vector<koopaTroopa> koopaTroopas;
  vector<Block> earthlyBlocks;
  vector<Block> regularBlocks;
  vector <pipe> pipes;
  vector <regularBrick> regularBricks;
  vector <extraordinaryBrick> extraordinaryBricks;
  vector <prize> prizes;
  vector <bullet> bullets;
public:
  bool get_won(){return won;};
 void add_Block(int x,int y,int st){
   Block m;
   m.set_x(x);
   m.set_y(y);
   if(st==0){//earth
     earthlyBlocks.push_back(m);
   }else{//regular
     regularBlocks.push_back(m);
   }
 }
 void add_regularBrick(int x,int y){
   regularBrick m;
   m.set_x(x);
   m.set_y(y);
   regularBricks.push_back(m);
 }
 void add_exBrick(int x,int y,string cont){
   extraordinaryBrick m;
   m.set_x(x);
   m.set_y(y);
   m.set_content(cont);
   m.set_isUsed(false);
   extraordinaryBricks.push_back(m);
 }
 void add_pipe(int x,int y,int l){
   pipe p;
   p.set_x(x);
   p.set_y(y);
   p.set_leght(l);
   pipes.push_back(p);
 }
 void add_littleGomba(int x,int y){
   littleGomba p;
   p.set_isInAir(false);
   p.set_x(x);
   p.set_y(y);
   p.set_vY(0);
   p.set_alive(true);
   p.set_visible(true);
   p.set_moving(false);
   littleGombas.push_back(p);
 }
 void add_koopaTroopa(int x,int y){
   koopaTroopa p;
   p.set_isInAir(false);
   p.set_x(x);
   p.set_y(y);
   p.set_vY(0);
   p.set_alive(true);
   p.set_visible(true);
   p.set_moving(false);
   koopaTroopas.push_back(p);
 }
  Mario get_mario(){return mario;};
  void Set_Mario_place(int x, int y){
    mario.set_initX(x);
    mario.set_initY(y);
  };
  void marioBounce(){
    mario.bounce();
  };

  void set_mario_speed(int x, int y){
    mario.set_secX(x);
    mario.set_secY(y);
  };
  void set_mario_face(int f){
    mario.set_face(f);
  };
  void set_flag_place(int x,int y, int l){
    finishflag.set_x(x);
    finishflag.set_y(y);
    finishflag.set_leght(l);
  };
  void refreshbricks(){
    int i;
    int l=regularBricks.size();
    for ( i=0;i<l ;i++) {
      regularBricks[i].refresh();
    }
    l=extraordinaryBricks.size();
    for ( i=0;i<l ;i++) {
      extraordinaryBricks[i].refresh();
    }
  };
  void reset_exbricks(){
    int i;
    int l=extraordinaryBricks.size();
    for ( i=0;i<l ;i++) {
      extraordinaryBricks[i].set_isUsed(false);
    }
    for ( i=0;i<prizes.size() ;i++) {
      prizes[i].disable();
    }
  };
  void shoot(){
    //state=1   bulllet
    //state=2   dead body
    bullet b;
    if(mario.get_face()==0){
      b.set_vX(-25);
    }else{
      b.set_vX(25);
    }
    b.set_x(mario.get_initX() + (mario.get_size()-b.get_size())/2 );
    b.set_y(mario.get_initY() + (mario.get_size()-b.get_size())/2 );
    if(mario.canFire()){
        bullets.push_back(b);
    }
  };
  void physics_check(){
    if(mario.get_initY()>700){
      loose();
    }
    int i;
    int j;

    int collideResult=-1;
    int lilgombacollide=-1;
    bool check=false;
    bool tagh=false;
    int miny=10000;
    int maxy=-10000;
    Block bl;
    int l=earthlyBlocks.size();
    int l2=littleGombas.size();
    int l3=koopaTroopas.size();
    //////////////////////delete outbounded things
    for(j=0;j<l2;j++){
      littleGombas[j].set_minimumy();
      if(littleGombas[j].get_y()>800){
        littleGombas[j].set_moving(false);
        littleGombas[j].set_alive(false);
      }
    }
    for(j=0;j<l3;j++){
      koopaTroopas[j].set_minimumy();
      if(koopaTroopas[j].get_y()>800){
        koopaTroopas[j].set_moving(false);
        koopaTroopas[j].set_alive(false);
      }
    }
    /////////earthlyBlocks
    for ( i=0;i<l ;i++) {
      bl=  earthlyBlocks[i];
      collideResult=mario.collide(bl.get_x(),bl.get_y(),bl.get_size());
      if(collideResult==0){//up
        check=true;
        if( bl.get_y()< miny ){
          miny=bl.get_y();
        }
      }
      else if(collideResult==1){///down
        if( bl.get_y()> maxy ){
          maxy=bl.get_y();
        }
        tagh=true;
      }
      ////////for enemies
      for(j=0;j<l2;j++){
        lilgombacollide=littleGombas[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
        if(lilgombacollide==0){//up
          littleGombas[j].compare(bl.get_y());
        }
      }
      for(j=0;j<l3;j++){
        lilgombacollide=koopaTroopas[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
        if(lilgombacollide==0){//up
          koopaTroopas[j].compare(bl.get_y());
        }
      }
      for(j=0;j<bullets.size();j++){
        bullets[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
      }
    }

    ///////regularBlocks
    l=regularBlocks.size();
    for ( i=0;i<l ;i++) {
      bl= regularBlocks[i];
      collideResult=mario.collide(bl.get_x(),bl.get_y(),bl.get_size());
      if(collideResult==0){//up
        check=true;
        if( bl.get_y()< miny ){
          miny=bl.get_y();
        }
      }
      else if(collideResult==1){///down
        if( bl.get_y()> maxy ){
          maxy=bl.get_y();
        }
        tagh=true;
      }
      ////////for enemies
      for(j=0;j<l2;j++){
        lilgombacollide=littleGombas[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
        if(lilgombacollide==0){//up
          littleGombas[j].compare(bl.get_y());
        }
      }
      for(j=0;j<l3;j++){
        lilgombacollide=koopaTroopas[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
        if(lilgombacollide==0){//up
          koopaTroopas[j].compare(bl.get_y());
        }
      }
      for(j=0;j<bullets.size();j++){
        bullets[j].collide(bl.get_x(),bl.get_y(),bl.get_size());
      }
    }
    ////////regularBricks
    regularBrick br;
    l=regularBricks.size();
    int bricknumber=-1;
    for ( i=0;i<l ;i++) {
       br=  regularBricks[i];
       if(br.is_enable()){
          collideResult=mario.collide(br.get_x(),br.get_y(),br.get_size());
          if(collideResult==0){//up
            check=true;
            if( br.get_y()< miny ){
              miny=br.get_y();
            }
          }
          else if(collideResult==1){///down
            if(br.get_y()== maxy){
              if(bricknumber>-1 && abs(regularBricks[i].get_x()-mario.get_initX() )<abs(regularBricks[bricknumber].get_x()-mario.get_initX() )    ){
                bricknumber=i;
              }
            }else if( br.get_y()> maxy ){
              maxy=br.get_y();
              bricknumber=i;
            }
            tagh=true;
          }
          ////////enemies collision to regularbricks
          for(j=0;j<l2;j++){
            lilgombacollide=littleGombas[j].collide(br.get_x(),br.get_y(),br.get_size());
            if(lilgombacollide==0){//up
              littleGombas[j].compare(br.get_y());
            }
          }
          for(j=0;j<l3;j++){
            lilgombacollide=koopaTroopas[j].collide(br.get_x(),br.get_y(),br.get_size());
            if(lilgombacollide==0){//up
              koopaTroopas[j].compare(br.get_y());
            }
          }
          for(j=0;j<bullets.size();j++){
            bullets[j].collide(br.get_x(),br.get_y(),br.get_size());
          }
      }
    }
    //////////////extra bricks
    extraordinaryBrick ebr;
    l=extraordinaryBricks.size();
    int exbricknumber=-1;
    for ( i=0;i<l ;i++) {
       ebr=  extraordinaryBricks[i];
       collideResult=mario.collide(ebr.get_x(),ebr.get_y(),ebr.get_size());
       if(collideResult==0){//up
         check=true;
         if( ebr.get_y()< miny ){
           miny=ebr.get_y();
         }
       }
       else if(collideResult==1){///down
         if(ebr.get_y()== maxy){
           if(exbricknumber>-1 && abs(extraordinaryBricks[i].get_x()-mario.get_initX() )<abs(extraordinaryBricks[exbricknumber].get_x()-mario.get_initX() )    ){
             exbricknumber=i;
           }
           if( bricknumber>-1 && abs(extraordinaryBricks[i].get_x()-mario.get_initX() )<abs(regularBricks[bricknumber].get_x()-mario.get_initX() ) ){
             exbricknumber=i;
           }
         }else if( ebr.get_y()> maxy ){
           maxy=ebr.get_y();
           exbricknumber=i;
         }
         tagh=true;
       }
       ////////enemies collision to extrabricks
       for(j=0;j<l2;j++){
         lilgombacollide=littleGombas[j].collide(ebr.get_x(),ebr.get_y(),ebr.get_size());
         if(lilgombacollide==0){//up
           littleGombas[j].compare(ebr.get_y());
         }
       }
       for(j=0;j<l3;j++){
         lilgombacollide=koopaTroopas[j].collide(ebr.get_x(),ebr.get_y(),ebr.get_size());
         if(lilgombacollide==0){//up
           koopaTroopas[j].compare(ebr.get_y());
         }
       }
       for(j=0;j<bullets.size();j++){
         bullets[j].collide(ebr.get_x(),ebr.get_y(),ebr.get_size());
       }
    }
    //////////////////////////pipes
    pipe p;
    l=pipes.size();
    int len;
    int q;
    for ( i=0;i<l ;i++) {
       p=  pipes[i];
       len=p.get_lenght();
       for(j=0;j<len;j++){
          collideResult=mario.collide( p.get_x() , p.get_y()+ j*p.get_size() , p.get_size() );
          if(collideResult==0){//up
            check=true;
            if( p.get_y()+ j*p.get_size()< miny ){
              miny=p.get_y()+ j*p.get_size();
            }
          }
          else if(collideResult==1){///down
            if( p.get_y()+ j*p.get_size()> maxy ){
              maxy=p.get_y()+ j*p.get_size();
              exbricknumber=i;
            }
            tagh=true;
          }
          collideResult=mario.collide( p.get_x()+p.get_size() , p.get_y()+ j*p.get_size() , p.get_size() );
          if(collideResult==0){//up
            check=true;
            if( p.get_y()+ j*p.get_size()< miny ){
              miny=p.get_y()+ j*p.get_size();
            }
          }
          else if(collideResult==1){///down
              if( p.get_y()+ j*p.get_size()> maxy ){
                maxy=p.get_y()+ j*p.get_size();
                exbricknumber=i;
              }
              tagh=true;
          }
          /////////collision of enemies ad bullets with pipes
          for(q=0;q<littleGombas.size();q++){
            lilgombacollide=littleGombas[q].collide(p.get_x(),p.get_y()+j*p.get_size(),p.get_size());
            if(lilgombacollide==0){//up
              littleGombas[q].compare(p.get_y()+j*p.get_size());
            }
            lilgombacollide=littleGombas[q].collide(p.get_x()+p.get_size(),p.get_y()+j*p.get_size(),p.get_size());
            if(lilgombacollide==0){//up
              littleGombas[q].compare(p.get_y()+j*p.get_size());
            }
          }
          for(q=0;q<l3;q++){
            lilgombacollide=koopaTroopas[q].collide(p.get_x(),p.get_y()+j*p.get_size(),p.get_size());
            if(lilgombacollide==0){//up
              koopaTroopas[q].compare(p.get_y()+j*p.get_size());
            }
            lilgombacollide=koopaTroopas[q].collide(p.get_x()+p.get_size(),p.get_y()+j*p.get_size(),p.get_size());
            if(lilgombacollide==0){//up
              koopaTroopas[q].compare(p.get_y()+j*p.get_size());
            }
          }
          for(q=0;q<bullets.size();q++){
            bullets[q].collide(             p.get_x(),p.get_y()+j*p.get_size(),p.get_size());
            bullets[q].collide(p.get_x()+p.get_size(),p.get_y()+j*p.get_size(),p.get_size());
          }
       }
    }
    ///////////////////////////prizes
    l=prizes.size();
    for ( i=0;i<l ;i++) {
       if( prizes[i].is_enable() &&  mario.canEat(prizes[i].get_x(), prizes[i].get_y(), prizes[i].get_size() )    ){
         prizes[i].disable();
         if(prizes[i].get_behave()=="coin"){
           mario.add_coin();
         }
         if(prizes[i].get_behave()=="red_mushroom"){
           mario.set_size(70);
         }
         if(prizes[i].get_behave()=="health_mushroom"){
           mario.set_joon(1+mario.get_joon());
         }
         if(prizes[i].get_behave()=="fire_flower"){
           mario.set_OnFire(true);
         }
       }
    }
    ///////////////little goombas
    int k;
    for(j=0;j<l2;j++){
      if(littleGombas[j].Is_alive()){
        //killinggoombas with bullets
        for(k=0;k<bullets.size();k++){
          if(bullets[k].is_enable() && littleGombas[j].canEat(bullets[k].get_x(),bullets[k].get_y(),bullets[k].get_size())  ){
            prize C;
            C.set_behave(  "coin"  );
            C.set_x(littleGombas[j].get_x()+ (   (littleGombas[j].get_size()-C.get_size())/2 )    );
            C.set_y(littleGombas[j].get_y()    );
            prizes.push_back(C);
            littleGombas[j].die();
            bullets[k].disable();
          }
        }
        //killing goombas with doodooda
        for(k=0;k<koopaTroopas.size();k++){
          if(koopaTroopas[k].get_doodooda() && littleGombas[j].canEat(koopaTroopas[k].get_x(),koopaTroopas[k].get_y(),koopaTroopas[k].get_size())  ){
            prize C;
            C.set_behave(  "coin"  );
            C.set_x(littleGombas[j].get_x()+ (   (littleGombas[j].get_size()-C.get_size())/2 )    );
            C.set_y(littleGombas[j].get_y()    );
            prizes.push_back(C);
            littleGombas[j].die();
          }
        }
        //////mario && gomba
    if(mario.is_shieldless()){
        collideResult=mario.collide( littleGombas[j].get_x() , littleGombas[j].get_y(), littleGombas[j].get_size() );
        if(collideResult==0){//up
          mario.littlebounce();
          prize C;
          C.set_behave(  "coin"  );
          C.set_x(littleGombas[j].get_x()+ (   (littleGombas[j].get_size()-C.get_size())/2 )    );
          C.set_y(littleGombas[j].get_y()    );
          prizes.push_back(C);
          littleGombas[j].die();
        }else if(collideResult==2 || collideResult==3 || (collideResult==1 && littleGombas[j].get_y()>maxy ) ){
          if(mario.get_size()>50 || mario.canFire() ){
            mario.set_size(40);
            mario.set_OnFire(false);
            mario.make_shield();
          }else{
            loose();
          }
        }
      }
      }
    }
    ///////////////koopaTroopas
    for(j=0;j<koopaTroopas.size();j++){
      if(koopaTroopas[j].Is_alive()){
        //killing koopatroopa with bullets
        for(k=0;k<bullets.size();k++){
          if(bullets[k].is_enable() && koopaTroopas[j].canEat(bullets[k].get_x(),bullets[k].get_y(),bullets[k].get_size())  ){
            prize C;
            C.set_behave(  "coin"  );
            C.set_x(koopaTroopas[j].get_x()+ (   (koopaTroopas[j].get_size()-C.get_size())/2 )    );
            C.set_y(koopaTroopas[j].get_y()    );
            prizes.push_back(C);
            koopaTroopas[j].die();
            bullets[k].disable();
          }
        }
        //killing koopatropa with doodooda
        for(k=0;k<koopaTroopas.size();k++){
          if(j!=k && koopaTroopas[k].get_doodooda() && koopaTroopas[j].canEat(koopaTroopas[k].get_x(),koopaTroopas[k].get_y(),koopaTroopas[k].get_size())  ){
            prize C;
            C.set_behave(  "coin"  );
            C.set_x(koopaTroopas[j].get_x()+ (   (koopaTroopas[j].get_size()-C.get_size())/2 )    );
            C.set_y(koopaTroopas[j].get_y()    );
            prizes.push_back(C);
            koopaTroopas[j].die();
          }
        }
        //interaction mario & koopatroopa
    if(mario.is_shieldless()){
        collideResult=mario.collide( koopaTroopas[j].get_x() , koopaTroopas[j].get_y(), koopaTroopas[j].get_size() );
        if(collideResult==0){//up
          mario.littlebounce();
          prize C;
          C.set_behave(  "coin"  );
          C.set_x(koopaTroopas[j].get_x()+ (   (koopaTroopas[j].get_size()-C.get_size())/2 )    );
          C.set_y(koopaTroopas[j].get_y()    );
          prizes.push_back(C);
          koopaTroopas[j].die_doodooda();
        }else if(collideResult==2 || collideResult==3 || (collideResult==1 && koopaTroopas[j].get_y()>maxy ) ){
          if(mario.get_size()>50 || mario.canFire() ){
            mario.set_size(40);
            mario.set_OnFire(false);
            mario.make_shield();
          }else{
            loose();
          }
        }
      }
      }
      else if(koopaTroopas[j].get_doodooda() && koopaTroopas[j].get_vX()==0){
        collideResult=mario.collide( koopaTroopas[j].get_x() , koopaTroopas[j].get_y(), koopaTroopas[j].get_size() );
        if(collideResult==0 || collideResult==2){//up
            koopaTroopas[j].set_vX(30);
        }else if(collideResult==3){
            koopaTroopas[j].set_vX(-30);
        }
      }
    }

    /////////////finishflag
    l=finishflag.get_lenght();
    int temp;
    for ( i=0;i<l ;i++) {
       if(  mario.canEat( finishflag.get_x() ,finishflag.get_y()+ i*finishflag.get_size(),finishflag.get_size())   ){
         won=true;
       }
    }
    ////////check isinair for enemies
    for(j=0;j<l2;j++){
      if(littleGombas[j].get_minimumy()<8000){
        littleGombas[j].set_y(littleGombas[j].get_minimumy()-littleGombas[j].get_size());
        littleGombas[j].set_isInAir(false);
        littleGombas[j].set_vY(0);
      }else{
        littleGombas[j].set_isInAir(true);
      }
    }
    for(j=0;j<koopaTroopas.size();j++){
      if(koopaTroopas[j].get_minimumy()<8000){
        koopaTroopas[j].set_y(koopaTroopas[j].get_minimumy()-koopaTroopas[j].get_size());
        koopaTroopas[j].set_isInAir(false);
        koopaTroopas[j].set_vY(0);
      }else{
        koopaTroopas[j].set_isInAir(true);
      }
    }
    //////////
    if(check){
      mario.set_isInAir(false);
      mario.set_initY(miny-mario.get_size());
      mario.set_secY(0);
    }else{
      mario.set_isInAir(true);
      if(tagh){
        mario.set_initY(maxy+bl.get_size() );
        mario.set_secY(0);
        if(bricknumber>-1){
           regularBricks[bricknumber].goup();
           //kill enemies on it
           for(j=0;j<l2;j++){
             if(littleGombas[j].canEat( regularBricks[bricknumber].get_x() ,regularBricks[bricknumber].get_y()-littleGombas[j].get_size(),littleGombas[j].get_size() )          ){
               prize C;
               C.set_behave(  "coin"  );
               C.set_x(littleGombas[j].get_x()+ (   (littleGombas[j].get_size()-C.get_size())/2 )    );
               C.set_y(littleGombas[j].get_y()    );
               prizes.push_back(C);
               littleGombas[j].die();
             }
           }
           for(j=0;j<koopaTroopas.size();j++){
             if(koopaTroopas[j].canEat( regularBricks[bricknumber].get_x() ,regularBricks[bricknumber].get_y()-koopaTroopas[j].get_size(),koopaTroopas[j].get_size() )          ){
               prize C;
               C.set_behave(  "coin"  );
               C.set_x(koopaTroopas[j].get_x()+ (   (koopaTroopas[j].get_size()-C.get_size())/2 )    );
               C.set_y(koopaTroopas[j].get_y()    );
               prizes.push_back(C);
               koopaTroopas[j].die();
             }
           }
           if(mario.get_size()>50){
             regularBricks[bricknumber].disable();
           }
        }
        if(exbricknumber>-1){
           extraordinaryBricks[exbricknumber].goup();
           //kill enemies on it
           for(j=0;j<l2;j++){
             if(littleGombas[j].canEat( extraordinaryBricks[exbricknumber].get_x() ,extraordinaryBricks[exbricknumber].get_y()-littleGombas[j].get_size(),littleGombas[j].get_size() )          ){
               prize C;
               C.set_behave(  "coin"  );
               C.set_x(littleGombas[j].get_x()+ (   (littleGombas[j].get_size()-C.get_size())/2 )    );
               C.set_y(littleGombas[j].get_y()    );
               prizes.push_back(C);
               littleGombas[j].die();
             }
           }
           for(j=0;j<koopaTroopas.size();j++){
             if(koopaTroopas[j].canEat( extraordinaryBricks[exbricknumber].get_x() ,extraordinaryBricks[exbricknumber].get_y()-koopaTroopas[j].get_size(),koopaTroopas[j].get_size() )          ){
               prize C;
               C.set_behave(  "coin"  );
               C.set_x(koopaTroopas[j].get_x()+ (   (koopaTroopas[j].get_size()-C.get_size())/2 )    );
               C.set_y(koopaTroopas[j].get_y()    );
               prizes.push_back(C);
               koopaTroopas[j].die();
             }
           }
           prize C;
           if(extraordinaryBricks[exbricknumber].get_content()=="red_mushroom"){
                if(mario.get_size()>50){
                    C.set_behave(  "fire_flower"  );
                }else{
                    C.set_behave(  "red_mushroom"  );
                }
           }else{
                C.set_behave(  extraordinaryBricks[exbricknumber].get_content()  );
           }
           C.set_x(extraordinaryBricks[exbricknumber].get_x()+ (   (extraordinaryBricks[exbricknumber].get_size()-C.get_size())/2 )    );
           C.set_y(extraordinaryBricks[exbricknumber].get_y()- C.get_size()    );
           if(extraordinaryBricks[exbricknumber].get_isUesd()==false){
              prizes.push_back(C);
           }
           extraordinaryBricks[exbricknumber].set_isUsed(true);
        }
      }
    }
  };
  void move_enemies(){
    int l=littleGombas.size();
    int i;
    for ( i=0;i<l;i++) {
      if(littleGombas[i].get_x()-mario.get_initX()<400){
        littleGombas[i].set_moving(true);
      }
      littleGombas[i].move() ;
    }
    int j;
    for(j=0;j<koopaTroopas.size();j++){
      if(koopaTroopas[j].get_x()-mario.get_initX()<400){
        koopaTroopas[j].set_moving(true);
      }
      koopaTroopas[j].move() ;
    }
  };
  void move_bullets(){
    int l=bullets.size();
    int i;
    for ( i=0;i<l;i++) {
      if(bullets[i].is_enable()){
        bullets[i].move();
      }
    }
  };
  void dinamik(){
    physics_check();
    refreshbricks();
    move_enemies();
    move_bullets();
    mario.move();
    mario.friction();
  };
  //Draw functions
  //Draw Functions of obstacles
  void draw_earthlyBlock(Window *myWindow){
     Block bl;
     int l=earthlyBlocks.size();
     int i;
     for ( i=0;i<l;i++) {
       bl=  earthlyBlocks[i];
       myWindow->draw_img("./assets/sprites/objects/bricks_blocks/clay.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
     }
  };
  void draw_regularBlock(Window *myWindow){
    Block bl;
    int l=regularBlocks.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= regularBlocks[i];
      myWindow->draw_img("./assets/sprites/objects/bricks_blocks/block.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
    }
  };
  void draw_regularBrick(Window *myWindow){
    regularBrick bl;
    int l=regularBricks.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= regularBricks[i];
      if(bl.is_enable()){
        myWindow->draw_img("./assets/sprites/objects/bricks_blocks/brick.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
      }
    }
  };
  void draw_extraordineryBrick(Window *myWindow){
    extraordinaryBrick bl;
    int l=extraordinaryBricks.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= extraordinaryBricks[i];
      if(bl.get_isUesd()==false){
        if(bl.get_anim()==0){
          myWindow->draw_img("./assets/sprites/objects/bricks_blocks/question-1.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
        }else if(bl.get_anim()==1){
          myWindow->draw_img("./assets/sprites/objects/bricks_blocks/question-2.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
        }else{
          myWindow->draw_img("./assets/sprites/objects/bricks_blocks/question-3.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
        }
      }else{
        myWindow->draw_img("./assets/sprites/objects/bricks_blocks/question-empty.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
      }
    }
  };
  void draw_pipes(Window *myWindow){
    pipe p;
    int len=pipes.size();
    int i;
    int j;
    int l;
    for ( i=0;i<len;i++) {
      p= pipes[i];
      l=p.get_lenght();
      myWindow->draw_img("./assets/sprites/objects/pipe/head-left.png",               Rectangle(p.get_x()-5-cameraX,p.get_y() ,p.get_size()+10,p.get_size()) );
      myWindow->draw_img("./assets/sprites/objects/pipe/head-right.png", Rectangle(p.get_x()+p.get_size()-5-cameraX,p.get_y() ,p.get_size()+10,p.get_size()) );
      for(j=1;j<l;j++){
        myWindow->draw_img("./assets/sprites/objects/pipe/left.png",              Rectangle(p.get_x()-5-cameraX,p.get_y()+ j*p.get_size() ,p.get_size()+10,p.get_size()) );
        myWindow->draw_img("./assets/sprites/objects/pipe/right.png",Rectangle(p.get_x()+p.get_size()-5-cameraX,p.get_y()+ j*p.get_size() ,p.get_size()+10,p.get_size()) );
      }
    }
  };
  void draw_flag(Window *myWindow){
    int l=finishflag.get_lenght();
    int j;
    myWindow->draw_img("./assets/sprites/objects/flag/head.png", Rectangle(finishflag.get_x()-cameraX,finishflag.get_y() ,finishflag.get_size(),finishflag.get_size()) );
    for(j=1;j<l;j++){
        myWindow->draw_img("./assets/sprites/objects/flag/body.png",Rectangle(finishflag.get_x()-cameraX,finishflag.get_y()+ j*finishflag.get_size() ,finishflag.get_size(),finishflag.get_size()) );
    }

  };
  void draw_prizes(Window *myWindow){
    prize c;
    int l=prizes.size();
    int i;
    for ( i=0;i<l;i++) {
      c=prizes[i];
      if(c.is_enable()){
        if(c.get_behave()=="coin"){
          myWindow->draw_img("./assets/sprites/objects/coin.png", Rectangle(c.get_x()-cameraX,c.get_y(),c.get_size(),c.get_size()));
        }
        if(c.get_behave()=="red_mushroom"){
          myWindow->draw_img("./assets/sprites/objects/mushroom/red.png", Rectangle(c.get_x()-cameraX,c.get_y(),c.get_size(),c.get_size()));
        }
        if(c.get_behave()=="health_mushroom"){
          myWindow->draw_img("./assets/sprites/objects/mushroom/health.png", Rectangle(c.get_x()-cameraX,c.get_y(),c.get_size(),c.get_size()));
        }
        if(c.get_behave()=="fire_flower"){
          myWindow->draw_img("./assets/sprites/objects/flower.png", Rectangle(c.get_x()-cameraX,c.get_y(),c.get_size(),c.get_size()));
        }
      }
    }
  };
  void draw_bullets(Window *myWindow){
    bullet bl;
    int l=bullets.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= bullets[i];
      if(bl.is_enable()){
        myWindow->draw_img("./assets/sprites/objects/bricks_blocks/brick.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
      }
    }
  };
  //Draw Functions of ennemies
  void draw_littleGomba(Window *myWindow){
    littleGomba bl;
    int l=littleGombas.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= littleGombas[i];
      if(bl.Is_visible()){
        if(bl.Is_alive()){
          if(bl.get_anim()==1){
            myWindow->draw_img("./assets/sprites/enemies/little_goomba/walking-1.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
          }else{
            myWindow->draw_img("./assets/sprites/enemies/little_goomba/walking-2.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
          }
        }else{
          myWindow->draw_img("./assets/sprites/enemies/little_goomba/dead.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
        }
      }
    }
  };
  void draw_koopaTroopas(Window *myWindow){
    koopaTroopa bl;
    int l=koopaTroopas.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= koopaTroopas[i];
      if(bl.Is_visible()){
        if(bl.Is_alive()){
          if(bl.get_vX()<0){
            if(bl.get_anim()==1){
              myWindow->draw_img("./assets/sprites/enemies/koopa_troopa/walking-left-1.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
            }else{
              myWindow->draw_img("./assets/sprites/enemies/koopa_troopa/walking-left-2.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
            }
          }else{
            if(bl.get_anim()==1){
              myWindow->draw_img("./assets/sprites/enemies/koopa_troopa/walking-right-1.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
            }else{
              myWindow->draw_img("./assets/sprites/enemies/koopa_troopa/walking-right-2.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
            }
          }
        }else{
          myWindow->draw_img("./assets/sprites/enemies/koopa_troopa/dead.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
        }
      }
    }
  };
  void draw_panel(Window *myWindow){
    //myWindow->draw_img("background_image.png", Rectangle(0,0,1000,750));
    myWindow->fill_rect(Rectangle(0,0,1000,80), RGB(40,40,80));
    string message1="lives: "+ std::to_string(mario.get_joon());
    myWindow->show_text(message1,Point(10,10),RGB(255,255,255),"FreeSans.ttf",50);
    string message2="coins: "+ std::to_string(mario.get_coins());
    myWindow->show_text(message2,Point(800,10),RGB(255,255,255),"FreeSans.ttf",50);
  };
  void draw_bgPicture(Window *myWindow){
    myWindow->draw_img("./assets/background_image.png", Rectangle(-500-cameraX,0,20000,750));
  };
  void draw_mario(Window *myWindow){
    mario.animation_check();
    string folder;
    if(mario.canFire()){
      folder="white";
    }else{
      folder="normal";
    }
    if (mario.get_state()=="standing_right") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/standing-right.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="standing_left") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/standing-left.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="sliding_right") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/sliding-right.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="sliding_left") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/sliding-left.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="jumping_right") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/jumping-right.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="jumping_left") {
        myWindow->draw_img("./assets/sprites/mario/"+folder+"/jumping-left.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
    }
    if (mario.get_state()=="walking_right") {
      int number=mario.get_walking_number();
      if(number==0){
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-right-1.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
      }else if(number==1){
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-right-2.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
      }else{
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-right-3.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
      }
    }
    if (mario.get_state()=="walking_left") {
        int number=mario.get_walking_number();
        if(number==0){
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-left-1.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
        }else if(number==1){
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-left-2.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
        }else{
          myWindow->draw_img("./assets/sprites/mario/"+folder+"/walking-left-3.png", Rectangle(mario.get_initX()-cameraX,mario.get_initY(),mario.get_size(),mario.get_size()));
        }
    }
  };
  void loose(){
      Set_Mario_place(105,400);
      mario.set_joon(mario.get_joon() -1);
      mario.set_size(40);
      mario.set_OnFire(false);
      reset_exbricks();
  };
  void draw_all(Window *myWindow){
    dinamik();
    myWindow->clear();
    cameraX=mario.get_initX()-500;
    draw_bgPicture(myWindow);
    draw_bullets(myWindow);
    draw_mario(myWindow);
    draw_littleGomba(myWindow);
    draw_koopaTroopas(myWindow);
    draw_earthlyBlock(myWindow);
    draw_regularBlock(myWindow);
    draw_regularBrick(myWindow);
    draw_extraordineryBrick(myWindow);
    draw_prizes(myWindow);
    draw_pipes(myWindow);
    draw_flag(myWindow);
    draw_panel(myWindow);
    myWindow->update_screen();
  };
  void finalshow(Window *myWindow){
    mario.set_initX(finishflag.get_x());
    cameraX=mario.get_initX()-500;
    while(mario.get_initY() > finishflag.get_y()){
      delay(50);
      mario.set_initY(  mario.get_initY()  -5 );
      myWindow->clear();
      draw_bgPicture(myWindow);
      draw_earthlyBlock(myWindow);
      draw_regularBlock(myWindow);
      draw_regularBrick(myWindow);
      draw_extraordineryBrick(myWindow);
      draw_prizes(myWindow);
      draw_pipes(myWindow);
      draw_flag(myWindow);
      draw_mario(myWindow);
      draw_littleGomba(myWindow);
      draw_panel(myWindow);
      myWindow->update_screen();
    }
    while(mario.get_size() <100){
      delay(50);
      mario.set_size(  mario.get_size()  +1 );
      mario.set_initX(finishflag.get_x() + (finishflag.get_size()- mario.get_size())/2);
      mario.set_initY(finishflag.get_y() + (finishflag.get_size()- mario.get_size())/2);
      myWindow->clear();
      draw_bgPicture(myWindow);
      draw_earthlyBlock(myWindow);
      draw_regularBlock(myWindow);
      draw_regularBrick(myWindow);
      draw_extraordineryBrick(myWindow);
      draw_prizes(myWindow);
      draw_pipes(myWindow);
      draw_flag(myWindow);
      draw_mario(myWindow);
      draw_littleGomba(myWindow);
      draw_panel(myWindow);
      myWindow->update_screen();
    }
  };
};

int main(int argc, char const *argv[]) {
  gameMap newMap;
  string mapPath=argv[1];
  string s;
  ifstream mapFile;
  mapFile.open(mapPath);

  if(!mapFile){
  cerr << "Error: words.text could not be opened"<<endl;
  exit(1);
  }
  int tedad=0;
  int size_x;
  int size_y=0;
  string temp;
  int i;
  int pipechars[1000][40]={0};
  vector<int> pipeheadx;
  vector<int> pipeheady;
  while( getline(mapFile,s)){
    tedad++;
    if(tedad==1){
      size_x=s.size();
    }
    for(i=0;i<s.size();i++){
       temp=s.substr(i,1);
       if(temp=="b"){//regular_brick
         newMap.add_regularBrick(50*i,50*size_y);
       }else if(temp=="?"){//coin_brick
         newMap.add_exBrick(50*i,50*size_y,"coin");
       }else if(temp=="m"){//redmushroom_brick
         newMap.add_exBrick(50*i,50*size_y,"red_mushroom");
       }else if(temp=="h"){//health_brick
         newMap.add_exBrick(50*i,50*size_y,"health_mushroom");
       }else if(temp=="@"){//regularBlock
         newMap.add_Block(50*i,50*size_y,1);
       }else if(temp=="#"){//earthlyBlocks
         newMap.add_Block(50*i,50*size_y,0);
       }else if(temp=="M"){//mario
         newMap.Set_Mario_place(50*i,50*size_y);
       }else if(temp=="l"){//little goomba
         newMap.add_littleGomba(50*i,50*size_y);
       }else if(temp=="k"){//koopa troopa
         newMap.add_koopaTroopa(50*i,50*size_y);
       }else if(temp=="|"){//pipe
         pipechars[i][size_y]=1;
       }else if(temp=="f"){
         pipechars[i][size_y]=2;
       }
    }
    size_y++;
  }
  //adding pipes and flag
  int u;
  int upper;
  int lower;
  for(u=0;u<40;u++){
    for(i=0;i<1000;i++){
        if(pipechars[i][u]==2){
          upper=u;
          while(upper>=0 && pipechars[i][upper]==2){
            upper--;
          }
          upper++;
          lower=upper;
          while(lower<40 && pipechars[i][lower]==2){
            pipechars[i][lower]=0;
            lower++;
          }
          lower--;
          newMap.set_flag_place(50*i,50*upper, 1+lower-upper);
        }
        if(pipechars[i][u]==1){
          upper=u;
          while(upper>=0 && pipechars[i][upper]==1){
            upper--;
          }
          upper++;
          lower=upper;
          while(lower<40 && pipechars[i][lower]==1){
            pipechars[i][lower]=0;
            pipechars[i+1][lower]=0;
            lower++;
          }
          lower--;
          newMap.add_pipe(50*i,50*upper, 1+lower-upper);
        }
    }
  }

  Window myWindow= Window(1000,750,"SUPER MARIO");
  newMap.draw_all(&myWindow);
bool contin=true;
int hitn=0;
while(contin){
  if(myWindow.has_pending_event()){
    Event event=myWindow.poll_for_event();
     Event::EventType type = event.get_type();
     char pressed_char;
     if(type == Event::KEY_PRESS ) {
       pressed_char = event.get_pressed_key();
        if (pressed_char == 'w') {
          newMap.marioBounce();
        }
        if (pressed_char == 'a') {
          newMap.set_mario_speed(-20,newMap.get_mario().get_secY());
          newMap.set_mario_face(0);
        }
        if (pressed_char == 'd') {
          newMap.set_mario_speed(20,newMap.get_mario().get_secY());
          newMap.set_mario_face(1);
        }
        if (pressed_char == 'x') {
          newMap.shoot();
        }
     }
  }
  if(newMap.get_won()){
    contin=false;
    newMap.finalshow(&myWindow);
  }
  if(newMap.get_mario().get_joon()<=0){
    contin=false;
    cout<<"Game Over!";
  }
  newMap.draw_all(&myWindow);
  delay(50);
}
  return 0;
}
