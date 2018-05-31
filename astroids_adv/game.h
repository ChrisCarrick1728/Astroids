

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include "menu.h"
#include "score.h"
#include <string>


#define CLOSE_ENOUGH 15
#define GAME_OVER 2
#define OFF_SCREEN 16
#define SHIP_SIZE 10


/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
   public:
      /*********************************************
       * Constructor
       * Initializes the game
       *********************************************/
      Game(Point tl, Point br);
      ~Game(){};
   
      /*********************************************
       * Function: handleInput
       * Description: Takes actions according to whatever
       *  keys the user has pressed.
       *********************************************/
      void handleInput(const Interface & ui);
   
      /*********************************************
       * Function: advance
       * Description: Move everything forward one
       *  step in time.
       *********************************************/
      void advance();
      void advanceAsteroids();
      void advanceBullets();
      void advanceShip();
      Point wrapScreen(Point point);
      float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
      void cleanUpZombies();
      void deleteAsteroids();
      void createAsteroids();
      void resetGame();
   
      /*********************************************
       * Function: draw
       * Description: draws everything for the game.
       *********************************************/
      void draw(const Interface & ui);
   
      bool isOnScreen(const Point & point);
   
   private:
      // The coordinates of the screen
      Point topLeft;
      Point bottomRight;
   
      // Create our objects
      Ship *ship;
      std::vector<Rock*> asteroids;
      std::vector<Bullet*> bullets;
   
      // Set up our Menus
      Menu mainMenu;
      Menu pauseMenu;
      Score scoreScreen;
   
      // Game state variables
      bool gameOverState;
      bool isHighScore;
      int score;
      int round;
      int numAsteroids;
      int lives;
      int livesFrameCount;
};

#endif /* GAME_H */

