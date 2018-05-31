/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <cstdlib>
#include <string>
#include <cstring>
#include <limits>
#include <algorithm>
using namespace std;


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   obj1.getVelocity();
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/*********************************************************************
 * SLEEP
 * Borrowed from uiInteract.cpp
 * Pause for a while.  We want to put the program to sleep until it
 * is time to draw again.  Note that this requires us to tell the OS
 * that we are idle.  the nanosleep function performs this task for us
 *   INPUT: msSleep: sleep time in milliseconds
 *********************************************************************/
void mSleep(unsigned long msSleep)
{
   // Windows handles sleep one way
#ifdef _WIN32
   ::Sleep(msSleep + 35);

   // Unix-based operating systems (OS-X, Linux) do it another
#else // LINUX, XCODE
   timespec req = {};
   time_t sec = (int)(msSleep / 1000);
   msSleep -= (sec * 1000);

   req.tv_sec = sec;
   req.tv_nsec = msSleep * 1000000L;

   while (nanosleep(&req, &req) == -1)
      ;
#endif // LINUX, XCODE
   return;
}

/*************************************************************************
 * Constructor: Game()
 * Purpose: Set's all the initial values for the game.
 ************************************************************************/
Game :: Game(Point tl, Point br) : topLeft(tl), bottomRight(br)
{
   mainMenu.setMenuState(true);
   mainMenu.addMenuItem("(R) Run Game");
   mainMenu.addMenuItem("(S) Score Screen");
   mainMenu.addMenuItem("(X) Exit Game");
   mainMenu.setTitle("Asteroids");
   // Set our pause menu to be hidden.
   pauseMenu.setMenuState(false);
   // Initialize our pause menu itmes.
   pauseMenu.addMenuItem("(R) Resume Game");
   pauseMenu.addMenuItem("(M) Main Menu");
   pauseMenu.addMenuItem("(X) Exit Game");
   pauseMenu.setTitle("Game Paused");
   
   scoreScreen.setScoreScreenState(false);
   
   gameOverState = false;
   isHighScore = false;
   score = 0;
   numAsteroids = 0;
   round = 1;
   lives = 3;
   livesFrameCount = 0;
   //createAsteroids();
   
   ship = new Ship(Point(0,0));
}

/*************************************************************************
 * Method: handleInput()
 * Purpose: Handles all keyboard input allowing user to navigate various
 *    menus as well as play the game.
 ************************************************************************/
void Game :: handleInput(const Interface & ui)
{
      // Handle user input while in the main menu.
   if (mainMenu.getMenuState() && !pauseMenu.getMenuState() && !gameOverState)
   {
      if (ui.isUp())
      {
         mainMenu.setSelection(-1);
         mSleep(200); // Pause for a bit so we don't navigate to fast
      }
      if (ui.isDown())
      {
         mainMenu.setSelection(1);
         mSleep(200); // Pause for a bit so we don't navigate to fast
      }
      if (ui.isReturn())
      {
         if (mainMenu.getSelection() == 1)
         {
         
         }
         else if (mainMenu.getSelection() == 2)
         {
            scoreScreen.setScoreScreenState(true);
         }
         else
         {
            // Exit the program.
            exit(0);
         }
         mainMenu.setMenuState(false);
      }
      if (ui.isS())
      {
         scoreScreen.setScoreScreenState(true);
         mainMenu.setMenuState(false);
      }
      if (ui.isR())
      {
      
         mainMenu.setMenuState(false);
      }
      if (ui.isX())
         // Exit the Program
         exit(0);
   
   }
   else if (pauseMenu.getMenuState() && !mainMenu.getMenuState() && !gameOverState)
   {
      if (ui.isUp())
      {
         pauseMenu.setSelection(-1);
         mSleep(200); // Pause for a bit so we don't navigate to fast
      }
      if (ui.isDown())
      {
         pauseMenu.setSelection(1);
         mSleep(200); // Pause for a bit so we don't navigate to fast
      }
      if (ui.isR())
      {
         pauseMenu.setMenuState(false);
      }
      if (ui.isM())
      {
         resetGame();
      }
      if (ui.isReturn())
      {
         if (pauseMenu.getSelection() == 1)
         {
            pauseMenu.setMenuState(false);
         }
         else if (pauseMenu.getSelection() == 2)
         {
            resetGame();
         }
         else
         {
            exit(0);
         }
      }
      if (ui.isX())
      {
         exit(0);
      }
   }
   else if (gameOverState)
   {
      if (isHighScore)
      {
         scoreScreen.scoreInteract(ui);
      }
      if (ui.isReturn())
      {
         resetGame();
      }
   }
   else if (scoreScreen.scoreScreenState())
   {
   
      if (ui.isReturn())
      {
         scoreScreen.setScoreScreenState(false);
         mainMenu.setMenuState(true);
      }
   }
   else
   {
      if (ui.isPause())
      {
         pauseMenu.setMenuState(true);
         mainMenu.setMenuState(false);
         mSleep(200);
      }
      if (ship != NULL)
      {
         if (ui.isLeft())
         {
            ship->rotateLeft();
         }
         if (ui.isRight())
         {
            ship->rotateRight();
         }
         if (ui.isUp())
         {
            ship->addThrust();
         }
         if (ui.isSpace())
         {
            if (livesFrameCount == 0)
            {
               Bullet* newBullet;
               newBullet = new Bullet;
               newBullet->fire(ship->getPoint(), ship->getAngle());
            
               bullets.push_back(newBullet);
            }
         }
      }
   }
}

