/*************************************************************
 * File: velocity.cpp
 * Author: Christohper Carrick
 *
 * Description: Contains the implementations of the
 *  method bodies for the VELOCITY class.
 *
 *************************************************************/

#include "velocity.h"
#include <cassert>

/*************************************************************************
 * Method: Velocity()
 * Purpose: Constructor for our Velocity object.
 ************************************************************************/
Velocity :: Velocity()
{
   this->dx = 0.0;
   this->dy = 0.0;
}

/*************************************************************************
 * Method: Velocity(float, float)
 * Purpose: Non-Default Constructor for our Velocity object.
 ************************************************************************/
Velocity :: Velocity(float dx, float dy)
{
   this->dx += dx;
   this->dy += dy;
}

/*************************************************************************
 * Method: getDx()
 * Purpose: Returns the value of DX.
 ************************************************************************/
void Velocity :: resetVelocity()
{
   this->dx = 0.0;
   this->dy = 0.0;
}

/*************************************************************************
 * Method: getDx()
 * Purpose: Returns the value of DX.
 ************************************************************************/
float Velocity :: getDx() const
{
   return this->dx;
}

/*************************************************************************
 * Method: getDy()
 * Purpose: Returns the value of DY.
 ************************************************************************/
float Velocity :: getDy() const
{
   return this->dy;
}

/*************************************************************************
 * Method: setDx()
 * Purpose: Sets the value of DX.
 ************************************************************************/
void  Velocity :: setDx(float dx)
{
   this->dx += dx; // The "+=" adds inertia.
}

/*************************************************************************
 * Method: setDy()
 * Purpose: Sets the value of DY.
 ************************************************************************/
void  Velocity :: setDy(float dy)
{
   this->dy += dy; // The "+=" adds intertia.
}

/******************************************
 * POINT insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Velocity & vl)
{
   out << "(" << vl.getDx() << ", " << vl.getDy() << ")";
   return out;
}
