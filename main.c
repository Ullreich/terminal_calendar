#include <curses.h>
#include <ncurses.h>
// #include <string.h>
// #include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "customutils.h"
#include "week.h"

int main(int argc, char ** argv) {
  // initializes the screen
  // sets up memory and clears the screen
  initscr();
  noecho();
  nodelay(stdscr, true);
  curs_set(0);
  use_default_colors();
  start_color();

  // need 12 hours, 7 days, make it modular tho

  //-----------------------------------------------------------------------------
  // important variables
  //-----------------------------------------------------------------------------
  int screenMaxy, screeenMaxx;
  getmaxyx(stdscr, screenMaxy, screeenMaxx);
  // dims for pad of weekdays, hours and cells
  int dayYOffset = 3; //TODO hardcoded for now change later I guess
  int dayXOffset = 10;
  int hourYOffset = 3;
  int hourXOffset = 0;
  int scrollY = 0;
  int scrollX = 0;


  const char weekdays[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  const int numDays = 7;
  const int tableHeight = 37;
  const int numHours = 12;
  const int tableXOffset = dayXOffset;
  const int tableYOffset = hourYOffset;
  const int cellWidth = 25;
  const int cellHeight = calcCellHeight(tableHeight, numHours); 
  const int startTime = 8;
  int c; // to get input chars
  int currd = 0;
  int currh = 0;
  bool loop = true;
  bool isHighlighted = true;
  
  // TODO rename mainwin
  //WINDOW *mainwin = newwin(tableHeight, (cellWidth-1)*numDays+1, tableYOffset, tableXOffset); // height has to be 1 mod timeslots -> get size of current window and update height
  WINDOW *mainwin = newpad(tableHeight, (cellWidth-1)*numDays+1); // height has to be 1 mod timeslots -> get size of current window and update height
  prefresh(mainwin, 0, 0, tableYOffset, tableXOffset, screenMaxy, screeenMaxx); // pad, upper left corner (y,x) to start in,
  keypad(mainwin, true);

  init_pair(1, -1, -1); // default colors
  init_pair(2, COLOR_BLACK, COLOR_RED);

  //-----------------------------------------------------------------------------
  // initialization
  //-----------------------------------------------------------------------------

  // write all the day names
  // TODO put in pad
  attron(A_BOLD);
  for (int i=0; i<numDays; ++i) {
    // calculate centering offset
    int centerOffset = centerString(cellWidth, stringLength(weekdays[i]));
    mvprintw(tableYOffset-1, (tableXOffset+1)+(cellWidth-1)*i+centerOffset, weekdays[i]);
  }
  attroff(A_BOLD);

  // write all the times
  // TODO put in pad
  attron(A_BOLD);
  for (int i=0; i<numHours; ++i) {
    mvprintw(tableYOffset+1 + (cellHeight-1)*i, centerString(tableXOffset, 5), "%d:00", i+startTime); // can have 5 here as long as we dont change string formatting
  }
  attroff(A_BOLD);
  refresh();

  // draw all the cells
  struct Week week = weekConst(numDays, numHours, tableYOffset, tableXOffset, mainwin);
  makeDays(&week);
  drawDays(&week);

  //highlight current cell
  colorCellBackground(&week, currd, currh, 2);

  // test writing into cells
  updateCell(&week, 0, 2, "hewo guys", true);
  // colorCellBackground(&week, 0, 2, 2);

  //-----------------------------------------------------------------------------
  // main loop
  //-----------------------------------------------------------------------------
  
  while (loop) {
    // get keys
    int c = wgetch(mainwin);
    switch (c) {
      // quit
      case 'q':
        loop=false;
        break;
      // arrow movement TODO add vim keybinds
      case KEY_UP:
      case KEY_DOWN:
      case KEY_LEFT:
      case KEY_RIGHT:
        isHighlighted = true;
        colorCellBackground(&week, currd, currh, 1);
        drawCell(&week, currd, currh, true);
        if (c==KEY_UP) {currh = max(0, currh-1);}
        else if (c==KEY_DOWN) {currh = min(numHours-1, currh+1);}
        else if (c==KEY_LEFT) {currd = max(0, currd-1);}
        else {currd = min(numDays-1, currd+1);}
        colorCellBackground(&week, currd, currh, 2);
        break;
      // toggle highlight
      case ' ':
        if (isHighlighted) {
          colorCellBackground(&week, currd, currh, 1);
          drawCell(&week, currd, currh, true);
        } else {
          colorCellBackground(&week, currd, currh, 2);
        }
        isHighlighted = !isHighlighted;
      default:
        break;
    }

    // fix scaling on resizing

    // redraw 

    // sleep so we dont have too many useless cycles refreshing
    usleep(1000 * 8); //about 120 fps //TODO make fps settable from calling from commandline
  }

  endwin();

  return 0;
}
