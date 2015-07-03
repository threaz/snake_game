#include "Snake.hh"

Snake::Snake(WINDOW * win, const int y, const int x)
{
  int Y_Pos = y/2, X_Pos = x/2;
    
  for(int i = 0; i < 5; ++i)
    _Part.push_back(Point(Y_Pos, X_Pos + i));
    
  _Head = &_Part.front();
  _Tail = &_Part.back();
  _Win = win;
    
  // start direction 
  _Dir = L;
}

void Snake::showSnake()
{
  for(const Point & temp_part : _Part)
    temp_part.showPoint(_Win);
  wrefresh(_Win);
}

bool Snake::removeLast()
{ 
  // if snake is empty
  if(!_Part.size()) return false;
    
  // else
  Point & last_point = _Part.back();
  int y = last_point.getY(), x = last_point.getX();
    
  _Part.pop_back();
  mvwprintw(_Win, y, x, "%c", ' ');
  return true;
} 

void Snake::addLast()
{
  int y = _Tail->getY(), x = _Tail->getX();
  if(_Dir == L) _Part.push_back(Point(y, ++x));
  else if(_Dir == R) _Part.push_back(Point(y, --x));
  else if(_Dir == U) _Part.push_back(Point(++y, x));
  else if(_Dir == D) _Part.push_back(Point(--y, x));
}

void Snake::moveUp()
{
  if(_Dir == D) return; // cant go back
     
  int y, x;
  y = _Head->getY();
  x = _Head->getX();
    
  if((*this).removeLast()) // if there is an element
    {
      _Part.push_front(Point(--y, x));
      _Head = &_Part.front();
      _Dir = U;
    }
  (*this).showSnake();
}

void Snake::moveDown()
{
  if(_Dir == U) return;
    
  int y, x;
  y = _Head->getY();
  x = _Head->getX();
    
  if((*this).removeLast()) // if there is an element
    {
      _Part.push_front(Point(++y, x));
      _Head = &_Part.front();
      _Dir = D;
    }
  (*this).showSnake();
}

void Snake::moveLeft()
{
  if(_Dir == R) return; 
    
  int y, x;
  y = _Head->getY();
  x = _Head->getX();
    
  if((*this).removeLast()) // if there is an element
    {
      _Part.push_front(Point(y, --x));
      _Head = &_Part.front();
      _Dir = L;
    }
  (*this).showSnake();
}

void Snake::moveRight()
{
  if(_Dir == L) return;
  int y, x;
  y = _Head->getY();
  x = _Head->getX();
    
  if((*this).removeLast()) // if there is an element
    {
      _Part.push_front(Point(y, ++x));
      _Head = &_Part.front();
      _Dir = R;
    }
  (*this).showSnake();
}  

void Snake::autoMove()
{
  if(_Dir == L)
    moveLeft();
  else if(_Dir == R)
    moveRight();
  else if(_Dir == U)
    moveUp();
  else 
    moveDown();
}
  

bool Snake::collide()
{
  int y = _Head->getY(), x = _Head->getX();
  if(x == 0 || x == B_WID - 1) return true;
  else if(y == 0 || y == B_HEI - 3) return true;
    
  std::list<Point>::iterator Iter;
  for(Iter = ++_Part.begin(); Iter != _Part.end(); ++Iter)
    if((*Iter).getX() == x && (*Iter).getY() == y) return true;
      
  return false;
}

