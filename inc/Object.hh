#ifndef OBJECT_HH
#define OBJECT_HH

#include "Point.hh"

class Object : public Point
{
public:
  Object(int y, int x, char sgn) : Point(y, x){
    (*this).changeSign(sgn);
  }
  bool doCordsMatch(const int y, const int x){
    return ((*this).getY() == y && (*this).getX() == x);
  }
};

#endif
