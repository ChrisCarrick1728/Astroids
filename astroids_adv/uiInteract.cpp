/***********************************************************************
 * Source File:
 *     UI INTERACT
 * Author:
 *     Br. Helfrich
 * Description:
 *     Implement the interfaces specified in uiInterface.h.  This handles
 *     all the interfaces and events necessary to work with OpenGL.  Your
 *     program will interface with this thorough the callback function
 *     pointer towards the bottom of the file.
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock
#include <cstdlib>    // for rand()


#ifdef __APPLE__
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>    // Main OpenGL library
#include <GL/glut.h>  // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <Gl/glut.h>           // OpenGL library we copied
#include <ctime>            // for ::Sleep();
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "uiInteract.h"
#include "point.h"

using namespace std;


/*********************************************************************
 * SLEEP
 * Pause for a while.  We want to put the program to sleep until it
 * is time to draw again.  Note that this requires us to tell the OS
 * that we are idle.  the nanosleep function performs this task for us
 *   INPUT: msSleep: sleep time in milliseconds
 *********************************************************************/
void sleep(unsigned long msSleep)
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

/************************************************************************
 * DRAW CALLBACK
 * This is the main callback from OpenGL. It gets called constantly by
 * the graphics engine to refresh and draw the window.  Here we will
 * clear the background buffer, draw on it, and send it to the forefront
 * when the appropriate time period has passsed.
 *
 * Note: This and all other callbacks can't be member functions, they must
 * have global scope for OpenGL to see them.
 *************************************************************************/
void drawCallback()
{
   // even though this is a local variable, all the members are static
   Interface ui;
   // Prepare the background buffer for drawing
   glClear(GL_COLOR_BUFFER_BIT); //clear the screen
   glColor3f(1,1,1);
   
   //calls the client's display function
   assert(ui.callBack != NULL);
   ui.callBack(&ui, ui.p);
   
   //loop until the timer runs out
   if (!ui.isTimeToDraw())
      sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));

   // from this point, set the next draw time
   ui.setNextDrawTime();

   // bring forth the background buffer
   glutSwapBuffers();

   // clear the space at the end
   ui.keyEvent();
}

/************************************************************************
 * KEY DOWN CALLBACK
 * When a key on the keyboard has been pressed, we need to pass that
 * on to the client.  Currently, we are only registering the arrow keys
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyDownCallback(int key, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(key, true /*fDown*/);
}

/************************************************************************
 * KEY UP CALLBACK
 * When the user has released the key, we need to reset the pressed flag
 *   INPUT   key:   the key we pressed according to the GLUT_KEY_ prefix
 *           x y:   the position in the window, which we ignore
 *************************************************************************/
void keyUpCallback(int key, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(key, false /*fDown*/);
}

/***************************************************************
 * KEYBOARD CALLBACK
 * Generic callback to a regular ascii keyboard event, such as
 * the space bar or the letter 'q'
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y)
{
   // Even though this is a local variable, all the members are static
   // so we are actually getting the same version as in the constructor.
   Interface ui;
   ui.keyEvent(key, true /*fDown*/);
}

/***************************************************************
 * INTERFACE : KEY EVENT
 * Either set the up or down event for a given key
 *   INPUT   key     which key is pressed
 *           fDown   down or brown
 ****************************************************************/
