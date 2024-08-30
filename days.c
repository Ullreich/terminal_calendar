#include <curses.h>
#include <ncurses.h>
#include "days.h"
#include "customutils.h"

const char weekdays[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// constructor
struct Days daysConst(int dayHeight, int dayXOffset,  WINDOW *pw) {
  struct Days temp;

  temp.parentWindow = pw;
  temp.dayXOffset = dayXOffset;
  temp.dayLength = calcCellLength(getmaxx(temp.parentWindow), 7);
  temp.dayHeight = dayHeight;
  temp.scrollX = 0;

  return temp;
}

void refreshCellsDays(struct Days *days) {
  prefresh(days->parentWindow, 0, days->scrollX, 0, days->dayXOffset, getmaxy(stdscr)-1, getmaxx(stdscr)-1);
}

void makeDays(struct Days *days) {
  for (int d=0; d<7; ++d) {
    days->cells[d] = subpad(days->parentWindow, days->dayHeight, days->dayLength, 0, (days->dayLength-1)*d);
  }
}

void drawDays(struct Days *days) {
  for (int d=0; d<7; ++d) {
    int centerOffset = centerString(days->dayLength, stringLength(weekdays[d]));
    wattron(days->cells[d], A_BOLD);
    mvwprintw(days->cells[d], 1, centerOffset+1, weekdays[d]);
    // box(days->cells[d], 0, 0);
    wattroff(days->cells[d], A_BOLD);
  }
  refresh();
  refreshCellsDays(days);
}

void scrollLeftDays(struct Days *days) {
  // increase scrolling speed
  for (int i=0; i<3; ++i) { //TODO: this is ineffictient, set a global variable and do it with arithmetic
    if (days->scrollX>0) {
      --days->scrollX;
    } else {break;}
  }
  refreshCellsDays(days);
}

void scrollRightDays(struct Days *days) {
  // increase scrolling speed 
  for (int i=0; i<3; ++i) {
    if (days->scrollX<(getmaxx(days->parentWindow)-(getmaxx(stdscr)-days->dayXOffset))) {
      ++days->scrollX;
    } else {break;}
  }
  refreshCellsDays(days);
}
