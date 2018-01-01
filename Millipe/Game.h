#pragma once



uint8_t Length = 5;
uint8_t Level = 0;

void LevelSetup(){
  uint8_t x;
  uint8_t y;
  playerobj.H = 5;
  POINTS = 0;
  bool Done = false;
  for (uint8_t j=0; j<MAXSTARTSHROOM; j++){
    Done = false;
    while (not Done) {
      y = 8*random(0,7);
      x = 8*random(3,14);
      Done = true;
      for (uint8_t i=0; i<MAXSTARTSHROOM; i++){
        if ((Mushrooms[i].GetActive())&&(x == Mushrooms[i].GetX())&&(y == Mushrooms[i].GetY())){
          Done = false;
        }
      } 
    }
    Mushrooms[j].Set(x,y);
   }  
}

void NewLevel(){
  for (uint8_t j=0; j<MAXCENTE; j++){
    Cente[j].Kill();
  }
  
  uint8_t y = 8*random(0,7);
  uint8_t leng = (Length+Level);
  if (leng >= MAXCENTE) {leng = MAXCENTE;}
  for (uint8_t j=0; j<leng; j++){
    if (j == 0) 
      Cente[j].Set(119,y,0,true);
    else
      Cente[j].Set(119,y,(j-1),false);    
  }

  Level++;
}

void GameInit(){
  Length = 5;
  LevelSetup();
  NewLevel();
  gameState = GameState::Game;
}


void DrawCente(){
  for (uint8_t i=0; i<MAXCENTE; i++)
    if (Cente[i].GetActive())
      {
      Cente[i].Disp();
      }
}

void UpdateCente(){
  for (uint8_t i=0; i<MAXCENTE; i++)
    if (Cente[((MAXCENTE-1)-i)].GetActive())
      Cente[((MAXCENTE-1)-i)].Update();
}

void UpdateMainMenu(){
  sprites.drawSelfMasked(0,0,Title,0);
  if (showarrow){sprites.drawOverwrite(36,51,Arrow,0);}
  if (Audio){sprites.drawOverwrite(100,2,Speaker,1);} else {sprites.drawOverwrite(100,2,Speaker,0);}
  if (ard.justPressed(A_BUTTON)){
    sound.noTone();
    sound.tone(NOTE_C5,50);
    gameState = GameState::Init;
  }
  if (ard.justPressed(B_BUTTON)){
    Audio = !Audio;
    ard.audio.on();
    sound.noTone();
    sound.tone(NOTE_C4,50);
    ard.audio.off();
    if (Audio){ard.audio.on();}else{ard.audio.off();}
  }
  if (ard.everyXFrames(15)) {
      showarrow = !showarrow;
      }
}



void DrawPlayer(){
  sprites.drawSelfMasked(0,playerobj.x,Tiles,3);
}

void DrawBullets(){
  for (uint8_t i=0; i<MAXBULLET; i++)
    if (Bullets[i].GetActive())
      Bullets[i].Disp();
}

void DrawShrooms(){
  for (uint8_t i=0; i<MAXSHROOM; i++)
    if (Mushrooms[i].GetActive())
      Mushrooms[i].Disp();
}

void UpdateBullets(){
  for (uint8_t i=0; i<MAXBULLET; i++)
    if (Bullets[i].GetActive())
      Bullets[i].Update();
  for (uint8_t i=0; i<MAXBULLET; i++)
    if (Bullets[i].GetActive())
      for (uint8_t j=0; j<MAXSHROOM; j++)
        if (Mushrooms[j].GetActive() && Collision(Mushrooms[j].GetX(),Mushrooms[j].GetY(),Bullets[i].GetX(),Bullets[i].GetY())){
          Bullets[i].Kill();
          Mushrooms[j].Damage();
          break;
        }
        
  for (uint8_t i=0; i<MAXBULLET; i++)
    if (Bullets[i].GetActive())
      for (uint8_t j=0; j<MAXCENTE; j++)
        if (Cente[j].GetActive() && Collision(Cente[j].GetX(),Cente[j].GetY(),Bullets[i].GetX(),Bullets[i].GetY())){
          Bullets[i].Kill();
          Cente[j].Damage();
          if (j+1 != MAXCENTE){
            Cente[j+1].SetHead(true);
            Cente[j+1].SetDirect(!Cente[j].GetDirect());
          }
          break;
        }
}

void LevelScreen(){
  ard.print(F("Level:"));
  ard.println(Level);
  ard.print(F("Points:"));
  ard.println(POINTS);
  if(ard.everyXFrames(120)||(ard.justPressed(A_BUTTON))){NewLevel(); gameState = GameState::Game;}
}


void DeathScreen(){
  ard.print(F("Level:"));
  ard.println(Level);
  ard.print(F("Points:"));
  ard.println(POINTS);
  if(ard.justPressed(A_BUTTON)){ gameState = GameState::MainMenu;}
}

bool CheckAlive(){
  bool Alive = false;
   for (uint8_t j=0; j<MAXCENTE; j++)
     if (Cente[j].GetActive()){
        Alive = true;
     }
  return Alive;
}

void GameUpdate() {
  playerobj.PlayerMovement();
  UpdateBullets();
  if(ard.everyXFrames(15))
    UpdateCente();
  
  DrawShrooms();
  DrawPlayer();
  DrawBullets();
  DrawCente();

  if (!CheckAlive()){ sound.noTone(); sound.tone(NOTE_C5,50,NOTE_E5,50,NOTE_G5,50);gameState = GameState::NextLevel;}
  if ((playerobj.H == 0)||(playerobj.H > 5)) {gameState = GameState::Dead;}
  
  }
