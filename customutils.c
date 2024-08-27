#include <ncurses.h>
#include <curses.h>
#include "customutils.h"

int max(int a, int b) {
  return (a>=b)*a + (b>a)*b;
}

int min(int a, int b) {
  return (a>=b)*b + (b>a)*a;
}

// find length of string
int stringLength(const char *string) {
  int ret = 0;
  while (*string != '\0') {
    ++ret;
    ++string;
  }

  return ret;
}

int centerString(int windowLength, int stringLength) {
  int windowHalf = windowLength/2;
  int stringHalf = stringLength/2;


  return windowHalf-stringHalf-1;
}
