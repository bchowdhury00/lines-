#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

#define PI 3.14159265

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
  if (x0 < x1){
    double d = ((double)x1 - (double)x0)/2;
    *x = x0 + (int)d;
  }else{
    double d = ((double)x0 - (double)x1)/2;
    *x = x1 + (int)d;
  }
  if (y0 < y1){
    double d = ((double)y1 - (double)x0)/2;
    *y = y0 + (int)d;
  }else{
    double d = ((double)y0 - (double)y1)/2;
    *y = y1 + (int)d;
  }
}

void sierpinski_sieve(screen s,color c,int iterations){
    int x0 = XRES / 2;
    int y0 = XRES * sin(PI / 3);
    int x1 = 0;
    int y1 = 0;
    int x2 = XRES;
    int y2 = 0;
    draw_line(x0,y0,x1,y1,s,c);
    draw_line(x1,y1,x2,y2,s,c);
    draw_line(x2,y2,x0,y0,s,c);
    sierpinski_sieve_helper(s,c,iterations,x0,y0,x1,y1,x2,y2);
}

void sierpinski_sieve_helper(screen s, color c, int iterations, int x0, int y0,int x1,int y1,int x2,int y2){
  if (iterations <= 0){
    return;
  }
  int newx0, newx1, newx2, newy0,newy1,newy2;
  findMidpoint(x0,y0,x1,y1,&newx0,&newy0);
  findMidpoint(x1,y1,x2,y2,&newx1,&newy1);
  findMidpoint(x0,y0,x2,y2,&newx2,&newy2);
  draw_line(newx0,newy0,newx1,newy1,s,c);
  draw_line(newx1,newy1,newx2,newy2,s,c);
  draw_line(newx2,newy2,newx0,newy0,s,c);
  color newc;
  newc.red = rand() % 255;
  newc.blue = rand() % 255;
  newc.green = rand() % 255;
  sierpinski_sieve_helper(s,newc,iterations - 1,x0,y0,newx0,newy0,newx2,newy2);
  sierpinski_sieve_helper(s,newc,iterations - 1,newx0,newy0,x1,y1,newx1,newy1);
  sierpinski_sieve_helper(s,newc,iterations - 1,newx2,newy2,newx1,newy1,x2,y2);
  return;
}
