#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "point.h"
#include "flyingObject.h"
#include "uiDraw.h"



// Define the following classes here:

//   Rock
class Rock : public FlyingObject
{
   public :
      Rock();
      Rock(Point point);
      ~Rock(){};
      void advance();
      virtual int hit(){kill();return 6;};
      virtual void draw(){};
      virtual string getName() {return "hello";};
};

//   BigRock
class BigRock : public Rock
{
   public:
      BigRock();
      BigRock(Point point);
      BigRock(Point point, Velocity velocity);
      ~BigRock(){}
      void draw();
      int hit();
      string getName() { return "BigRock"; };
   
};

//   MediumRock
class MediumRock : public Rock
{
   public:
      MediumRock();
      MediumRock(Point point);
      MediumRock(Point point, Velocity velocity);
      ~MediumRock(){}
      void draw();
      int hit();
      string getName() { return "MediumRock"; };
};

//   SmallRock
class SmallRock : public Rock
{
   public:
      SmallRock();
      SmallRock(Point point);
      SmallRock(Point point, Velocity velocity);
      ~SmallRock(){}
      void draw();
      int hit();
      string getName() { return "SmallRock"; };
};

#endif /* rocks_h */
