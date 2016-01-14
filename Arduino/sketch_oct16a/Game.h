#include "VGAX.h"
#include "Rocket.h"
#include "Margins.h"
#include "Obstacle.h"
#include "Bullet.h"

#define obstCount 6
#define bullCount 3

int a=0;
class Game
{
  private:
  byte spawnTimer;
  byte lastIndex;
  
  public:
  Rocket rocket;
  Margins margins;
  Obstacle obs[obstCount];
  Bullet bull[bullCount];
  
  void Begin()
  {
    
    VGAX::begin();
    VGAX::clear(0);
  }
  
  void Draw ()
  {
    if(rocket.IsAlive()){
      rocket.Draw();
      margins.Draw();
  
      //Rysowanie przeszkód
      for (int i = 0; i < obstCount; ++i)
      {
        if(obs[i].enabled)
        {
          obs[i].Draw();
          if (obs[i].posY >= 64)
          {
            //checkCollision
            obs[i].enabled = false;
          }
        }
      }
  
      //Spawnowanie przeszkód
      ++spawnTimer;
      if(!spawnTimer)
        SpawnObstacle();
  
      //Kolizje przeszkód z graczem.
      for (int i = 0; i < obstCount; ++i)
      {
        if(obs[i].posY > 52 && obs[i].posY <56){
          if (rocket.CollidesWith(obs[i].posX))
            rocket.Die();
          }
        }
  
      //Rysowanie pocisków
      for (int i=0; i<bullCount; ++i){
        if (bull[i].enabled){
          bull[i].Draw();
          if (bull[i].posY < -3)
            bull[i].enabled = false;
        }
      }
  
      //Kolizje pocisków
      for (int i=0; i<bullCount; ++i){
        if (bull[i].enabled){
          for (int k=0; k<obstCount; ++k){
            if(obs[k].enabled){
              if(obs[k].posX - bull[i].posX <= 2 && obs[k].posX - bull[i].posX>=-2
                  &&  obs[k].posY - bull[i].posY <= 2 && obs[k].posY - bull[i].posY >= -2){
                obs[k].Destroy();
                bull[i].Destroy();
                break;
              }
            }
          }
        }
      }
    } else {
      VGAX::clear(1);
    }

    //Sprawdzanie przycisku
      if (currentButtonValue() == true && previousButtonValue == false){
        previousButtonValue = true;
        OnButtonPressed();
      } else 
        previousButtonValue=currentButtonValue();
  }

  void SpawnObstacle()
  {
    lastIndex = (lastIndex+1)%obstCount;
    for (int i=0; i<obstCount; ++i){
      if (!obs[i].enabled){
        obs[i].Activate();
        break;
      }
    }
    //obs[lastIndex].Activate();
  }

  void OnButtonPressed(){
    VGAX::tone(700);
    if(rocket.IsAlive()){
      int posX = rocket.position;
      int posY = rocket.positionY-3;
      for (int i=0; i<bullCount; ++i){
        if (!bull[i].enabled){
          bull[i].Spawn(posX, posY);
          break;
        }
      }
    } else {
      reset();
    }
  }
  
  bool currentButtonValue(){
    return digitalRead(13) == 1;
  }

  void reset(){
    digitalWrite(11, LOW);
  }

  bool previousButtonValue = false;
};