/*************************************************************************
 * Method: resetGame()
 * Purpose: reset's the game values.
 ************************************************************************/
void Game :: resetGame()
{
   if (isHighScore)
      scoreScreen.setScore(score);
   score = 0;
   numAsteroids = 0;
   round = 1;
   lives = 3;
   ship = new Ship;
   deleteAsteroids();
   //createAsteroids();
   gameOverState = false;
   isHighScore = false;
   mainMenu.setMenuState(true);
   pauseMenu.setMenuState(false);
   ship->setPoint(Point(0, 0));
   ship->resetVelocity();
   for (vector<Bullet*> :: iterator it = bullets.begin(); it != bullets.end();)
   {
      delete (*it);
      (*it) = NULL;
      bullets.erase(it);
   }
}

/*************************************************************************
 * Method: deleteAsteroids()
 * Purpose: delete's all asteroids in the asteroids vector.
 ************************************************************************/
void Game :: deleteAsteroids()
{
   for (vector<Rock*> :: iterator it = asteroids.begin(); it != asteroids.end();)
   {
      if ((*it) != NULL)
      {
         delete (*it);
         (*it) = NULL;
         asteroids.erase(it);
      }
      else
      {
         ++it;
      }
   }
}

/*************************************************************************
 * Method: createAsteroids()
 * Purpose: creates new asteroids, and add's one new asteroid every 3 rounds.
 ************************************************************************/
void Game :: createAsteroids()
{
   // We add addtional asteroids every 3 rounds to increase difficulty.
   if (!(round % 3))
   {
      numAsteroids++;
   }
   for (int i = 0; i < 2 + numAsteroids; i++)
   {
      // We wan't the asteroids to not spawn in the middle of the screen where
      // out ship is and end the game before it's began, so we do some math to
      // create a safe zone that the asteroids won't spawn in.
      int x = random(50, 200);
      int y = random(50, 200);
      int negX = random(1, 3);
      int negY = random(1, 3);
      x *= (negX == 1? -1 : 1);
      y *= (negY == 1? -1 : 1);
      asteroids.push_back(new BigRock(Point(x, y)));
   }
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX()
      && point.getX() <= bottomRight.getX()
      && point.getY() >= bottomRight.getY()
      && point.getY() <= topLeft.getY());
}

/*************************************************************************
 * Method: advance()
 * Purpose: Advances the game
 ************************************************************************/
void Game :: advance()
{
   // Added to handle the display of a menu
   // Display's main menu if the menu state is on.
   if (this->mainMenu.getMenuState())
   {
      mainMenu.drawMenu();
   }
   // Display's the pause menu if the pause menu state is on.
   else if (this->pauseMenu.getMenuState())
   {
      pauseMenu.drawMenu();
   }
   // Display the Score Screen
   else if (this->scoreScreen.scoreScreenState())
   {
      scoreScreen.drawScoreScreen();
   }
   // Display screen that allows the user to enter their initials
   else if (isHighScore)
   {
      scoreScreen.drawGetInitials();
   }
   else
   {
      advanceAsteroids();
      advanceBullets();
   
      if (ship != NULL)
         advanceShip();
   
      cleanUpZombies();
      if (asteroids.size() == 0)
      {
         round++;
         createAsteroids();
      }
   
      if (scoreScreen.checkHighScore(score) && ship == NULL)
      {
         gameOverState = true;
         isHighScore = true;
      }
   }
}

