#ifndef WIN_F_HH
#define WIN_F_HH

#include <ncurses.h>
#include <string>
#include <cstring>
#include <iostream>

#define MAXLINE 100

namespace win_f 
{
  class Opt_WINDOW 
  {
  private:
    WINDOW *       _Window;
    const char **  _Options;
    int            _n_Options;
    
    int            _Win_length;
    int            _Win_height;
    
    int            _Highlight;
    
  public:

    Opt_WINDOW(int y, int x, const char ** op, int n);
    
    void display(void);
    void del_win(void);

    void disp_next_opt(void);
    void disp_prev_opt(void);
    
    int get_user_choice(void);
    
    int find_longest_ind(void);
    int get_longest_opt(void);
    
    void enable_special_keys(void) { keypad(_Window, TRUE); }
    void disable_special_keys(void) { keypad(_Window, FALSE); }
    void hold(void){ wgetch(_Window); }
  };

}

#endif
