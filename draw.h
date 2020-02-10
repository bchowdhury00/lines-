#include "ml6.h"

#ifndef DRAW_H
#define DRAW_H

void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
void octantOneLine(int x0, int y0, int x1, int y1, screen s, color c);
void octantTwoLine(int x0, int y0, int x1, int y1, screen s, color c);
void octantThreeLine(int x0, int y0, int x1, int y1, screen s, color c);
void octantFourLine(int x0, int y0, int x1, int y1, screen s, color c);
#endif
