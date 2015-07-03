#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>

class Player
{
private:
  std::string _Name;
  int _Score;

public:
  Player() { _Name = " "; _Score = 0; }
  Player(std::string name){ _Name = name; _Score = 0; }
  int getScore(){ return _Score; }
  void incrScore(){ ++_Score; } 
};

#endif
