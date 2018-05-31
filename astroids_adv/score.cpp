//
//  score.cpp
//  skeet_adv
//
//  Created by Chris Carrick on 3/4/18.
//  Copyright © 2018 Chris Carrick. All rights reserved.
//

#include "score.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>

//#include <stdio.h>
#include <time.h>     // for clock


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

#include "point.h"
#include "uiDraw.h"

using namespace std;

/*************************************************************************
 * Constructor: Score()
 * Purpose: Default constructor for the SCORE class.
 ************************************************************************/
Score :: Score()
      {
         static char blank[] = "   ";
         pHighScores = new ScoreStruct[MAX_SCORES];
         for (int i = 0; i < MAX_SCORES; i++)
         {
            //for (int j = 0; j < 3; j++)
               strcpy(pHighScores[i].initials, blank);
               cout << pHighScores[i].initials << endl;
            pHighScores[i].score = 0;
         }
         numScores = 0;
         charPosition = 0;
         if (checkFile())
         {
            readFile();
         }
         else
         {
            // delete corrupt files
            remove(FILE_NAME);
         }
         state = false;
      }

/*************************************************************************
 * Method: getScores()
 * Purpose: Returns our scores structure.
 ************************************************************************/
ScoreStruct* Score :: getScores()
{
   return this->pHighScores;
}

/*************************************************************************
 * Method: setScore()
 * Purpose: Used to save a new high score.
 ************************************************************************/
void Score :: setScore(int score)
{
   ScoreStruct tempScore = pHighScores[0];
   ScoreStruct tempScore1;
   bool setNewScore = false;
   // Shift scores up one
   for (int i = 0; i < MAX_SCORES; i++)
   {
      if ((i + 1) != MAX_SCORES) // Ensure we dont read off the end of our array
      {
         if (score > pHighScores[i].score)
         {
            // Check to see if we've saved the new score yet
            if (!setNewScore)
            {
               tempScore = pHighScores[i];
               for (int j = 0; j < 3; j++)
               {
                  pHighScores[i].initials[j] = newInitials[j];
               }
               pHighScores[i].score = score;
               setNewScore = true;
            }
         
            tempScore1 = pHighScores[i + 1];
            pHighScores[i + 1] = tempScore;
            tempScore = tempScore1;
         
         
         }
      }
   }
   // Clear our input buffer for the initials
   for (int i = 0; i < 3; i++)
      newInitials[i] = ' ';
   charPosition = 0;
   // Update the number elements in our array
   numScores++;
   
   // Write our new scores to our save file
   writeFile();
}

/*************************************************************************
 * Method: checkHighScore()
 * Purpose: Used to see if our score is a new high score.
 ************************************************************************/
bool Score :: checkHighScore(int score)
{
   if (score > 0)
   {
      if (numScores == 0)
      {
         return true;
      }
      for (int i = 0; i < MAX_SCORES; i++)
      {
         if (score > pHighScores[i].score)
         {
         
            return true;
         }
      }
   }
   return false;
}

/*************************************************************************
 * Method: drawGetInitials()
 * Purpose: In the event of a high score, this draw's an input screen allowing
 *    the user to input their intials.
 ************************************************************************/
void Score :: drawGetInitials()
{
   drawText(Point(-50, 50), "Congragulations!");
   drawText(Point(-50, 35), "Enter Your 3 Digit Initials");
   
   // Draw Lines
   drawLine(Point(0, -50), Point(20, -50));
   drawLine(Point(25, -50), Point(45, -50));
   drawLine(Point(50, -50), Point(70, -50));
   
   char one = newInitials[0];
   char two = newInitials[1];
   char three = newInitials[2];
   
   drawText(Point(8, -45), string(1, one).c_str());
   drawText(Point(33, -45), string(1, two).c_str());
   drawText(Point(58, -45), string(1, three).c_str());
   
}

/*************************************************************************
 * Method: drawScoreScreen()
 * Purpose: Draw's our Score Screen.
 ************************************************************************/
void Score :: drawScoreScreen()
{
   drawText(Point(-90, 160), "Score Screen! Press (Return) to go back.");
   int yValue = 110;
   for (int i = 0; i < MAX_SCORES; i++)
   {
      drawText(Point(-50, yValue - 17), pHighScores[i].initials);
      //char a = pHighScores[i].score;
      //string b(1, a);
   
      stringstream getScore;
      getScore << pHighScores[i].score;
      string score = getScore.str();
      if (pHighScores[i].score != 0)
         drawText(Point(0, yValue -= 17), score.c_str());
   }
}

/*************************************************************************
 * Method: scoreScreenState()
 * Purpose: Returns the state of our score screen.
 ************************************************************************/
bool Score :: scoreScreenState()
{
   return this->state;
}

/*************************************************************************
 * Method: setScoreScreenState()
 * Purpose: Sets the score screen state.
 ************************************************************************/
void Score :: setScoreScreenState(bool state)
{
   this->state = state;
}

