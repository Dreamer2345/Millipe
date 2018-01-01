#include <Arduboy2.h>
#include <ArduboyTones.h>
Arduboy2 ard;
Sprites sprites;
ArduboyTones sound(ard.audio.enabled);
bool showarrow;
bool Audio = true;
#define CENTERX 63
#define CENTERY 31

uint32_t POINTS = 0;

enum class GameState {MainMenu,Game,Init,NextLevel,Dead};
GameState gameState = GameState::MainMenu;



bool Intersect(uint16_t Min0, uint16_t Max0, uint16_t Min1, uint16_t Max1){return ((Max0 > Min1) && (Min0 < Max1));}
bool Collision(uint16_t x, uint16_t y, uint16_t x1, uint16_t y1) {return (Intersect(x,x+7,x1,x1+7)&&Intersect(y,y+7,y1,y1+7));}


#include "Bitmaps.h"
#include "Player.h"
PlayerClass playerobj;
#include "Mushroom.h"
#include "Centepeed.h"
#include "Game.h"



void setup() {
  ard.boot();
  ard.flashlight();
  ard.audio.begin();
  ard.clear();
  ard.initRandomSeed();

  sprites.drawSelfMasked(CENTERX-26,CENTERY-17,MainLogo,0);
  ard.display();
  delay(1000);
}



void loop() {
  if(!ard.nextFrame())
    return;
  ard.pollButtons();
  ard.clear();

  switch(gameState) {
    case GameState::Game: GameUpdate(); break;
    case GameState::Init: GameInit(); break;
    case GameState::NextLevel: LevelScreen(); break;
    case GameState::MainMenu: UpdateMainMenu(); break;
    case GameState::Dead: DeathScreen(); break;
  }

  
  ard.display();
}
