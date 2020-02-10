#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
    if (x1 == x0){
        if (y0 > y1){
            return octantThreeLine(x0,y0,x1,y1,s,c);
        }else{
            return octantThreeLine(x1,y1,x0,y0,s,c);
        }
    }
    double m = ((double)(y1 - y0) / (double)(x1 - x0));
    printf("m = [%lf]\n",m);
    if (m <= 1 && m >= 0){
        if (x1 > x0){
            return octantOneLine(x0,y0,x1,y1,s,c);
        }else{
            return octantOneLine(x1,y1,x0,y0,s,c);
        }
    }
    if (m > 1){
        if (y1 > y0){
            return octantTwoLine(x0,y0,x1,y1,s,c);
        }else{
            return octantTwoLine(x1,y1,x0,y0,s,c);
        }
    }
    if (m <= -1){
        if (y0 > y1){
            return octantThreeLine(x0,y0,x1,y1,s,c);
        }else{
            return octantThreeLine(x1,y1,x0,y0,s,c);
        }
    }
    if (m < 0 && m > -1){
        if (y0 > y1){
            return octantFourLine(x0,y0,x1,y1,s,c);
        }else{
            return octantFourLine(x1,y1,x0,y0,s,c);
        }
    }
}

void octantOneLine(int x0, int y0, int x1, int y1, screen s, color c){
    int x = x0;
    int y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;
    int A = deltaY;
    int B = -deltaX;
    int D = (2 * A) + B;
    while (x < x1){
        plot(s,c,x,y);
        if (D > 0){
            D += 2 * B;
            y += 1;
        }
        D += 2 * A;
        x += 1;
    }
}

void octantTwoLine(int x0, int y0, int x1, int y1, screen s, color c){
    int x = x0;
    int y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;
    int A = deltaY;
    int B = -deltaX;
    int D = A + (B * 2);
    while (y < y1){
        plot(s,c,x,y);
        if (D < 0){
            D += 2 * A;
            x += 1;
        }
        D += 2 * B;
        y += 1;
    }
}

void octantThreeLine(int x0, int y0, int x1, int y1, screen s, color c){
    int x = x0;
    int y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;
    int A = deltaY;
    int B = -deltaX;
    int D = A + (2 * B);
    while (y > y1){
        plot(s,c,x,y);
        if (D > 0){
            D += 2 * A;
            x += 1;
        }
        D -= 2 * B;
        y -= 1;
    }
}

void octantFourLine(int x0, int y0, int x1, int y1, screen s, color c){
    int x = x0;
    int y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;
    int A = deltaY;
    int B = -deltaX;
    int D = 2 * A + B;
    while (x < x1){
        plot(s,c,x,y);
        if (D < 0){
            D -= 2 * B;
            y -= 1;
        }
        D += 2 * A;
        x += 1;
    }
}

void findMidpoint(int x0,int y0, int x1, int y1, int * x, int * y){
  double x2 = ((double)x1 - (double)x0)/2;
  double y2 = ((double)y1 - (double)y0)/2;
  *x = floor(x2);
  *y = floor(y2);
  return;
}

void sierpinski_sieve(screen s, color c, int iterations, int x0, int y0,int x1,int x2,int x3){
  if (iterations <= 0){
    return;
  }
  int * newx0, newx1, newx2, newy0,newy1,newy2;
  findMidpoint(x0,y0,x1,y1,newx0,newy0);
  findMidpoint(x0,y0,x2,y2,newx1,newy1);
  findMidpoint(x1,y1,x2,y2,newx2,newy2);
  draw_line(newx0,newy0,newx1,newy1,s,c);
  draw_line(newx1,newy1,newx2,newy2,s,c);
  draw_line(newx0,newy0,newx2,newy2,s,c);


}
