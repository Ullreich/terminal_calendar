#ifndef WEEK_H   /* Include guard */
#define WEEK_H

#include <curses.h>
#include <ncurses.h>
#include <libical/ical.h>

int calcCellHeight(int windowHeight, int hours);

int calcCellLength(int windowLength, int days);

struct Week {
  int days, hours, cellLength, cellHeight, scrollY, scrollX, tableYOffset, tableXOffset;
  WINDOW *parentWindow;
  // these three should maybe be wrapped by a struct?
  WINDOW *cells[7][12]; // TODO: fix this so its not static: https://stackoverflow.com/questions/17250480/declaring-int-array-inside-struct
  WINDOW *textCells[7][12];
  icalcomponent *cellsContent[7][12];
};

void refreshCells(struct Week *w);

struct Week weekConst(int days, int hours, int tableYOffset, int tableXOffset, WINDOW *pw);

void makeWeek(struct Week *w);

void drawCell(struct Week *w, int day, int hour, bool refresh);

void updateCell(struct Week *w, int d, int h, char *text, bool center);

void colorCellBackground(struct Week *w, int d, int h, int colorpair);

void drawWeek(struct Week *w);

void scrollDown(struct Week *w);

void scrollUp(struct Week *w);

void scrollLeft(struct Week *w);

void scrollRight(struct Week *w);

#endif
