#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Object.hh"

#define B_WID 80
#define B_HEI 24
#define B_SIGN '#'
#define B_CORNER '+'


class Board
{
private:
  std::vector<Object> _Obj;
  
public:
  Board(WINDOW * win); // make borders and credits
  
  void generateRandObject(WINDOW *, const int, const int);
  bool isThereObject(WINDOW * win, const int y, const int x);
  
  void showAuthor(WINDOW * win, const int y);
  void showScore(WINDOW * win, const int y, const int score);
  void showSpeed(WINDOW * win, const int y, const int speed);  
  void showGameOver(WINDOW * win, const int y, const int x);
};

#endif
