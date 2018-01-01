#pragma once

#define MAXBULLET 6


class BulletClass{
  public:
  void Set(uint8_t _x, uint8_t _y){x = _x; y = _y; Active = true;}
  bool GetActive(){return Active;}
  uint8_t GetX() {return x;}
  uint8_t GetY() {return y;}
  void Update();
  void Disp();
  void Kill();
  private:
  bool Active = false;
  uint8_t x;
  uint8_t y;
};

void BulletClass::Update(){  
  if (x+8 < 127)
    x += 1;
  else
    Active = false;
}

void BulletClass::Disp(){  
  sprites.drawSelfMasked(x,y,Tiles,6);
}

void BulletClass::Kill(){  
  Active = false;
}

BulletClass Bullets[MAXBULLET];





class PlayerClass{
  public:
  void PlayerMovement();
  uint8_t x;
  uint8_t H;
};

void PlayerClass::PlayerMovement(){

  if (ard.pressed(UP_BUTTON)){
    if (x > 0){
      x-=1;
      }
    }
  if (ard.pressed(DOWN_BUTTON)){
    if (x+8 < 64){
      x+=1;
    }
    }
  if (ard.justPressed(RIGHT_BUTTON)||ard.justPressed(A_BUTTON)){
    for (uint8_t i=0; i<MAXBULLET; i++){
      if (!Bullets[i].GetActive()){
        Bullets[i].Set(0,x);
        sound.noTone();
        sound.tone(NOTE_D2,50);
        break;
      }
    }
    }    
}

