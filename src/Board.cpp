
#include "Board.hh"
#include "Object.hh"

Board::Board(WINDOW * win) // make borders and credits
{
  wborder(win, '|', '|', '-', '-', 
	  B_CORNER, B_CORNER, B_CORNER, B_CORNER);
    
  // draw bottom line and scores underneath
  mvwhline(win, LINES-3, 1, '-', COLS-2);
    
  showScore(win, B_HEI-2, 0);
  showAuthor(win, B_HEI-2); 
  wrefresh(win);
}

void Board::generateRandObject(WINDOW * win, const int max_y, const int max_x)
{
  int r_y, r_x;
    
  r_y = (rand() % (max_y-4)) + 1;
  r_x = (rand() % (max_x-1)) + 1;
    
  _Obj.push_back(Object(r_y, r_x, 'O'));
  _Obj.back().showPoint(win);
  wrefresh(win);
}

bool Board::isThereObject(WINDOW * win, const int y, const int x)
{
  for(Object & temp_obj : _Obj)
    if(temp_obj.doCordsMatch(y,x)) return true;
    
  return false;
}

void Board::showAuthor(WINDOW * win, const int y) 
{
  std::string author = "Author: Damian Pukaluk ";
  int a_len = author.size();
    
  mvwprintw(win, y, B_WID - a_len -1, author.c_str());
}

void Board::showScore(WINDOW * win, const int y, const int score)
{
  mvwprintw(win, y, 2, "Score: %d", score);
}

void Board::showSpeed(WINDOW * win, const int y, const double speed)
{
  mvwprintw(win, y, 15, "Speed: %.2lf%%", speed);
}

void Board::showGameOver(WINDOW * win, const int y, const int x)
{
  std::string napis = "Game Over. Press any key to exit...";
  mvwprintw(win, y/2, x/2 - napis.size()/2,  "%s", napis.c_str());
  wrefresh(win);
}
