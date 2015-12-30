#include "Snake.hh"
#include "Board.hh"
#include "Player.hh"

//#include <boost/timer.hpp>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <iomanip>

#define SECOND 1000000
#define DELAY_SHOW_FRUIT 2

int main()
{
  initscr();
  noecho();
  cbreak(); // dont have to use ENTER 
  curs_set(FALSE); // no cursor
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE); 
  srand(time(NULL));
  
  Board Plansza(stdscr);
  Snake W1(stdscr);
  Player P1("Damian");

  int ch = 'y', prev_ch = 'x'; // just some different values
  long delay = 0.2 * SECOND;
  time_t last_time, cur_time;
 
  /* MAIN PROGRAM */
  
  // drawing snake
  W1.showSnake();
  // and score 
  Plansza.showScore(stdscr, LINES-2, P1.getScore()); // fix this last argument!
  Plansza.showSpeed(stdscr, LINES-2, delay/1000);    // fix it to show some accurate speed
  time(&last_time);
  // set timer
  
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

      time(&cur_time);
      if(difftime(cur_time, last_time) > DELAY_SHOW_FRUIT)
 	{
 	  Plansza.generateRandObject(stdscr, LINES, COLS);
	  time(&last_time);
 	}
      
      
      if(Plansza.isThereObject(stdscr, W1.getHeadY(), W1.getHeadX()))
	{
	  W1.addLast(); // add snake's segment
	  P1.incrScore();
	  delay = delay * 0.95;
	}
      
      if(W1.collide())
	break;
      
      Plansza.showScore(stdscr, LINES-2, P1.getScore());
      Plansza.showSpeed(stdscr, LINES-2, delay/1000);
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

