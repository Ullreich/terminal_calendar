#include <curses.h>
#include <ncurses.h>
// #include <string.h>
// #include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
//#include "player.h"
#include "customutils.h"
#include "week.h"

/*
void updateCell(struct Day *day, int d, int h, char *text) {
  mvwprintw(day[d].cells[h], 1, 1, text);
  refresh();
  wrefresh(day[d].cells[h]);
}

void invertCell(struct Day *day, int d, int h, int colorpair) {
  //mvwprintw(day[d].cells[h], 1, 1, "inverse");
  wbkgd(day[d].cells[h], COLOR_PAIR(colorpair));
  refresh();
  wrefresh(day[d].cells[h]);
  wattroff(day[d].cells[h], COLOR_PAIR(colorpair));
}
*/

/*
void moveCell(struct Day *day, int d, int h, int numDays, int numHours) {
   invert
}
*/

// move all this to a util file

int main(int argc, char ** argv) {
  // initializes the screen
  // sets up memory and clears the screen
  initscr();
  noecho();
  nodelay(stdscr, true);
  curs_set(0);
  use_default_colors();
  start_color();

  // need 12 timeslots, make it modular tho
  // array of weekdays

  // important variables
  const char weekdays[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  const int numDays = 7;
  const int tableHeight = 37;
  const int numHours = 12;
  const int tableXOffset = 10;
  const int tableYOffset = 3;
  const int cellWidth = 25;
  const int cellHeight = calcCellHeight(tableHeight, numHours); 
  const int startTime = 8;
  int c; // to get input chars
  int currd = 0;
  int currh = 0;
  bool loop = true;
  
  WINDOW *mainwin = newwin(tableHeight, (cellWidth-1)*numDays+1, tableYOffset, tableXOffset); // height has to be 1 mod timeslots -> get size of current window and update height
  keypad(mainwin, true);

  init_pair(1, -1, -1); // default colors
  init_pair(2, COLOR_BLACK, COLOR_RED);

  // write all the day names
  attron(A_BOLD);
  for (int i=0; i<numDays; ++i) {
    // calculate centering offset
    int centerOffset = centerString(cellWidth, stringLength(weekdays[i]));
    mvprintw(tableYOffset-1, (tableXOffset+1)+(cellWidth-1)*i+centerOffset, weekdays[i]);
  }
  attroff(A_BOLD);

  // write all the times
  attron(A_BOLD);
  for (int i=0; i<numHours; ++i) {
    mvprintw(tableYOffset+1 + (cellHeight-1)*i, centerString(tableXOffset, 5), "%d:00", i+startTime); // can have 5 here as long as we dont change string formatting
  }
  attroff(A_BOLD);

  // draw all the cells
  struct Week week = weekConst(numDays, numHours, mainwin);
  makeDays(&week);
  drawDays(&week);

  // test writing into cells
  updateCell(&week, 0, 2, "hewo", false);

  // main loop
  while (loop) {
    // get keys
    int c = wgetch(mainwin);
    switch (c) {
      case 'q':
        loop=false;
        break;
      // can you compact the keypress code? so much boilderplate
      case KEY_UP:
      case KEY_DOWN:
      case KEY_LEFT:
      case KEY_RIGHT:
        // invertCell(columns, currd, currh, 1);
        if (c==KEY_UP) {currh = max(0, currh-1);}
        else if (c==KEY_DOWN) {currh = min(numHours-1, currh+1);}
        else if (c==KEY_LEFT) {currd = max(0, currd-1);}
        else {currd = min(numDays-1, currd+1);}
        // invertCell(columns, currd, currh, 2);
        break;
      case ' ':
        // invertCell(columns, currd, currh, 1);
      default:
        break;
    }

    // fix scaling on resizing

    // redraw 

    // sleep so we dont have too many useless cycles refreshing
    usleep(1000 * 8); //about 120 fps
  }

  endwin();

  return 0;
}
