#include "week.h"
#include "customutils.h"

//------------------------------------------------------------------------------
// struct week
//------------------------------------------------------------------------------

// constructor
struct Week weekConst(int days, int hours, int tableYOffset, int tableXOffset,  WINDOW *pw) {
  struct Week temp;

  temp.parentWindow = pw;
  temp.tableYOffset = tableYOffset;
  temp.tableXOffset = tableXOffset;
  temp.days = days;
  temp.hours = hours;
  temp.cellLength = calcCellLength(getmaxx(temp.parentWindow), temp.days);
  temp.cellHeight = calcCellHeight(getmaxy(temp.parentWindow), temp.hours); // TODO dunno if tableheight is nescessary varaibale
  temp.scrollY = temp.scrollX = 0;

  // fill cellsContent with null or something
  for (int d=0; d<days; ++d) {
    for (int h=0; h<hours; ++h) {
      temp.cellsContent[d][h] = NULL;
    }
  }

  return temp;
}

void makeWeek(struct Week *w) {
  for (int d=0; d<(w->days); ++d) {
    for (int h=0; h<(w->hours); ++h) {
      // init a subwindow at d.cells[day][hour]
      w->cells[d][h] = subpad(w->parentWindow, w->cellHeight, w->cellLength, (w->cellHeight-1)*h, (w->cellLength-1)*d);
    }
  }
}

void drawCell(struct Week *w, int d, int h, bool refresh) {
  // border
  int topleft, topright, bottomleft, bottomright;
  topleft = topright = bottomleft = bottomright = ACS_PLUS;

  // find out bordertype
  if (d==0) {
    topleft = bottomleft = ACS_LTEE;
    if (h==0) {
      topleft = ACS_ULCORNER;
      topright = ACS_TTEE;
    } else if (h==(w->hours)-1) {
      bottomleft = ACS_LLCORNER;
      bottomright = ACS_BTEE;
    }
  } else if (d==(w->days)-1) {
    topright = bottomright = ACS_RTEE;
     if (h==0) {
      topleft = ACS_TTEE;
      topright = ACS_URCORNER;
    } else if (h==(w->hours)-1) {
      bottomleft = ACS_BTEE;
      bottomright = ACS_LRCORNER;
    }
  } else if (h==0) {
    topleft = topright = ACS_TTEE;
  } else if (h==(w->hours)-1) {
    bottomleft = bottomright = ACS_BTEE;
  }
  
  // draw border
  wborder(w->cells[d][h], 0, 0, 0, 0, topleft, topright, bottomleft, bottomright);
  if (refresh) {
    refreshCells(w);
  }
}

void refreshCells(struct Week *w) {
  prefresh(w->parentWindow, w->scrollY, w->scrollX, w->tableYOffset, w->tableXOffset, getmaxy(stdscr)-1, getmaxx(stdscr)-1);
}

void updateCell(struct Week *w, int d, int h, char *text, bool center) {
  int x,y;
  x = y = 1;
  if (center) {
    x = centerString(w->cellLength, stringLength(text));
  }
  mvwprintw(w->cells[d][h], y, x, text);
  refreshCells(w);
}

void colorCellBackground(struct Week *w, int d, int h, int colorpair) {
  // color background
  wbkgd(w->cells[d][h], COLOR_PAIR(colorpair));
  // redraw box so it looks fancier
  wborder(w->cells[d][h], 0, 0, 0, 0, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  refreshCells(w);
  wattroff(w->cells[d][h], COLOR_PAIR(colorpair));
}

void drawWeek(struct Week *w) {
  for (int d=0; d<(w->days); ++d) {
    for (int h=0; h<(w->hours); ++h) {
      // draw in drawcell so that code is more modular
      drawCell(w, d, h, false);
    }
  }
  refreshCells(w);
}

void scrollDown(struct Week *w) {
  if (w->scrollY<(getmaxy(w->parentWindow)-(getmaxy(stdscr)-w->tableYOffset))) {
    ++w->scrollY;
  }
  refreshCells(w);
}

void scrollUp(struct Week *w) {
  if (w->scrollY>0) {
    --w->scrollY;
  }
  refreshCells(w);
}

void scrollLeft(struct Week *w) {
  // increase scrolling speed
  for (int i=0; i<3; ++i) {
    if (w->scrollX>0) {
      --w->scrollX;
    } else {break;}
  }
  refreshCells(w);
}

void scrollRight(struct Week *w) {
  // increase scrolling speed 
  for (int i=0; i<3; ++i) {
    //tableheight-(maxheightofterminal-cellsoffset) = 37-(15-3);
    if (w->scrollX<(getmaxx(w->parentWindow)-(getmaxx(stdscr)-w->tableXOffset))) {
      ++w->scrollX;
    } else {break;}
  }
  refreshCells(w);
}
