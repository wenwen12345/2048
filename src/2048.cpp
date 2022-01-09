/*
    Implementation of the 2048 game.
*/

#include "2048.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include <vector>

// Namespace Begin
namespace Game2048 {

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Game Class Init Function
////////////////////////////////////////////////////////////////////////////////

Game::Game() {
  __gameMap = array<array<int, 4>, 4>{};
  __stepNum = 0;
  createNewNum();
}

////////////////////////////////////////////////////////////////////////////////
// Show
////////////////////////////////////////////////////////////////////////////////

void Game::show() const {
  initscr();
  cbreak();
  noecho();
  char strList[16][7];
  int idx = 0;

  for (auto i : __gameMap) {
    for (int j : i) {
      if (j) {
        sprintf(strList[idx], "  %-4d", j);
      } else {
        strcpy(strList[idx], "      ");
      }

      idx++;
    }
  }

  clear();

  printw(" ------ ------ ------ ------ \n");
  printw("|      |      |      |      |\n");
  printw("|%s|%s|%s|%s|\n", strList[0], strList[1], strList[2], strList[3]);
  printw("|      |      |      |      |\n");
  printw(" ------ ------ ------ ------ \n");
  printw("|      |      |      |      |\n");
  printw("|%s|%s|%s|%s|\n", strList[4], strList[5], strList[6], strList[7]);
  printw("|      |      |      |      |\n");
  printw(" ------ ------ ------ ------ \n");
  printw("|      |      |      |      |\n");
  printw("|%s|%s|%s|%s|\n", strList[8], strList[9], strList[10], strList[11]);
  printw("|      |      |      |      |\n");
  printw(" ------ ------ ------ ------ \n");
  printw("|      |      |      |      |\n");
  printw("|%s|%s|%s|%s|\n", strList[12], strList[13], strList[14], strList[15]);
  printw("|      |      |      |      |\n");
  printw(" ------ ------ ------ ------ \n");
  printw("\nStep: %d\n", __stepNum);
}

////////////////////////////////////////////////////////////////////////////////
// Create A New Number
////////////////////////////////////////////////////////////////////////////////

void Game::createNewNum() {
  vector<array<int, 2>> idxList;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (__gameMap[i][j] == 0) {
        idxList.push_back(array<int, 2>{i, j});
      }
    }
  }

  int listLen = idxList.size();

  srand(time(nullptr));
  int randIdx = rand() % listLen;

  __gameMap[idxList[randIdx][0]][idxList[randIdx][1]] = rand() % 2 + 1;
}

////////////////////////////////////////////////////////////////////////////////
// Press Left
////////////////////////////////////////////////////////////////////////////////

void Game::pressLeft() {
  bool moveBool = false;

  for (auto &numLine : __gameMap) {
    int tarIdx = 0;

    for (int idx = 1; idx < 4; idx++) {
      if (numLine[idx]) {
        if (numLine[tarIdx] == 0) {
          numLine[tarIdx] = numLine[idx];
          numLine[idx] = 0;
          moveBool = true;
        } else if (numLine[tarIdx] == numLine[idx]) {
          numLine[tarIdx] *= 2;
          numLine[idx] = 0;
          tarIdx++;
          moveBool = true;
        } else {
          tarIdx++;

          if (idx > tarIdx) {
            numLine[tarIdx] = numLine[idx];
            numLine[idx] = 0;
            moveBool = true;
          }
        }
      }
    }
  }

  afterPress(moveBool);
}

////////////////////////////////////////////////////////////////////////////////
// Press Right
////////////////////////////////////////////////////////////////////////////////

void Game::pressRight() {
  bool moveBool = false;

  for (auto &numLine : __gameMap) {
    int tarIdx = 3;

    for (int idx = 2; idx >= 0; idx--) {
      if (numLine[idx]) {
        if (numLine[tarIdx] == 0) {
          numLine[tarIdx] = numLine[idx];
          numLine[idx] = 0;
          moveBool = true;
        } else if (numLine[tarIdx] == numLine[idx]) {
          numLine[tarIdx] *= 2;
          numLine[idx] = 0;
          tarIdx--;
          moveBool = true;
        } else {
          tarIdx--;

          if (idx < tarIdx) {
            numLine[tarIdx] = numLine[idx];
            numLine[idx] = 0;
            moveBool = true;
          }
        }
      }
    }
  }

  afterPress(moveBool);
}

