#include "Snake.hh"
#include "Board.hh"
#include "Player.hh"

#include <ctime>
#include <cstdio>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <iomanip>

#define SCND 1000000

int main()
{
  initscr();
  noecho();
  cbreak(); // dont have to use ENTER 
  curs_set(FALSE); // no cursor
  keypad(stdscr, TRUE);
  srand(time(NULL));
  
  /* MAIN PROGRAM */
  Board Plansza(stdscr);
  Snake W1(stdscr);
  Player P1("Damian");
  
  W1.showSnake();
  // score 
  Plansza.showScore(stdscr, LINES-2, P1.getScore());
  
  int ch = 'y', prev_ch = 'x';
  long delay = 0.6 * SCND;
  
  nodelay(stdscr, TRUE);
  
  while(ch = getch())
    {
      if(ch == ERR) // no character was entered
	  W1.autoMove();
      else if(ch == prev_ch) continue;
      else if(ch == 's') // slow down
	{
	delay = delay * 1.1;
	continue;
      }
      else if(ch == 'w') // speed up
	{
	  delay = delay * 0.9;
	  continue;
	}
      else 
	{ 
	  W1.moveSnake(ch);
	  prev_ch = ch;
	}      

      if(rand() % 4 == 0) // popraw to XDDDD
	Plansza.generateRandObject(stdscr, LINES, COLS);
      
      // check if snake has eaten something
      if(Plansza.isThereObject(stdscr, W1.getHeadY(), W1.getHeadX()))
	{
	  W1.addLast(); // add snake's segment
	  P1.incrScore();
	  Plansza.showScore(stdscr, LINES-2, P1.getScore());
	  delay = delay * 0.95;
	}
      
      if(W1.collide()) break;
      usleep(delay);
    }
  
  Plansza.showGameOver(stdscr, LINES, COLS);
   /* END OF THE PROGRAM */  

  nodelay(stdscr, FALSE);
  nocbreak();
  getch();
  
  endwin();
  return 0;
}

