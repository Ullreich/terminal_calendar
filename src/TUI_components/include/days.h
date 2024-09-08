#ifndef DAYS_H   /* Include guard */
#define DAYS_H

#include <curses.h>
#include <ncurses.h>

struct Days {
  int dayLength, dayHeight, scrollX, dayXOffset;
  WINDOW *parentWindow;
  WINDOW *cells[7];
};

struct Days daysConst(int dayHeight, int dayXOffset,  WINDOW *pw);

void refreshCellsDays(struct Days *days);

void makeDays(struct Days *days);

void drawDays(struct Days *days);

void scrollLeftDays(struct Days *days);

void scrollRightDays(struct Days *days);

#endif
