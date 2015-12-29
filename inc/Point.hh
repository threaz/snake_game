#ifndef POINT_HH
#define POINT_HH

#include <ncurses.h>

class Point
{
private:
  int _X, _Y;
  char _Sign;
  
public:
  Point(){ _Y = _X = 0; _Sign = ' '; }
  Point(int y, int x) { _Y = y; _X = x; _Sign = '#'; }  
  void showPoint(WINDOW * win) const {
    mvwprintw(win, _Y, _X, "%c", _Sign);
  }
  char getSign(){ return _Sign; } 
  void changeSign(char ch){ _Sign = ch; }
  int getY(){ return _Y; }
  int getX(){ return _X; }
};

#endif
