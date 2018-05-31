//
//  score.h
//  skeet_adv
//
//  Created by Chris Carrick on 3/4/18.
//  Copyright © 2018 Chris Carrick. All rights reserved.
//
#include "uiInteract.h"
#include <iostream>
#ifndef score_h
#define score_h

#define MAX_SCORES 10
#define FILE_NAME "skeet_score.skeet"

#include <stdio.h>

struct ScoreStruct
{
   char initials[3];
   int  score;
};

class Score
{
   public:
   
      Score();
      ~Score()
      {
         writeFile();
         delete pHighScores;
      }
   
      ScoreStruct* getScores();
      void         setScore(int score);
      bool         checkHighScore(int score);
      void         drawScoreScreen();
      bool         scoreScreenState();
      void         setScoreScreenState(bool state);
      void         scoreInteract(const Interface & ui);
      void         drawGetInitials();
   
   
   private:
      bool         checkFile();
      bool         readFile();
      bool         writeFile();
   
   
      ScoreStruct  *pHighScores;
      bool state;
      char newInitials[3];
      int  charPosition;
      int  numScores;
      
};

#endif /* score_h */