void Interface::keyEvent(int key, bool fDown)
{
   switch(key)
   {
      case 'a':
      case 'A':
         isAPress = fDown;
         break;
      case 'b':
      case 'B':
         isBPress = fDown;
         break;
      case 'c':
      case 'C':
         isCPress = fDown;
         break;
      case 'd': // Same as glut_key_left
      case 'D':
         isLeftPress = fDown;
         isDPress = fDown;
         break;
      case 'e': // Same as glut_key_up
      case 'E':
         isUpPress = fDown;
         isEPress = fDown;
         break;
      case 'f': // Same as glut_key_right
      case 'F':
         isRightPress = fDown;
         isFPress = fDown;
         break;
      case 'g': // Same as glut_key_down
      case 'G':
         isDownPress = fDown;
         isGPress = fDown;
         break;
      case 'h':
      case 'H':
         isHPress = fDown;
         break;
      case 'i':
      case 'I':
         isIPress = fDown;
         break;
      case 'j':
      case 'J':
      case ' ':
         isSpacePress = fDown;
         isJPress = fDown;
         break;
      case 'k':
      case 'K':
         isKPress = fDown;
         break;
      case 'l':
      case 'L':
         isLPress = fDown;
         break;
      case 'm':
      case 'M':
         isMPress = fDown;
         break;
      case 'n':
      case 'N':
         isNPress = fDown;
         break;
      case 'o':
      case 'O':
         isOPress = fDown;
         break;
      case 'p':
      case 'P':
         isPausePress = fDown;
         isPPress = fDown;
         break;
      case 'q':
      case 'Q':
         isQPress = fDown;
         break;
      case 'r':
      case 'R':
         isRPress = fDown;
         break;
      case 's':
      case 'S':
         isSPress = fDown;
         break;
      case 't':
      case 'T':
         isTPress = fDown;
         break;
      case 'u':
      case 'U':
         isUPress = fDown;
         break;
      case 'v':
      case 'V':
         isVPress = fDown;
         break;
      case 'w':
      case 'W':
         isWPress = fDown;
         break;
      case 'x':
      case 'X':
         isXPress = fDown;
         break;
      case 'y':
      case 'Y':
         isYPress = fDown;
         break;
      case 'z':
      case 'Z':
         isZPress = fDown;
         break;
      //case GLUT_KEY_DOWN:
      //   isDownPress = fDown;
      //   break;
      //case GLUT_KEY_UP:
      //   isUpPress = fDown;
      //   break;
      //case GLUT_KEY_RIGHT:
      //   isRightPress = fDown;
      //   break;
      //case GLUT_KEY_LEFT:
      //   isLeftPress = fDown;
      //   break;
      case 13: //Return Key
         isReturnPress = fDown;
         break;
      case 127:
         isDeletePress = fDown;
         break;
      //case GLUT_KEY_HOME:
      //case ' ':
      //   isSpacePress = fDown;
      //   break;
   }
}
/***************************************************************
 * INTERFACE : KEY EVENT
 * Either set the up or down event for a given key
 *   INPUT   key     which key is pressed
 *           fDown   down or brown
 ****************************************************************/
void Interface::keyEvent()
{
   if (isDownPress)
      isDownPress++;
   if (isUpPress)
      isUpPress++;
   if (isLeftPress)
      isLeftPress++;
   if (isRightPress)
      isRightPress++;
   if (isReturnPress)
      isReturnPress = false;
   if (isDeletePress)
      isDeletePress = false;
   if (isPausePress)
      isPausePress  = false;
   if (isAPress)
      isAPress      = false;
   if (isBPress)
      isBPress      = false;
   if (isCPress)
      isCPress      = false;
   if (isDPress)
      isDPress      = false;
   if (isEPress)
      isEPress      = false;
   if (isFPress)
      isFPress      = false;
   if (isGPress)
      isGPress      = false;
   if (isHPress)
      isHPress      = false;
   if (isIPress)
      isIPress      = false;
   if (isJPress)
      isJPress      = false;
   if (isKPress)
      isKPress      = false;
   if (isLPress)
      isLPress      = false;
   if (isMPress)
      isMPress      = false;
   if (isNPress)
      isNPress      = false;
   if (isOPress)
      isOPress      = false;
   if (isPPress)
      isPPress      = false;
   if (isQPress)
      isQPress      = false;
   if (isRPress)
      isRPress      = false;
   if (isSPress)
      isSPress      = false;
   if (isTPress)
      isTPress      = false;
   if (isUPress)
      isUPress      = false;
   if (isVPress)
      isVPress      = false;
   if (isWPress)
      isWPress      = false;
   if (isXPress)
      isXPress      = false;
   if (isYPress)
      isYPress      = false;
   if (isZPress)
      isZPress      = false;
   isSpacePress     = false;
}


/************************************************************************
 * INTEFACE : IS TIME TO DRAW
 * Have we waited long enough to draw swap the background buffer with
 * the foreground buffer?
 *************************************************************************/
bool Interface::isTimeToDraw()
{
   return ((unsigned int)clock() >= nextTick);
}

/************************************************************************
 * INTERFACE : SET NEXT DRAW TIME
 * What time should we draw the buffer again?  This is a function of
 * the current time and the frames per second.
 *************************************************************************/
