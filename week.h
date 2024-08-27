#ifndef WEEK_H   /* Include guard */
#define WEEK_H

#include <curses.h>
#include <ncurses.h>
#include "customutils.h"

int calcCellHeight(int windowHeight, int hours);

int calcCellLength(int windowLength, int days);

struct Week {
  int windowLength, windowHeight, days, hours, cellLength, cellHeight;
  WINDOW *parentWindow;
  WINDOW *cells[7][12]; // TODO: fix this so its not static: https://stackoverflow.com/questions/17250480/declaring-int-array-inside-struct
  // probably gonna need a cell struct or something
};


struct Week weekConst(int days, int hours, WINDOW *pw);

void makeDays(struct Week *w);

void drawCell(struct Week *w, int day, int hour, bool refresh);

void updateCell(struct Week *w, int d, int h, char *text, bool center);

void drawDays(struct Week *w);

#endif
