#pragma once

#define MAXCENTE 30

bool Check(uint8_t x,uint8_t y){
  if ((y+8 > 64)||(y > 64)) return true;
  if (x == 0) return true;
  for (uint8_t j=0; j<MAXSHROOM; j++)
        if (Mushrooms[j].GetActive() && Collision(Mushrooms[j].GetX(),Mushrooms[j].GetY(),x,y)){
            return true;
        }
  return false;
}

class CenteClass{
  public:
  void Set(uint8_t _x, uint8_t _y, uint8_t _p, bool _h){Parent = _p; x = _x; y = _y; Head = _h; Direct = true; Active = true;}
  bool GetActive(){return Active;}
  void SetHead(bool k){Head = k;}
  void SetDirect(bool k) {Direct = k;}
  bool GetDirect() {return Direct;}
  uint8_t GetX() {return x;}
  uint8_t GetY() {return y;}
  void Disp();
  void Damage();
  void Update();
  void Kill();
  private:
  bool Active;
  bool Direct;
  bool Head;
  uint8_t x;
  uint8_t y;
  uint8_t Parent = 0;
};

CenteClass Cente[MAXCENTE];

void CenteClass::Disp(){  
  if (Head){
    sprites.drawSelfMasked(x,y,Tiles,4);
  }else {
    sprites.drawSelfMasked(x,y,Tiles,5);
  }
}

void CenteClass::Update(){
  if (!(Head)) {
    x = Cente[Parent].GetX();
    y = Cente[Parent].GetY();
    Direct = Cente[Parent].GetDirect();
  } else {
    if (Direct) {
      if (!(Check(x,y+8))) y+=8;
      else {if (!(Check(x-8,y))) {x-=8;} Direct = !Direct;} 
    } else {
      if (!(Check(x,y-8))) y-=8;
      else {if (!(Check(x-8,y))) {x-=8;} Direct = !Direct;}
    }
    if ((x > 119)||(x==0)) {x = (127-8); playerobj.H--; Direct = !Direct;}

    if (Check(x-8,y)&&(Check(x,y+8)&&Check(x,y-8))){
      while (Check(x,y+8)&&Check(x,y-8)) {x += 8;}
    }
    
  }
}


void CenteClass::Kill(){  
  Active = false;
}

void CenteClass::Damage(){  
  Active = false;
  sound.noTone();
  sound.tone(NOTE_E3H,50);
  for(uint8_t i=0; i<MAXSHROOM; i++){
    if (!Mushrooms[i].GetActive()) {
      Mushrooms[i].Set((x+1),y);
      break;
    }
  }
  POINTS += 30;
}


