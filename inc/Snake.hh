#include <iostream>
#include <ncurses.h>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Object.hh"

#define B_WID 80
#define B_HEI 24
#define B_SIGN '#'
#define B_CORNER '+'

class Snake
{
private:
  std::list<Point> _Part;
  Point * _Head;
  Point * _Tail; // XDDD
  
  WINDOW * _Win;
  enum Direction { U, D, L, R } _Dir;

  
public:
  Snake(WINDOW * win);
  void showSnake();
  
  bool removeLast();
  void addLast(); // add an element at the end of the snake
  
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  void moveSnake(int ch);
  void autoMove();
  
  int getHeadY(){ return _Head->getY(); }
  int getHeadX(){ return _Head->getX(); }

  bool collide();
};
