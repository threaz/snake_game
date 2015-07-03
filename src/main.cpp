#include "Snake.hh"
#include "Board.hh"
#include "Player.hh"

#include <ctime>
#include <ncurses.h>
#include <unistd.h>

#define DELAY_STEP 0.1

int main()
{
  initscr();
  noecho();
  cbreak(); // dont have to use ENTER 
  curs_set(FALSE); // no cursor
  keypad(stdscr, TRUE);
  
  /* MAIN PROGRAM */
  Board Plansza(stdscr);
  Snake W1(stdscr, LINES, COLS);
  Player P1("Damian");
  
  W1.showSnake();

  int ch = ' '; // not F1
  int prev_ch = 'x'; // not ch
  int objCount = 0;
  double DELAY = 3;

  time_t timer;
  while(true && ch != KEY_F(1))
    {
      halfdelay(DELAY);
      ch = getch();
      if(ch == ERR) // no character was entered
	W1.autoMove();
      else if(prev_ch == ch) // player entered same direction as snake had moved
	{
	  // do nothing
	}
      else // there was a character
	{ 
	  switch(ch)
	    {
	    case KEY_UP:
	      W1.moveUp();
	      break;
	    case KEY_DOWN:
	      W1.moveDown();
	      break;
	    case KEY_LEFT:
	      W1.moveLeft();
	      break;
	    case KEY_RIGHT:
	      W1.moveRight();
	      break;
	    default:
	      // do nothing
	      break;
	    }
	  
	  prev_ch = ch;
	}
      
      // score 
      Plansza.showScore(stdscr, LINES-2, P1.getScore());

      // get current time
      time(&timer);
      timer %= 10;
      
      if(timer == 0 || timer == 4 || timer == 8)
	Plansza.generateRandObject(stdscr, LINES, COLS);

      // check if snake eat something
      if(Plansza.isThereObject(stdscr, W1.getHeadY(), W1.getHeadX()))
	{
	  W1.addLast(); // expand snake
	  DELAY -= DELAY_STEP; // make game faster
	  P1.incrScore();
	}

      if(W1.collide()) ch = KEY_F(1);
    }
  
  Plansza.showGameOver(stdscr, LINES, COLS);
  
  /* END OF THE PROGRAM */  
  
  nocbreak();
  getch();
  endwin();
  return 0;
}
