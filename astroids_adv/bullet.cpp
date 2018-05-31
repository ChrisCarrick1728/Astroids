//
//  bullet.cpp
//  skeet
//
//  Created by Chris Carrick on 2/25/18.
//  Copyright © 2018 Chris Carrick. All rights reserved.
//

#include "bullet.h"
#include <iostream>
using namespace std;

#define SPEED 5

/*************************************************************************
 * Constructor: Bullet()
 * Purpose: Default Constructor.
 ************************************************************************/
Bullet :: Bullet()
{
   life = 0;
   size = 1;
}

/*************************************************************************
 * Method: advance()
 * Purpose: used to advance the bullet in the correct direction for 40 frames.
 ************************************************************************/
void Bullet :: advance()
{
   point.addX(-velocity.getDx());
   point.addY(-velocity.getDy());
   life++;
   if (life == BULLET_LIFE)
   {
      kill();
   }
}

/*************************************************************************
 * Method: draw()
 * Purpose: Draws the bullets on the screen.
 ************************************************************************/
void Bullet :: draw()
{
   drawDot(point);
}

/*************************************************************************
 * Method: fire(point, float)
 * Purpose: Used to fire our bullet.
 ************************************************************************/
void Bullet :: fire(Point point, float angle)
{
   this->point.setX(point.getX());
   this->point.setY(point.getY());
   velocity.setDx(5.0 * (sin(M_PI / 180.0 * angle)));
   velocity.setDy(5.0 * (-cos(M_PI / 180.0 * angle)));
   //cout << "Bullet angel: " << angle << endl;
}

