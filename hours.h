#ifndef HOURS_H   /* Include guard */
#define HOURS_H

#include <curses.h>
#include <ncurses.h>
#include "customutils.h"

struct Hours {
  int hourLength, hourHeight, scrollY, hourYOffset;
  WINDOW *parentWindow;
  WINDOW *cells[12];
};

struct Hours hoursConst(int hourLength, int hourYOffset,  WINDOW *pw);

void refreshCellsHours(struct Hours *hours);

void makeHours(struct Hours *hours);

void drawHours(struct Hours *hours);

void scrollUpHours(struct Hours *hours);

void scrollDownHours(struct Hours *hours);

#endif
