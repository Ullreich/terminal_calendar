
#include <curses.h>
#include <ncurses.h>
#include "hours.h"
#include "customutils.h"

struct Hours hoursConst(int hourLength, int hourYOffset,  WINDOW *pw) {
  struct Hours temp;

  temp.parentWindow = pw;
  temp.hourYOffset = hourYOffset ;
  temp.hourLength = hourLength; 
  temp.hourHeight = calcCellLength(getmaxy(temp.parentWindow), 12);
  temp.scrollY = 0;

  return temp;
}

void refreshCellsHours(struct Hours *hours) {
  prefresh(hours->parentWindow, hours->scrollY, 0 , hours->hourYOffset, 0, getmaxy(stdscr)-1, getmaxx(stdscr)-1);
}

void makeHours(struct Hours *hours) {
  for (int h=0; h<12; ++h) {
    hours->cells[h] = subpad(hours->parentWindow, hours->hourHeight, hours->hourLength, (hours->hourHeight-1)*h, 0);
  }
}

void drawHours(struct Hours *hours) {
  for (int h=0; h<12; ++h) {
    int centerOffset = centerString(hours->hourLength, 5); // 5 since hour strings eg 13:00 are 5 long
    wattron(hours->cells[h], A_BOLD);
    mvwprintw(hours->cells[h], 1, centerOffset, "%d:00", h+8);
    wattroff(hours->cells[h], A_BOLD);
  }
  refresh();
  refreshCellsHours(hours);
}

void scrollDownHours(struct Hours *hours) {
  if (hours->scrollY<(getmaxy(hours->parentWindow)-(getmaxy(stdscr)-hours->hourYOffset))) {
    ++hours->scrollY;
  }
  refreshCellsHours(hours);
}

void scrollUpHours(struct Hours *hours) {
  if (hours->scrollY>0) {
    --hours->scrollY;
  }
  refreshCellsHours(hours);
}
