#include "gameMap.h"
  bool gameMap:: get_won(){return won;}
 void gameMap:: add_Block(int x,int y,int st){
   Block m;
   m.set_x(x);
   m.set_y(y);
   if(st==0){//earth
     earthlyBlocks.push_back(m);
   }else{//regular
     regularBlocks.push_back(m);
   }
 }
 void gameMap:: add_regularBrick(int x,int y){
   regularBrick m;
   m.set_x(x);
   m.set_y(y);
   regularBricks.push_back(m);
 }
 void gameMap:: add_exBrick(int x,int y,string cont){
   extraordinaryBrick m;
   m.set_x(x);
   m.set_y(y);
   m.set_content(cont);
   m.set_isUsed(false);
   extraordinaryBricks.push_back(m);
 }
 void gameMap:: add_pipe(int x,int y,int l){
   pipe p;
   p.set_x(x);
   p.set_y(y);
   p.set_leght(l);
   pipes.push_back(p);
 }
 void gameMap:: add_littleGomba(int x,int y){
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
 void gameMap:: add_koopaTroopa(int x,int y){
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
  Mario gameMap:: get_mario(){return mario;}
  void gameMap:: Set_Mario_place(int x, int y){
    mario.set_initX(x);
    mario.set_initY(y);
  }
  void gameMap:: marioBounce(){
    mario.bounce();
  }

  void gameMap:: set_mario_speed(int x, int y){
    mario.set_secX(x);
    mario.set_secY(y);
  }
  void gameMap:: set_mario_face(int f){
    mario.set_face(f);
  }
  void gameMap:: set_flag_place(int x,int y, int l){
    finishflag.set_x(x);
    finishflag.set_y(y);
    finishflag.set_leght(l);
  }
  void gameMap:: refreshbricks(){
    int i;
    int l=regularBricks.size();
    for ( i=0;i<l ;i++) {
      regularBricks[i].refresh();
    }
    l=extraordinaryBricks.size();
    for ( i=0;i<l ;i++) {
      extraordinaryBricks[i].refresh();
    }
  }
  void gameMap:: reset_exbricks(){
    int i;
    int l=extraordinaryBricks.size();
    for ( i=0;i<l ;i++) {
      extraordinaryBricks[i].set_isUsed(false);
    }
    for ( i=0;i<prizes.size() ;i++) {
      prizes[i].disable();
    }}

  void gameMap:: shoot(){
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
  }
  void gameMap:: physics_check(){
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
  }
  void gameMap:: move_enemies(){
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
  }
  void gameMap:: move_bullets(){
    int l=bullets.size();
    int i;
    for ( i=0;i<l;i++) {
      if(bullets[i].is_enable()){
        bullets[i].move();
      }
    }
  }
  void gameMap:: dinamik(){
    physics_check();
    refreshbricks();
    move_enemies();
    move_bullets();
    mario.move();
    mario.friction();
  }
  //Draw functions
  //Draw Functions of obstacles
  void gameMap:: draw_earthlyBlock(Window *myWindow){
     Block bl;
     int l=earthlyBlocks.size();
     int i;
     for ( i=0;i<l;i++) {
       bl=  earthlyBlocks[i];
       myWindow->draw_img("./assets/sprites/objects/bricks_blocks/clay.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
     }
  }
  void gameMap:: draw_regularBlock(Window *myWindow){
    Block bl;
    int l=regularBlocks.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= regularBlocks[i];
      myWindow->draw_img("./assets/sprites/objects/bricks_blocks/block.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
    }
  }
  void gameMap:: draw_regularBrick(Window *myWindow){
    regularBrick bl;
    int l=regularBricks.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= regularBricks[i];
      if(bl.is_enable()){
        myWindow->draw_img("./assets/sprites/objects/bricks_blocks/brick.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
      }
    }
  }
  void gameMap:: draw_extraordineryBrick(Window *myWindow){
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
  }
  void gameMap:: draw_pipes(Window *myWindow){
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
  }
  void gameMap:: draw_flag(Window *myWindow){
    int l=finishflag.get_lenght();
    int j;
    myWindow->draw_img("./assets/sprites/objects/flag/head.png", Rectangle(finishflag.get_x()-cameraX,finishflag.get_y() ,finishflag.get_size(),finishflag.get_size()) );
    for(j=1;j<l;j++){
        myWindow->draw_img("./assets/sprites/objects/flag/body.png",Rectangle(finishflag.get_x()-cameraX,finishflag.get_y()+ j*finishflag.get_size() ,finishflag.get_size(),finishflag.get_size()) );
    }

  }
  void gameMap:: draw_prizes(Window *myWindow){
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
  }
  void gameMap:: draw_bullets(Window *myWindow){
    bullet bl;
    int l=bullets.size();
    int i;
    for ( i=0;i<l;i++) {
      bl= bullets[i];
      if(bl.is_enable()){
        myWindow->draw_img("./assets/sprites/objects/bricks_blocks/brick.png", Rectangle(bl.get_x()-cameraX,bl.get_y(),bl.get_size(),bl.get_size()));
      }
    }
  }
  //Draw Functions of ennemies
  void gameMap:: draw_littleGomba(Window *myWindow){
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
  }
  void gameMap:: draw_koopaTroopas(Window *myWindow){
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
  }
  void gameMap:: draw_panel(Window *myWindow){
    //myWindow->draw_img("background_image.png", Rectangle(0,0,1000,750));
    myWindow->fill_rect(Rectangle(0,0,1000,80), RGB(40,40,80));
    string message1="lives: "+ std::to_string(mario.get_joon());
    myWindow->show_text(message1,Point(10,10),RGB(255,255,255),"FreeSans.ttf",50);
    string message2="coins: "+ std::to_string(mario.get_coins());
    myWindow->show_text(message2,Point(800,10),RGB(255,255,255),"FreeSans.ttf",50);
  }
  void gameMap:: draw_bgPicture(Window *myWindow){
    myWindow->draw_img("background_image.png", Rectangle(-500-cameraX,0,20000,750));
  }
  void gameMap:: draw_mario(Window *myWindow){
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
  }
  void gameMap:: loose(){
      Set_Mario_place(105,400);
      mario.set_joon(mario.get_joon() -1);
      mario.set_size(40);
      mario.set_OnFire(false);
      reset_exbricks();
  }
  void gameMap:: draw_all(Window *myWindow){
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
  }
  void gameMap:: finalshow(Window *myWindow){
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
  }
