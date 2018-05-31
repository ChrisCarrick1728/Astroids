/*************************************************************
 * File: velocity.h
 * Author: Christopher Carrick
 *
 * Description: Contains the definition of the velocity class.
 *
 *************************************************************/
#ifndef velocity_h
#define velocity_h

#include <iostream>
/*************************************************************************
 * Class: Velocity()
 * Purpose: Object to track the X and Y velocity of our object.
 ************************************************************************/
class Velocity
{
   public:
   
      // Constructors
      Velocity();
      Velocity(float dx, float dy);
   
      void resetVelocity();
   
      // Getters
      float getDx() const;
      float getDy() const;
   
      // Setters
      void  setDx(float dx);
      void  setDy(float dy);
   private:
      float dx;
      float dy;
};
std::ostream & operator << (std::ostream & out, const Velocity & vl);

#endif /* velocity_h */
