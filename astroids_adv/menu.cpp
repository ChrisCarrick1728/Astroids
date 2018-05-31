/*************************************************************
 * File: menu.cpp
 * Author: Christohper Carrick
 *
 * Description: Contains the implementations of the
 *  method bodies for the MENU class.
 *
 *************************************************************/

#include "menu.h"
#include <cassert>
#include <iostream>
using namespace std;

#ifdef __APPLE__
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

/*************************************************************************
 * Method: drawMenu()
 * Purpose: Draw's the menu on the screen taking into account which menu
 *    item is currently selected.
 ************************************************************************/
void Menu :: drawMenu()
{
   // Assign the title to a string variable that can then be convverted to
   // a c_string for the drawText function.
   string title = getTitle();
   
   // Set the color of the text to orange.
   glColor3f(1,0.5,0);
   
   // Display the title on the screen.
   drawText(titleLocation, title.c_str());
   
   // Loop through our menu items to display each object.
   for (int i = 0; i < getNumItems(); i++)
   {
      // Set the color to white
      glColor3f(1,1,1);
   
      // Set the color to green for the current selection
      if (i + 1 == getSelection())
         glColor3f(0,1,0);
   
      // Display the menu item
      drawText(menuLocation, menuItems[i].c_str());
      // Update the menu location for the next menu item.
      menuLocation.setY(menuLocation.getY() - 30);
   }
   // Reset back to the starting location.
   menuLocation.setY(30);
}

/*************************************************************************
 * Method: addMenuItem()
 * Purpose: Used to add menu items to an object.
 ************************************************************************/
void Menu :: addMenuItem(std::string menuItem)
{
   this->menuItems[getNumItems()] = menuItem;
   setNumItems(getNumItems() + 1);
   assert(numItems < 10);
}

/*************************************************************************
 * Method: setSelection()
 * Purpose: Used to keep track of which menu item is current selected.
 ************************************************************************/
void Menu :: setSelection(int upDown)
{
   if ((getSelection() > 0 && getSelection() <= getNumItems()) && (upDown == 1 || upDown == -1))
      this->currentSelection += upDown;
   if (getSelection() < 1)
      this->currentSelection = 1;
   if (getSelection() > getNumItems())
      this->currentSelection = getNumItems();
}

/*************************************************************************
 * Method: setTitle()
 * Purpose: Used to the set the title of the menu.
 ************************************************************************/
void Menu :: setTitle(std::string title)
{
   this->title = title;
}

/*************************************************************************
 * Method: getSelection()
 * Purpose: Returns the current menu selection.
 ************************************************************************/
int Menu :: getSelection()
{
   return this->currentSelection;
}

/*************************************************************************
 * Method: getNumItemes()
 * Purpose: Returns the number of menu items saved to our array.
 ************************************************************************/
int Menu :: getNumItems()
{
   return this->numItems;
}

/*************************************************************************
 * Method: getTitle()
 * Purpose: Returns the title of the menu.
 ************************************************************************/
string Menu :: getTitle()
{
   return this->title;
}

/*************************************************************************
 * Method: setNumItems()
 * Purpose: Used to set the number of items saved to our array.
 ************************************************************************/
void Menu :: setNumItems(int numItems)
{
   this->numItems = numItems;
}

/*************************************************************************
 * Method: setMenuState()
 * Purpose: Used to set the menu state to true or false (on or off)
 ************************************************************************/
void Menu :: setMenuState(bool menuState)
{
   this->menuState = menuState;
}

/*************************************************************************
 * Method: getMenuState()
 * Purpose: Returns the current menu state.
 ************************************************************************/
int Menu :: getMenuState()
{
   return this->menuState;
}
