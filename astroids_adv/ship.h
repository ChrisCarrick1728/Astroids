#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#include "flyingObject.h"
#include "uiDraw.h"
#include "point.h"

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define MAX_THRUST 8



// Put your Ship class here
class Ship : public FlyingObject
{
   public:
      Ship();
      ~Ship() {};
      Ship(Point point);
      void advance(float angle);
      void draw();
      void rotateRight();
      void rotateLeft();
      void addThrust();
      int getAngle() { return this->rotation; };
      void resetVelocity();

};

#endif /* ship_h */
