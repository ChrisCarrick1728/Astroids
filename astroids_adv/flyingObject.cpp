 #include "flyingObject.h"

// Put your FlyingObject method bodies here
Point FlyingObject :: getPoint() const
{
   return point;
}

Velocity FlyingObject :: getVelocity() const
{
   return velocity;
}

bool FlyingObject :: isAlive() const
{
   return alive;
}

void FlyingObject :: setPoint(Point point)
{
   this->point = point;
}

void FlyingObject :: setVelocity(Velocity velocity)
{
   this->velocity = velocity;
}

void FlyingObject :: kill()
{
   this->alive = false;
}
