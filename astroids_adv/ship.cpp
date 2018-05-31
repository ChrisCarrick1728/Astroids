#include "ship.h"
#include <iostream>
using namespace std;

// Put your ship methods here

/*************************************************************************
 * Constructor: Ship()
 * Purpose: Default Constructor.
 ************************************************************************/
Ship :: Ship()
{
   rotation = 0;
   size = SHIP_SIZE;
}

/*************************************************************************
 * Constructor: Ship(Point)
 * Purpose: Constructor that accepts a point.
 ************************************************************************/
Ship :: Ship(Point point)
{
   setPoint(point);
   size = SHIP_SIZE;
   rotation = 0;
}

/*************************************************************************
 * Method: advance()
 * Purpose: Used to advance our ship across the screen.
 ************************************************************************/
void Ship :: advance(float angle)
{
   point.addX(-velocity.getDx());
   point.addY(-velocity.getDy());
   
}

/*************************************************************************
 * Method: addThrust()
 * Purpose: Used to apply velocity to our ship.
 ************************************************************************/
void Ship :: addThrust()
{
      velocity.setDx(.5 * (sin(M_PI / 180.0 * rotation)));
      velocity.setDy(.5 * (-cos(M_PI / 180.0 * rotation)));
}

/*************************************************************************
 * Method: draw()
 * Purpose: Draws our ship.
 ************************************************************************/
void Ship :: draw()
{
   drawShip(getPoint(), rotation);
}

/*************************************************************************
 * Method: RotateRight()
 * Purpose: Rotates our ship to the right.
 ************************************************************************/
void Ship :: rotateRight()
{
   if (rotation >= 0)
      rotation -= 6;
   else
      rotation = 354;
}

/*************************************************************************
 * Method: rotateLeft()
 * Purpose: Rotates our ship to the left.
 ************************************************************************/
void Ship :: rotateLeft()
{
   if (rotation <= 360)
      rotation += 6;
   else
      rotation = 6;
}

void Ship :: resetVelocity()
{
   this->velocity.resetVelocity();
}


