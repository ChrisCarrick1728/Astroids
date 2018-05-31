#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"


// Put your FlyingObject class here



class FlyingObject
{
   public:
      FlyingObject()  {alive = true;}
      ~FlyingObject() {};
   
      Point    getPoint   () const;
      Velocity getVelocity() const;
      bool     isAlive    () const;
      void     setPoint   (Point point);
      void     setVelocity(Velocity velocity);
      void     kill       ();
      int      getSize(){ return size; };
   
   
   protected:
      Point    point;
      Velocity velocity;
      bool     alive;
      int      size;
      int      rotation;
};



#endif /* flyingObject_h */
