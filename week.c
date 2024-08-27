#include <curses.h>
#include <ncurses.h>
#include "week.h"

// helper functions
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
  for (int day=0; day<(w->days); ++day) {
    for (int hour=0; hour<(w->hours); ++hour) {
      // init a subwindow at d.cells[day][hour]
      w->cells[day][hour] = derwin(w->parentWindow, w->cellHeight, w->cellLength, (w->cellHeight-1)*hour, (w->cellLength-1)*day);
    }
  }
}

void drawCell(struct Week *w, int day, int hour, bool refresh) {
  int topleft, topright, bottomleft, bottomright;
  topleft = topright = bottomleft = bottomright = ACS_PLUS;

  // find out bordertype
  if (day==0) {
    topleft = bottomleft = ACS_LTEE;
    if (hour==0) {
      topleft = ACS_ULCORNER;
      topright = ACS_TTEE;
    } else if (hour==(w->hours)-1) {
      bottomleft = ACS_LLCORNER;
      bottomright = ACS_BTEE;
    }
  } else if (day==(w->days)-1) {
    topright = bottomright = ACS_RTEE;
     if (hour==0) {
      topleft = ACS_TTEE;
      topright = ACS_URCORNER;
    } else if (hour==(w->hours)-1) {
      bottomleft = ACS_BTEE;
      bottomright = ACS_LRCORNER;
    }
  } else if (hour==0) {
    topleft = topright = ACS_TTEE;
  } else if (hour==(w->hours)-1) {
    bottomleft = bottomright = ACS_BTEE;
  }
  
  // draw border
  wborder(w->cells[day][hour], 0, 0, 0, 0, topleft, topright, bottomleft, bottomright);
  if (refresh) {
    refresh();
    wrefresh(w->parentWindow);
  }
}

void updateCell(struct Week *w, int d, int h, char *text, bool center) {
  mvwprintw(w->cells[d][h], 1, 1, text);
  refresh();
  wrefresh(w->cells[d][h]);
}

void drawDays(struct Week *w) {
  for (int day=0; day<(w->days); ++day) {
    for (int hour=0; hour<(w->hours); ++hour) {
      // draw in drawcell so that code is more modular
      drawCell(w, day, hour, false);
    }
  }
  refresh();
  wrefresh(w->parentWindow);
}
