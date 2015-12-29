#include "win_f.hh"

using namespace win_f;

int Opt_WINDOW::find_longest_ind(void)
{
  int longest = 0;
  unsigned tmp_len;
  
  for(int i = 0; i < _n_Options; ++i){
    if((tmp_len = strlen(_Options[i])) > strlen(_Options[longest]))
      longest = i;
  }

  return longest;
}

int Opt_WINDOW::get_longest_opt(void)
{
  return strlen(_Options[find_longest_ind()]);
}

Opt_WINDOW::Opt_WINDOW(int y, int x, const char ** op, int n):
  _Options(op),  _n_Options(n)
{ 
  _Highlight = 0;
  
  _Win_length = 2 + get_longest_opt();
  _Win_height = 2 + _n_Options;
  
  _Window = newwin(_Win_height, _Win_length, y, x);

  box(_Window, 0, 0);
}

void Opt_WINDOW::del_win(void)
{
  werase(_Window);
  delwin(_Window);
}

void Opt_WINDOW::display(void)
{
  int x, y;
  
  x = 1;
  y = 1;
  
  for(int i = 0; i < _n_Options; ++i, ++y){
    if(_Highlight == i)
      /* enable highlight */
      wattron(_Window, A_REVERSE);
    else /* disable it */
      wattroff(_Window, A_REVERSE);

    mvwprintw(_Window, y, x, "%s", _Options[i]);
  }
  
  wrefresh(_Window);
}

void Opt_WINDOW::disp_next_opt(void)
{
  if((++_Highlight) > _n_Options - 1)
    _Highlight = 0;
  
  display();
}

void Opt_WINDOW::disp_prev_opt(void)
{
  if((--_Highlight) < 0)
    _Highlight = _n_Options - 1;
  
  display();
}

int Opt_WINDOW::get_user_choice(void)
{
  int c = 0;
  
  enable_special_keys();
 
  display();
  while((c = wgetch(_Window)) != KEY_RIGHT) {

    switch(c) {
    case KEY_UP:
      disp_prev_opt();
      break;
    case KEY_DOWN:
      disp_next_opt();
      break;      
    default:
      break;
    }    
  }
  
  return _Highlight;
}
