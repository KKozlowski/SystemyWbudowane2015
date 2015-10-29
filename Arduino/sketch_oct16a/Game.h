#include "VGAX.h"
#include "Rocket.h"
#include "Margins.h"
#include "Obstacle.h"

#define obstCount 6

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
  
  void Begin()
  {
    VGAX::begin();
    VGAX::clear(0);
  }
  
  void Draw ()
  {
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

    if (currentButtonValue() == true && previousButtonValue == false){
      previousButtonValue = true;
      OnButtonPressed();
    } else 
      previousButtonValue=currentButtonValue();
  }

  void SpawnObstacle()
  {
    lastIndex = (lastIndex+1)%obstCount;
    obs[lastIndex].Activate();
  }

  void OnButtonPressed(){
    VGAX::tone(700);
  }
  
  bool currentButtonValue(){
    return digitalRead(13) == 1;
  }

  bool previousButtonValue = false;
};
