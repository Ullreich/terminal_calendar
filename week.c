#include <curses.h>
#include <ncurses.h>
#include "week.h"
#include "customutils.h"

//------------------------------------------------------------------------------
// helper functions
//------------------------------------------------------------------------------

int calcCellHeight(int windowHeight, int hours) {
  return (windowHeight/hours)+1;
}

int calcCellLength(int windowLength, int days) {
  return (windowLength/days)+1;
}

//------------------------------------------------------------------------------
// struct week
//------------------------------------------------------------------------------

// constructor
struct Week weekConst(int days, int hours, WINDOW *pw) {
  struct Week temp;

  int _;
  getmaxyx(pw, temp.windowHeight, temp.windowLength);
  temp.days = days;
  temp.hours = hours;
  temp.cellLength = calcCellLength(temp.windowLength, temp.days);
  temp.cellHeight = calcCellHeight(temp.windowHeight, temp.hours); // might be wrong, test this
  temp.parentWindow = pw;

  return temp;
}

void makeDays(struct Week *w) {
  for (int d=0; d<(w->days); ++d) {
    for (int h=0; h<(w->hours); ++h) {
      // init a subwindow at d.cells[day][hour]
      w->cells[d][h] = derwin(w->parentWindow, w->cellHeight, w->cellLength, (w->cellHeight-1)*h, (w->cellLength-1)*d);
    }
  }
}

void drawCell(struct Week *w, int d, int h, bool refresh) {
  int topleft, topright, bottomleft, bottomright;
  topleft = topright = bottomleft = bottomright = ACS_PLUS;

  // find out bordertype
  if (d==0) {
    topleft = bottomleft = ACS_LTEE;
    if (h==0) {
      topleft = ACS_ULCORNER;
      topright = ACS_TTEE;
    } else if (h==(w->hours)-1) {
      bottomleft = ACS_LLCORNER;
      bottomright = ACS_BTEE;
    }
  } else if (d==(w->days)-1) {
    topright = bottomright = ACS_RTEE;
     if (h==0) {
      topleft = ACS_TTEE;
      topright = ACS_URCORNER;
    } else if (h==(w->hours)-1) {
      bottomleft = ACS_BTEE;
      bottomright = ACS_LRCORNER;
    }
  } else if (h==0) {
    topleft = topright = ACS_TTEE;
  } else if (h==(w->hours)-1) {
    bottomleft = bottomright = ACS_BTEE;
  }
  
  // draw border
  wborder(w->cells[d][h], 0, 0, 0, 0, topleft, topright, bottomleft, bottomright);
  if (refresh) {
    refresh();
    wrefresh(w->cells[d][h]);
  }
}

void updateCell(struct Week *w, int d, int h, char *text, bool center) {
  int x,y;
  x = y = 1;
  if (center) {
    x = centerString(w->cellLength, stringLength(text));
  }
  mvwprintw(w->cells[d][h], y, x, text);
  refresh();
  wrefresh(w->cells[d][h]);
}

void colorCellBackground(struct Week *w, int d, int h, int colorpair) {
  // color background
  wbkgd(w->cells[d][h], COLOR_PAIR(colorpair));
  // redraw box so it looks fancier
  wborder(w->cells[d][h], 0, 0, 0, 0, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  refresh();
  wrefresh(w->cells[d][h]);
  wattroff(w->cells[d][h], COLOR_PAIR(colorpair));
}

void drawDays(struct Week *w) {
  for (int d=0; d<(w->days); ++d) {
    for (int h=0; h<(w->hours); ++h) {
      // draw in drawcell so that code is more modular
      drawCell(w, d, h, false);
    }
  }
  refresh();
  wrefresh(w->parentWindow);
}
