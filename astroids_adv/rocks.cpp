#include "rocks.h"
#include <iostream>
using namespace std;
// Put your Rock methods here

/*************************************************************************
 * Constructor: Rock()
 * Purpose: Default constructor.
 ************************************************************************/
Rock :: Rock()
{

}

/*************************************************************************
 * Method: advance()
 * Purpose: Handles advance our rock.
 ************************************************************************/
void Rock :: advance()
{
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
}

/*************************************************************************
 * Constructor: BigRock()
 * Purpose: Default constructor.
 ************************************************************************/
BigRock :: BigRock()
{
   setPoint(point);
}

/*************************************************************************
 * Constructor: BigRock()
 * Purpose: BigRock constructor that accepts a Point.
 ************************************************************************/
BigRock :: BigRock(Point point)
{
   setPoint(point);
   Velocity v;
   v.setDx(random(1, 3));
   v.setDy(random(1, 3));
   if (v.getDx() == 2)
      v.setDx(-3);
   
   if (v.getDy() == 2)
      v.setDy(-3);
   
   setVelocity(v);
   rotation = 0;
   size = BIG_ROCK_SIZE;
}

/*************************************************************************
 * Constructor: BigRock()
 * Purpose: BigRock constructor that accepts a Point and Velocity.
 ************************************************************************/
BigRock :: BigRock(Point point, Velocity velocity)
{
   setPoint(point);
   setVelocity(velocity);
   rotation = 0;
   size = BIG_ROCK_SIZE;
}

/*************************************************************************
 * Method: draw()
 * Purpose: draw's the big rock.
 ************************************************************************/
void BigRock :: draw()
{
   drawLargeAsteroid(getPoint(), rotation+=BIG_ROCK_SPIN);
}

/*************************************************************************
 * Method: hit()
 * Purpose: kill's the rock and returns the score.
 ************************************************************************/
int BigRock :: hit()
{
   kill();
   return 15;  // Used for scoring
}

/*************************************************************************
 * Constructor: MediumRock()
 * Purpose: Default constructor.
 ************************************************************************/
MediumRock :: MediumRock()
{
   setPoint(point);
}

/*************************************************************************
 * Constructor: mediumRock()
 * Purpose: mediumRock constructor that accepts a Point.
 ************************************************************************/
MediumRock :: MediumRock(Point point)
{
   setPoint(point);
   Velocity v;
   v.setDx(random(1, 3));
   v.setDy(random(1, 3));
   if (v.getDx() == 2)
      v.setDx(-3);
   
   if (v.getDy() == 2)
      v.setDy(-3);
   
   setVelocity(v);
   rotation = 0;
   size = MEDIUM_ROCK_SIZE;
}

/*************************************************************************
 * Constructor: mediumRock()
 * Purpose: mediumRock constructor that accepts a Point and Velocity.
 ************************************************************************/
MediumRock :: MediumRock(const Point point, Velocity velocity)
{
   setPoint(point);
   setVelocity(velocity);
   rotation = 0;
   size = MEDIUM_ROCK_SIZE;
}

/*************************************************************************
 * Method: draw()
 * Purpose: draw's the medium rock.
 ************************************************************************/
void MediumRock :: draw()
{
   drawMediumAsteroid(getPoint(), rotation+=MEDIUM_ROCK_SPIN);
}

/*************************************************************************
 * Method: hit()
 * Purpose: kill's the rock and returns the score.
 ************************************************************************/
int MediumRock :: hit()
{
   kill();
   return 30;  // Used for scoring
}

/*************************************************************************
 * Constructor: SmallRock()
 * Purpose: Default constructor.
 ************************************************************************/
SmallRock :: SmallRock()
{
   setPoint(point);
}

/*************************************************************************
 * Constructor: SmallRock()
 * Purpose: SmallRock constructor that accepts a Point.
 ************************************************************************/
SmallRock :: SmallRock(Point point)
{
   setPoint(point);
   Velocity v;
   v.setDx(random(1, 3));
   v.setDy(random(1, 3));
   if (v.getDx() == 2)
      v.setDx(-3);
   
   if (v.getDy() == 2)
      v.setDy(-3);
   
   setVelocity(v);
   rotation = 0;
   size = SMALL_ROCK_SIZE;
}

/*************************************************************************
 * Constructor: SmallRock()
 * Purpose: smallRock constructor that accepts a Point and Velocity.
 ************************************************************************/
SmallRock :: SmallRock(Point point, Velocity velocity)
{
   setPoint(point);
   setVelocity(velocity);
   rotation = 0;
   size = SMALL_ROCK_SIZE;
}

/*************************************************************************
 * Method: draw()
 * Purpose: draw's the small rock.
 ************************************************************************/
void SmallRock :: draw()
{
   drawSmallAsteroid(getPoint(), rotation += SMALL_ROCK_SPIN);
}

/*************************************************************************
 * Method: hit()
 * Purpose: kill's the rock and returns the score.
 ************************************************************************/
int SmallRock :: hit()
{
   kill();
   return 50;  // Used for scoring
}
