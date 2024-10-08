#ifndef CUSTOMUTILS_H   /* Include guard */
#define CUSTOMUTILS_H

int max(int a, int b);

int min(int a, int b);

int stringLength(const char *string);

int centerString(int windowLength, int stringLength);

int calcCellHeight(int windowHeight, int hours);

int calcCellLength(int windowLength, int days);

#endif
