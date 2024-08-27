#include <curses.h>
#include <ncurses.h>

// helper functions
int calcCellHeight(int height, int ts) {
  return (height/ts)+1;
}

// TODO: rename struct variables and make into matrix so it is less trash
struct Day {
  const char* weekday;
  int length, height, offset, timeslots, cellHeight;
  WINDOW *parentWindow;
  WINDOW *cells[12]; // TODO: fix this so its not static: https://stackoverflow.com/questions/17250480/declaring-int-array-inside-struct
  // probably gonna need a cell struct or something
};

// constructor
struct Day dayConst(const char* w, int l, int os, int ts, WINDOW *pw) {
  struct Day temp;

  int _;
  getmaxyx(pw, temp.height, _);
  temp.weekday = w;
  temp.length = l;
  temp.offset = os;
  temp.timeslots = ts;
  temp.cellHeight = calcCellHeight(temp.height, ts); // might be wrong, test this
  temp.parentWindow = pw;
  //temp.cells[ts];
  return temp;
}

void drawCell(struct Day *d) {}

// draw cells
void drawDay(struct Day *d) {
  for (int i=0; i<(d->timeslots); ++i) {
    d->cells[i] = derwin(d->parentWindow, d->cellHeight, d->length, (d->cellHeight-1)*i, d->offset);
    wborder(d->cells[i], 0, 0, 0, 0, ACS_PLUS, ACS_PLUS, 0, 0);
    // test writing in cells
    if (i == 2) {
      mvwprintw(d->cells[i], 1, 1, "hi");
    }
    refresh();
    wrefresh(d->cells[i]);
  }
  /* draw box around whole calendar
  box(d->parentWindow, 0, 0);
  refresh();
  wrefresh(d->parentWindow);
  */
}
