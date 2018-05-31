/*************************************************************
 * File: menu.h
 * Author: Christopher Carrick
 *
 * Description: Contains the definition of the MENU class.
 *
 *************************************************************/
 
#ifndef menu_h
#define menu_h

#include <string>
#include <iostream>
#include "uiInteract.h"
#include "point.h"
#include "uiDraw.h"

class Menu
{
   public:
      Menu()
      {
         menuLocation.setX(-150);
         menuLocation.setY(30);
         titleLocation.setX(-38);
         titleLocation.setY(150);
         this->currentSelection = 1;
         setNumItems(0);
      }
      Menu(Point tl, Point br) : topLeft(tl), bottomRight(br)
      {
         menuLocation.setX(-150);
         menuLocation.setY(30);
         titleLocation.setX(-38);
         titleLocation.setY(150);
         setNumItems(0);
         this->currentSelection = 1;
      }
      
      void drawMenu();
   
      void addMenuItem(std::string menuItem);
   
      void setSelection(int upDown);
      void setTitle(std::string title);
      void setMenuState(bool menuState);
   
      int getMenuState();
      int getSelection();
      int getNumItems();
      string getTitle();
   
   private:
      std::string menuItems[10];
      std::string title;
      int numItems;
      int currentMenuItem;
      void setNumItems(int numItems);
      Point topLeft;
      Point bottomRight;
      Point menuLocation;
      Point titleLocation;
      bool menuState;
      int currentSelection;
};

#endif /* mainMenu_h */