/*************************************************************************
 * Method: advanceShip()
 * Purpose: Advances the ship.
 ************************************************************************/
void Game :: advanceShip()
{
   ship->setPoint((wrapScreen(ship->getPoint())));
   ship->advance(ship->getAngle());
}

/*************************************************************************
 * Method: advanceBullets()
 * Purpose: Advances bullets.
 ************************************************************************/
void Game :: advanceBullets()
{
   for (vector<Bullet*> :: iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
   {
      if ((*bulletIt)->isAlive())
      {
         (*bulletIt)->setPoint(wrapScreen((*bulletIt)->getPoint()));
         (*bulletIt)->advance();
      }
   }
}

/*************************************************************************
 * Method: wrapScreen()
 * Purpose: Checks if an object has reached the edge of the screen and moves
 *   it to the opposite edge.
 ************************************************************************/
Point Game :: wrapScreen(Point point)
{
   if (!isOnScreen(point))
   {
      Point tempPoint = point;
      int tempX = tempPoint.getX();
      int tempY = tempPoint.getY();
   
      // Check if object has left the screen
   
      // left side
      if (tempPoint.getX() <= (topLeft.getX() - OFF_SCREEN))
      {
      
         tempX = bottomRight.getX() + OFF_SCREEN;
         return (Point(tempX, tempY));
      }
   
      // right side
      if (tempPoint.getX() >= (bottomRight.getX() + OFF_SCREEN))
      {
      
         tempX = topLeft.getX() - OFF_SCREEN;
         return (Point(tempX, tempY));
      }
      // top side
      if (tempPoint.getY() >= (topLeft.getY() + OFF_SCREEN))
      {
      
         tempY = bottomRight.getY() - OFF_SCREEN;
         return (Point(tempX, tempY));
      }
   
      // bottom side
      if (tempPoint.getY() <= (bottomRight.getY() - OFF_SCREEN))
      {
      
         tempY = topLeft.getY() + OFF_SCREEN;
         return (Point(tempX, tempY));
      }
   }
   return point;
}

/*************************************************************************
 * Method: advanceAsteroids()
 * Purpose: detects bullet and ship collisions and advances the asteriods
 *    across the screen.
 ************************************************************************/
void Game :: advanceAsteroids()
{
   
   for (vector<Rock*> :: iterator it = asteroids.begin(); it != asteroids.end(); ++it)
   {
      (*it)->setPoint(wrapScreen((*it)->getPoint()));
      (*it)->advance();
   
      // Check for collsion between ship and asteroids
      if (ship != NULL && livesFrameCount == 0)
      {
         // If hit and we have lives left we stop checking for hits for 40 frames
         // to allow our asteroids to move clear and give the new ship a clear spot
         // to respawn to.
         if (getClosestDistance(*(*it), *ship) < (*it)->getSize())
         {
            lives--;
            // check if we have any lives left.
            if (lives != 0)
            {
               // becaues we're in a loop of asteroids we must multiple
               // 40 by the number of asteroids to get an accurate count
               // of 40 frames until respawn.
               livesFrameCount = int(40 * asteroids.size());
            
               // Reset the ship to the center of the screen with 0 velocity.
               ship->setPoint(Point(0,0));
               ship->resetVelocity();
            
            }
            else
            {
               gameOverState = true;
               ship->kill();
            }
         }
      }
      // count down from 40
      else if (livesFrameCount > 0)
      {
         livesFrameCount--;
      }
   
      bool hit = false;
   
      // Check for collision between bullet and asteroids
      for (vector<Bullet*> :: iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
      {
         if ((*bulletIt)->isAlive())
         {
            if (getClosestDistance(*(*it), *(*bulletIt)) < (*it)->getSize())
            {
               hit = true;
               (*bulletIt)->kill();
               (*bulletIt)->setPoint(Point(500,500));
            }
         }
      }
      
      if (hit)
      {
         score += (*it)->hit();
      
         // create new medium rocks
         if (strcmp((*it)->getName().c_str(), "BigRock") == 0)
         {
            Velocity up = (*it)->getVelocity();
            Velocity down = (*it)->getVelocity();
            Velocity right = (*it)->getVelocity();
            up.setDy(1);
            down.setDy(-2);
            right.setDx(2);
            asteroids.push_back(new MediumRock((*it)->getPoint(), up));
            asteroids.push_back(new MediumRock((*it)->getPoint(), down));
            asteroids.push_back(new SmallRock((*it)->getPoint(), right));
         }
         
         // create new small rocks
         else if (strcmp((*it)->getName().c_str(), "MediumRock") == 0)
         {
            Velocity left = (*it)->getVelocity();
            Velocity right = (*it)->getVelocity();
         
            left.setDx(-3);
            right.setDx(3);
            asteroids.push_back(new SmallRock((*it)->getPoint(), left));
            asteroids.push_back(new SmallRock((*it)->getPoint(), right));
         }
      
         hit = false;
         break;
      }
   
   }
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // Check's for dead asteroids and deletes them.
   for (vector<Rock*> :: iterator it = asteroids.begin(); it != asteroids.end(); )
   {
      if (!(*it)->isAlive())
      {      
         
         delete (*it);
         (*it) = NULL;
         
         asteroids.erase(it);
      }
      else
      {
         ++it;
      }
   }
   
   // If the ship is dead, we delete it.
   if (ship != NULL)
      if (!ship->isAlive())
      {
         delete ship;
         ship = NULL;
      }
   
   // Look for dead bullets
   vector<Bullet*>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      if (!(*bulletIt)->isAlive())
      {
         delete (*bulletIt);
         (*bulletIt) = NULL;
      
         // remove from list and advance
         bullets.erase(bulletIt);
      }
      else
      {
         ++bulletIt; // advance
      }
   }
   
}

/*************************************************************************
 * Method: draw()
 * Purpose: Draw's the ship, asteroids, bullets, and game header text.
 ************************************************************************/
void Game :: draw(const Interface &ui)
{
   // Verifies that a menu is not currently active.
   if (!mainMenu.getMenuState() && !pauseMenu.getMenuState() &&
       !scoreScreen.scoreScreenState() && !gameOverState)
   {
      // Iteratates through our asteroids and draws them on the screen.
      for (vector<Rock*> :: iterator it = asteroids.begin(); it != asteroids.end(); ++it)
      {
         (*it)->draw();
      }
   
      // Draws our ship on the screen if it's alive.
      if (ship != NULL && livesFrameCount == 0)
         ship->draw();
   
      // Iterates through our bullets and draws them on the screen.
      for (vector<Bullet*> :: iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
      {
         if ((*bulletIt)->isAlive())
         {
         
            (*bulletIt)->draw();
         }
      }
   }
   
   // Draw's our game over message.
   else if (gameOverState)
   {
      drawText(Point(-50, -5), "GAME OVER");
      drawText(Point(-50, -20), "Press Enter to Continue");
   }
   
   // Draw's our game header.
   if (!mainMenu.getMenuState() && !scoreScreen.scoreScreenState())
   {
      // Put the score on the screen
      Point scoreLocation;
      scoreLocation.setX(topLeft.getX() + 60);
      scoreLocation.setY(topLeft.getY() - 5);
      drawText(Point(topLeft.getX() + 5, topLeft.getY() - 15), "SCORE:");
      drawNumber(scoreLocation, score);
   
      // Put's the round on the screen.
      Point roundLocation;
      roundLocation.setX(topLeft.getX() + 220);
      roundLocation.setY(topLeft.getY() - 5);
      drawText(Point(topLeft.getX() + 170, topLeft.getY() - 15), "ROUND:");
      drawNumber(roundLocation, round);
   
      // Put's the lives on the screen.
      Point livesTextLocation;
      livesTextLocation.setX(topLeft.getX() + 300);
      livesTextLocation.setY(topLeft.getY() - 15);
      drawText(livesTextLocation, "LIVES:");
   
      // Put's the number of ships left on the screen.
      Point livesPoint;
      livesPoint.setX(topLeft.getX() + 380);
      livesPoint.setY(topLeft.getY() - 10);
      for (int i = 0; i < lives; i++)
      {
         drawShip(livesPoint, 185);
         livesPoint.setX(livesPoint.getX() - 15);
      }

   }
}


