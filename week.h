#ifndef WEEK_H   /* Include guard */
#define WEEK_H

#include <curses.h>
#include <ncurses.h>
#include "customutils.h"

int calcCellHeight(int windowHeight, int hours);

int calcCellLength(int windowLength, int days);

struct Week {
  int windowLength, windowHeight, days, hours, cellLength, cellHeight, scrollY, scrollX, tableYOffset, tableXOffset;
  WINDOW *parentWindow;
  WINDOW *cells[7][12]; // TODO: fix this so its not static: https://stackoverflow.com/questions/17250480/declaring-int-array-inside-struct
  // probably gonna need a cell struct or something
};

void refreshCells(struct Week *w);

struct Week weekConst(int days, int hours, int tableYOffset, int tableXOffset, WINDOW *pw);

void makeDays(struct Week *w);

void drawCell(struct Week *w, int day, int hour, bool refresh);

void updateCell(struct Week *w, int d, int h, char *text, bool center);

void colorCellBackground(struct Week *w, int d, int h, int colorpair);

void drawDays(struct Week *w);

#endif
