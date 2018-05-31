#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
#include <cmath>

class Bullet : public FlyingObject
{
   public:
      Bullet();
      ~Bullet(){};
   
      void advance();
      void draw();
      void fire(Point point, float angle);
   private:
      int life;
   
};

#endif /* bullet_h */

