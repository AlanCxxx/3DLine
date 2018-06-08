/*
  3D Bresenham's algorithm
  ========================

  Original Bressenham algorithm source:
  https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/
// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "/usr/include/graphics.h"
// Other Linker Options: -lXbgi -lX11 -lm

void line3d(int xOld,int yOld,int zOld,int xNew,int yNew,int zNew) {
  int i,n;
  int dx,dy,dz;
  int ax,ay,az;
  int sx,sy,sz;
  int mx,my,mz;
  int xStep,yStep,zStep;

  dx=xNew-xOld;
  dy=yNew-yOld;
  dz=zNew-zOld;
  ax=abs(dx);
  ay=abs(dy);
  az=abs(dz);
  // Sign function
  sx=dx<0?-1:dx>0?1:0;
  sy=dy<0?-1:dy>0?1:0;
  sz=dz<0?-1:dz>0?1:0;
  if ((ax>=ay)&&(ax>=az)) {
    mx=0;
    my=ay-(ax>>1);
    mz=az-(ax>>1);
    n=ax;
  } else if ((ay>=ax)&&(ay>=az)) {
    mx=ax-(ay>>1);
    my=0;
    mz=az-(ay>>1);
    n=ay;
  } else {
    mx=ax-(az>>1);
    my=ay-(az>>1);
    mz=0;
    n=az;
  }

  for (i=1;i<=n;i++) {
    xStep=0;
    yStep=0;
    zStep=0;
    if ((ax>=ay)&&(ax>=az)) {
      if (my>=0) {
        my-=ax;
        yStep=sy;
      }
      if (mz>=0) {
        mz-=ax;
        zStep=sz;
      }
      my+=ay;
      mz+=az;
      xStep=sx;
    } else if ((ay>=ax)&&(ay>=az)) {
      if (mx>=0) {
        mx-=ay;
        xStep=sx;
      }
      if (mz>=0) {
        mz-=ay;
        zStep=sz;
      }
      mx+=ax;
      mz+=az;
      yStep=sy;
    } else {
      if (mx>=0) {
        mx-=az;
        xStep=sx;
      }
      if (my>=0) {
        my-=az;
        yStep=sy;
      }
      mx+=ax;
      my+=ay;
      zStep=sz;
    }
    putpixel(xOld,yOld,BLACK);
    xOld+=xStep;
    yOld+=yStep;
    zOld+=zStep;
    putpixel(xOld,yOld,BLACK);
  }
}

int main(void)
{
  // Display results
  initwindow(900,700);
  setbkcolor(WHITE);
  cleardevice();
  setcolor(BLACK);
  setlinestyle(SOLID_LINE,EMPTY_FILL,NORM_WIDTH);
  setfillstyle(SOLID_FILL,WHITE);

  // Units are pixels
  setcolor(RED);
  line(200,700-100,600,700-100);
  line(600,700-100,600,700-500);
  line(600,700-500,200,700-500);
  line(200,700-500,200,700-100);
  setcolor(BLACK);

  // Overlay my version on line
  line3d(200,700-100,0,600,700-100,0);
  line3d(600,700-100,0,600,700-500,0);
  line3d(600,700-500,0,200,700-500,0);
  line3d(200,700-500,0,200,700-100,0);

  printf("Done - Enter to exit");
  getchar();
  closegraph();

  return(0);
}
