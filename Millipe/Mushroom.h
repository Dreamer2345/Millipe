#pragma once

#define MAXSHROOM 40
#define MAXSTARTSHROOM 15

class MushroomClass{
  public:
  void Set(uint8_t _x, uint8_t _y){x = _x; y = _y; H = 2; Active = true;}
  bool GetActive(){return Active;}
  uint8_t GetX() {return x;}
  uint8_t GetY() {return y;}
  void Disp();
  void Damage();
  private:
  bool Active = false;
  uint8_t x;
  uint8_t y;
  uint8_t H;
};

void MushroomClass::Disp(){  
  sprites.drawSelfMasked(x,y,Tiles,2-H);
}

void MushroomClass::Damage(){  
  if (H > 0) {
    H--;
    sound.noTone(); sound.tone(NOTE_G2,50); 
  } else { sound.noTone(); sound.tone(NOTE_G3,50); Active = false; POINTS += 5;}
}

MushroomClass Mushrooms[MAXSHROOM];