////////////////////////////////////////////////////////////////////////////////
// Press Up
////////////////////////////////////////////////////////////////////////////////

void Game::pressUp() {
  bool moveBool = false;

  for (int colIdx = 0; colIdx < 4; colIdx++) {
    array<int *, 4> numPtrList;

    for (int idx = 0; idx < 4; idx++) {
      numPtrList[idx] = &__gameMap[idx][colIdx];
    }

    int tarIdx = 0;

    for (int idx = 1; idx <= 3; idx++) {
      if (*numPtrList[idx]) {
        if (*numPtrList[tarIdx] == 0) {
          *numPtrList[tarIdx] = *numPtrList[idx];
          *numPtrList[idx] = 0;
          moveBool = true;
        } else if (*numPtrList[tarIdx] == *numPtrList[idx]) {
          *numPtrList[tarIdx] *= 2;
          *numPtrList[idx] = 0;
          tarIdx++;
          moveBool = true;
        } else {
          tarIdx++;

          if (idx > tarIdx) {
            *numPtrList[tarIdx] = *numPtrList[idx];
            *numPtrList[idx] = 0;
            moveBool = true;
          }
        }
      }
    }
  }

  afterPress(moveBool);
}

////////////////////////////////////////////////////////////////////////////////
// Press Down
////////////////////////////////////////////////////////////////////////////////

void Game::pressDown() {
  bool moveBool = false;

  for (int colIdx = 0; colIdx < 4; colIdx++) {
    array<int *, 4> numPtrList;

    for (int idx = 0; idx < 4; idx++) {
      numPtrList[idx] = &__gameMap[idx][colIdx];
    }

    int tarIdx = 3;

    for (int idx = 2; idx >= 0; idx--) {
      if (*numPtrList[idx]) {
        if (*numPtrList[tarIdx] == 0) {
          *numPtrList[tarIdx] = *numPtrList[idx];
          *numPtrList[idx] = 0;
          moveBool = true;
        } else if (*numPtrList[tarIdx] == *numPtrList[idx]) {
          *numPtrList[tarIdx] *= 2;
          *numPtrList[idx] = 0;
          tarIdx--;
          moveBool = true;
        } else {
          tarIdx--;

          if (idx < tarIdx) {
            *numPtrList[tarIdx] = *numPtrList[idx];
            *numPtrList[idx] = 0;
            moveBool = true;
          }
        }
      }
    }
  }

  afterPress(moveBool);
}

////////////////////////////////////////////////////////////////////////////////
// Win Check
////////////////////////////////////////////////////////////////////////////////

bool Game::winCheck() const {
  for (auto i : __gameMap) {
    for (int j : i) {
      if (j == 2048) {
        return true;
      }
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// Lose Check
////////////////////////////////////////////////////////////////////////////////

bool Game::loseCheck() const {
  for (auto line : __gameMap) {
    for (int j : line) {
      if (j == 0) {
        return false;
      }
    }

    for (int idx = 0; idx < 3; idx++) {
      if (line[idx] == line[idx + 1]) {
        return false;
      }
    }
  }

  for (int colIdx = 0; colIdx < 4; colIdx++) {
    vector<int> colList;

    for (auto line : __gameMap) {
      colList.push_back(line[colIdx]);
    }

    for (int idx = 0; idx < 3; idx++) {
      if (colList[idx] == colList[idx + 1]) {
        return false;
      }
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
// After Press
////////////////////////////////////////////////////////////////////////////////

void Game::afterPress(const bool moveBool) {
  if (moveBool) {
    __stepNum++;
    createNewNum();
  }

  if (winCheck()) {
    show();
    printw("\nYou Win!\n");
    getch();
    exit(0);
  }

  if (loseCheck()) {
    show();
    printw("\nYou Lose!\n");
    getch();
    exit(0);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Run
////////////////////////////////////////////////////////////////////////////////

void Game::Run() {
  initscr();
  cbreak();
  noecho();
  show();
  char inputChar;

  while (1) {
    inputChar = getch();

    if (inputChar == 'H') {
      pressUp();
    } else if (inputChar == 'P') {
      pressDown();
    } else if (inputChar == 'K') {
      pressLeft();
    } else if (inputChar == 'M') {
      pressRight();
    }

    show();
  }
  endwin();
}

// Namespace End
} // namespace Game2048