#include <curses.h>
#include <ncurses.h>
// #include <string.h>
// #include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "customutils.h"
#include "week.h"
#include "days.h"
#include "hours.h"

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
  const int numDays = 7;
  const int numHours = 12;
  const int tableHeight = 37; //TODO: calculate this from cellHeight not other way around. Do we need this var?
  const int tableXOffset = 10;
  const int tableYOffset = 3;
  const int cellWidth = 25;
  const int cellHeight = calcCellHeight(tableHeight, numHours); 
  const int startTime = 8;
  int c; // to get input chars
  int currd = 0;
  int currh = 0;
  int oldy, oldx; // to check if dims changed
  getmaxyx(stdscr, oldy, oldx);
  bool loop = true;
  bool isHighlighted = true;
  
  // TODO rename mainwin
  WINDOW *mainwin = newpad(tableHeight, (cellWidth-1)*numDays+1); // height has to be 1 mod timeslots -> get size of current window and update height
  WINDOW *daywin = newpad(tableYOffset, (cellWidth-1)*numDays+1); // height has to be 1 mod timeslots -> get size of current window and update height
  WINDOW *hourwin = newpad(tableHeight, tableXOffset); // height has to be 1 mod timeslots -> get size of current window and update height
  wrefresh(hourwin);
  keypad(mainwin, true);

  init_pair(1, -1, -1); // default colors
  init_pair(2, COLOR_BLACK, COLOR_RED);

  //-----------------------------------------------------------------------------
  // initialization
  //-----------------------------------------------------------------------------

  // write all the day names
  struct Days days = daysConst(tableYOffset, tableXOffset, daywin);
  makeDays(&days);
  drawDays(&days);

  // write all the times
  struct Hours hours = hoursConst(tableXOffset, tableYOffset, hourwin);
  makeHours(&hours);
  drawHours(&hours);

  // draw all the cells
  struct Week week = weekConst(numDays, numHours, tableYOffset, tableXOffset, mainwin);
  makeWeek(&week);
  drawWeek(&week);
  colorCellBackground(&week, currd, currh, 2); //highlight current cell
  
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
      // TODO: should this be in week.c?
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
        break;
      case 's':
        scrollDown(&week);
        scrollDownHours(&hours);
        break;
      case 'w':
        scrollUp(&week);
        scrollUpHours(&hours);
        break;
      case 'd':
        scrollRight(&week);
        scrollRightDays(&days);
        break;
      case 'a':
        scrollLeft(&week);
        scrollLeftDays(&days);
        break;
     default:
        break;
    }

    // fix scaling on resizing

    // redraw on resize
    if (getmaxx(stdscr) != oldx || getmaxy(stdscr) != oldy) {
      // clear colored cell
      colorCellBackground(&week, currd, currh, 1);
      drawCell(&week, currd, currh, true);
      //reset scroll bc doing that math is annoying
      currd = currh = 0;
      days.scrollX = 0;
      hours.scrollY = 0;
      week.scrollX = week.scrollY = 0;
      getmaxyx(stdscr, oldy, oldx);
      drawDays(&days);
      drawHours(&hours);
      drawWeek(&week);
      // redraw
      if (isHighlighted) {
        colorCellBackground(&week, currd, currh, 2); //highlight current cell
      }
    }

    // sleep so we dont have too many useless cycles refreshing
    usleep(1000 * 8); //about 120 fps //TODO make fps settable from calling from commandline
  }

  endwin();

  return 0;
}