void Interface::setNextDrawTime()
{
   nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

/************************************************************************
 * INTERFACE : SET FRAMES PER SECOND
 * The frames per second dictates the speed of the game.  The more frames
 * per second, the quicker the game will appear to the user.  We will default
 * to 30 frames/second but the client can set this at will.
 *    INPUT  value        The number of frames per second.  30 is default
 *************************************************************************/
void Interface::setFramesPerSecond(double value)
{
    timePeriod = (1 / value);
}

/***************************************************
 * STATICS
 * All the static member variables need to be initialized
 * Somewhere globally.  This is a good spot
 **************************************************/
int          Interface::isDownPress   = 0;
int          Interface::isUpPress     = 0;
int          Interface::isLeftPress   = 0;
int          Interface::isRightPress  = 0;
bool         Interface::isSpacePress  = false;
bool         Interface::isReturnPress = false;
bool         Interface::isDeletePress = false;
bool         Interface::isPausePress  = false;
bool         Interface::isAPress      = false;
bool         Interface::isBPress      = false;
bool         Interface::isCPress      = false;
bool         Interface::isDPress      = false;
bool         Interface::isEPress      = false;
bool         Interface::isFPress      = false;
bool         Interface::isGPress      = false;
bool         Interface::isHPress      = false;
bool         Interface::isIPress      = false;
bool         Interface::isJPress      = false;
bool         Interface::isKPress      = false;
bool         Interface::isLPress      = false;
bool         Interface::isMPress      = false;
bool         Interface::isNPress      = false;
bool         Interface::isOPress      = false;
bool         Interface::isPPress      = false;
bool         Interface::isQPress      = false;
bool         Interface::isRPress      = false;
bool         Interface::isSPress      = false;
bool         Interface::isTPress      = false;
bool         Interface::isUPress      = false;
bool         Interface::isVPress      = false;
bool         Interface::isWPress      = false;
bool         Interface::isXPress      = false;
bool         Interface::isYPress      = false;
bool         Interface::isZPress      = false;
bool         Interface::initialized   = false;
double       Interface::timePeriod    = 1.0 / 30; // default to 30 frames/second
unsigned int Interface::nextTick      = 0;        // redraw now please
void *       Interface::p             = NULL;
void (*Interface::callBack)(const Interface *, void *) = NULL;


/************************************************************************
 * INTERFACE : DESTRUCTOR
 * Nothing here!
 ***********************************************************************/
Interface::~Interface()
{
}


/************************************************************************
 * INTEFACE : INITIALIZE
 * Initialize our drawing window.  This will set the size and position,
 * get ready for drawing, set up the colors, and everything else ready to
 * draw the window.  All these are part of initializing Open GL.
 *  INPUT    argc:       Count of command-line arguments from main
 *           argv:       The actual command-line parameters
 *           title:      The text for the titlebar of the window
 *************************************************************************/
void Interface::initialize(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight)
{
   if (initialized)
      return;
   
   // set up the random number generator
   srand((unsigned int)time(NULL));

   // create the window
   glutInit(&argc, argv);
   Point point;
   glutInitWindowSize(   // size of the window
      (int)(bottomRight.getX() - topLeft.getX()),
      (int)(topLeft.getY() - bottomRight.getY()));
            
   glutInitWindowPosition( 10, 10);                // initial position 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
   glutCreateWindow(title);              // text on titlebar
   glutIgnoreKeyRepeat(true);
   
   // set up the drawing style: B/W and 2D
   glClearColor(0, 0, 0, 0);          // Black is the background color
   gluOrtho2D((int)topLeft.getX(), (int)bottomRight.getX(),
              (int)bottomRight.getY(), (int)topLeft.getY()); // 2D environment

   // register the callbacks so OpenGL knows how to call us
   glutDisplayFunc(   drawCallback    );
   glutIdleFunc(      drawCallback    );
   glutKeyboardFunc(  keyboardCallback);
   glutSpecialFunc(   keyDownCallback );
   glutSpecialUpFunc( keyUpCallback   );
   initialized = true;
   
   // done
   return;
}

/************************************************************************
 * INTERFACE : RUN
 *            Start the main graphics loop and play the game
 * INPUT callBack:   Callback function.  Every time we are beginning
 *                   to draw a new frame, we first callback to the client
 *                   to see if he wants to do anything, such as move
 *                   the game pieces or respond to input
 *       p:          Void point to whatever the caller wants.  You
 *                   will need to cast this back to your own data
 *                   type before using it.
 *************************************************************************/
void Interface::run(void (*callBack)(const Interface *, void *), void *p)
{
   // setup the callbacks
   this->p = p;
   this->callBack = callBack;

   glutMainLoop();

   return;
}