/*************************************************************************
 * Method: checkFile()
 * Purpose: Used to verify our file is not corrupt before saving the contents
 *    of our file.
 ************************************************************************/
bool Score :: checkFile()
{
   ifstream fin(FILE_NAME);
   ScoreStruct tempScores[MAX_SCORES];
   if (fin.fail())
   {
      return false;
   }
   
   int i = 0;
   while(!fin.eof())
   {
      fin >> tempScores[i].initials;
      fin >> tempScores[i].score;
      i++;
   }
   
   fin.close();
   if (i > 2)
      for (int j = 0; j < i; j++)
      {
         if (tempScores[j].score < tempScores[j + 1].score)
         {
            return false;
         }
      }
   
   return true;
}

/*************************************************************************
 * Method: readFile()
 * Purpose: Used to read our save file when opening the game.
 ************************************************************************/
bool Score :: readFile()
{
   ifstream fin(FILE_NAME);
   
   if (fin.fail())
   {
      return false;
   }
   
   int i = 0;
   while (!fin.eof())
   {
      fin >> pHighScores[i].initials;
      fin >> pHighScores[i].score;
      i++;
      numScores++;
   }
   numScores--;
   
   fin.close();
   
   return true;
   
}

/*************************************************************************
 * Method: writeFile()
 * Purpose: Used to write all saved scores to a file.
 ************************************************************************/
bool Score :: writeFile()
{
   ofstream fout(FILE_NAME);

   if (fout.fail())
   {
     return false;
   }

   for (int i = 0; i < numScores; i++)
   {
      if (i < MAX_SCORES)
      {
         fout << pHighScores[i].initials << " ";
         fout << pHighScores[i].score << endl;
      }
   }

   fout.close();
   
   return true;
}

/*************************************************************************
 * Method: scoreInteract()
 * Purpose: Used to interact with key strokes when user is entering their initials.
 ************************************************************************/
void Score :: scoreInteract(const Interface & ui)
{
   
   if (charPosition < 3)
   {
      if (ui.isA())
      {
         newInitials[charPosition] = 'A';
         charPosition++;
      }
      if (ui.isB())
      {
         newInitials[charPosition] = 'B';
         charPosition++;
      }
      if (ui.isC())
      {
         newInitials[charPosition] = 'C';
         charPosition++;
      }
      if (ui.isD())
      {
         newInitials[charPosition] = 'D';
         charPosition++;
      }
      if (ui.isE())
      {
         newInitials[charPosition] = 'E';
         charPosition++;
      }
      if (ui.isF())
      {
         newInitials[charPosition] = 'F';
         charPosition++;
      }
      if (ui.isG())
      {
         newInitials[charPosition] = 'G';
         charPosition++;
      }
      if (ui.isH())
      {
         newInitials[charPosition] = 'H';
         charPosition++;
      }
      if (ui.isI())
      {
         newInitials[charPosition] = 'I';
         charPosition++;
      }
      if (ui.isJ())
      {
         newInitials[charPosition] = 'J';
         charPosition++;
      }
      if (ui.isK())
      {
         newInitials[charPosition] = 'K';
         charPosition++;
      }
      if (ui.isL())
      {
         newInitials[charPosition] = 'L';
         charPosition++;
      }
      if (ui.isM())
      {
         newInitials[charPosition] = 'M';
         charPosition++;
      }
      if (ui.isN())
      {
         newInitials[charPosition] = 'N';
         charPosition++;
      }
      if (ui.isO())
      {
         newInitials[charPosition] = 'O';
         charPosition++;
      }
      if (ui.isP())
      {
         newInitials[charPosition] = 'P';
         charPosition++;
      }
      if (ui.isQ())
      {
         newInitials[charPosition] = 'Q';
         charPosition++;
      }
      if (ui.isR())
      {
         newInitials[charPosition] = 'R';
         charPosition++;
      }
      if (ui.isS())
      {
         newInitials[charPosition] = 'S';
         charPosition++;
      }
      if (ui.isT())
      {
         newInitials[charPosition] = 'T';
         charPosition++;
      }
      if (ui.isU())
      {
         newInitials[charPosition] = 'U';
         charPosition++;
      }
      if (ui.isV())
      {
         newInitials[charPosition] = 'V';
         charPosition++;
      }
      if (ui.isW())
      {
         newInitials[charPosition] = 'W';
         charPosition++;
      }
      if (ui.isX())
      {
         newInitials[charPosition] = 'X';
         charPosition++;
      }
      if (ui.isY())
      {
         newInitials[charPosition] = 'Y';
         charPosition++;
      }
      if (ui.isZ())
      {
         newInitials[charPosition] = 'Z';
         charPosition++;
      }
   }
   if (charPosition > 0)
   {
      if (ui.isDelete())
      {
         newInitials[charPosition-1] = ' ';
         charPosition--;
      }
   
      // backspace
   }
   
}
