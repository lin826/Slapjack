#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw2.h"
#include "kb_input2.h"

typedef struct _image
{
    int row;
    int col;
    char *pixel;
    int *color;
} Image;

void destroy_image(Image *ip);
Image * read_image(char *pixel_file, char *color_file);
void show_image(Image *ip, int offx, int offy);
void destroy_image(Image *ip);
char getimgpixel(Image *ip, int x, int y);
int getimgcolor(Image *ip, int x, int y);

Image poke[55];

int setup(void)
{
    //Declare a Image, ex. Image *zebra = read_image("zebraOri_trans.pixel","zebraOri_trans.color");
    Image *peach1 = read_image("peach1.pixel","peach1.color");
    Image *peach2 = read_image("peach2.pixel","peach2.color");
    Image *peach3 = read_image("peach3.pixel","peach3.color");
    Image *peach4 = read_image("peach4.pixel","peach4.color");
    Image *peach5 = read_image("peach5.pixel","peach5.color");
    Image *peach6 = read_image("peach6.pixel","peach6.color");
    Image *peach7 = read_image("peach7.pixel","peach7.color");
    Image *peach8 = read_image("peach8.pixel","peach8.color");
    Image *peach9 = read_image("peach9.pixel","peach9.color");
    Image *peach10 = read_image("peach10.pixel","peach10.color");
    Image *peach11 = read_image("peach11.pixel","peach11.color");
    Image *peach12 = read_image("peach12.pixel","peach12.color");
    Image *peach13 = read_image("peach13.pixel","peach13.color");
    Image *heart1 = read_image("heart1.pixel","heart1.color");
    Image *heart2 = read_image("heart2.pixel","heart2.color");
    Image *heart3 = read_image("heart3.pixel","heart3.color");
    Image *heart4 = read_image("heart4.pixel","heart4.color");
    Image *heart5 = read_image("heart5.pixel","heart5.color");
    Image *heart6 = read_image("heart6.pixel","heart6.color");
    Image *heart7 = read_image("heart7.pixel","heart7.color");
    Image *heart8 = read_image("heart8.pixel","heart8.color");
    Image *heart9 = read_image("heart9.pixel","heart9.color");
    Image *heart10 = read_image("heart10.pixel","heart10.color");
    Image *heart11 = read_image("heart11.pixel","heart11.color");
    Image *heart12 = read_image("heart12.pixel","heart12.color");
    Image *heart13 = read_image("heart13.pixel","heart13.color");
    Image *clubs1 = read_image("clubs1.pixel","clubs1.color");
    Image *clubs2 = read_image("clubs2.pixel","clubs2.color");
    Image *clubs3 = read_image("clubs3.pixel","clubs3.color");
    Image *clubs4 = read_image("clubs4.pixel","clubs4.color");
    Image *clubs5 = read_image("clubs5.pixel","clubs5.color");
    Image *clubs6 = read_image("clubs6.pixel","clubs6.color");
    Image *clubs7 = read_image("clubs7.pixel","clubs7.color");
    Image *clubs8 = read_image("clubs8.pixel","clubs8.color");
    Image *clubs9 = read_image("clubs9.pixel","clubs9.color");
    Image *clubs10 = read_image("clubs10.pixel","clubs10.color");
    Image *clubs11 = read_image("clubs11.pixel","clubs11.color");
    Image *clubs12 = read_image("clubs12.pixel","clubs12.color");
    Image *clubs13 = read_image("clubs13.pixel","clubs13.color");
    Image *dimon1 = read_image("dimon1.pixel","dimon1.color");
    Image *dimon2 = read_image("dimon2.pixel","dimon2.color");
    Image *dimon3 = read_image("dimon3.pixel","dimon3.color");
    Image *dimon4 = read_image("dimon4.pixel","dimon4.color");
    Image *dimon5 = read_image("dimon5.pixel","dimon5.color");
    Image *dimon6 = read_image("dimon6.pixel","dimon6.color");
    Image *dimon7 = read_image("dimon7.pixel","dimon7.color");
    Image *dimon8 = read_image("dimon8.pixel","dimon8.color");
    Image *dimon9 = read_image("dimon9.pixel","dimon9.color");
    Image *dimon10 = read_image("dimon10.pixel","dimon10.color");
    Image *dimon11 = read_image("dimon11.pixel","dimon11.color");
    Image *dimon12 = read_image("dimon12.pixel","dimon12.color");
    Image *dimon13 = read_image("dimon13.pixel","dimon13.color");
    Image *poker1 = read_image("poker1.pixel","poker1.color");
    Image *poker2 = read_image("poker2.pixel","poker2.color");
    Image *poker3 = read_image("poker3.pixel","poker3.color");



    Image poke[55]= {*peach1,*peach2,*peach3,*peach4,*peach5,*peach6,*peach7,*peach8,*peach9,*peach10,*peach11,*peach12,*peach13,*heart1,
                     *heart1,*heart2,*heart3,*heart4,*heart5,*heart6,*heart7,*heart8,*heart9,*heart10,*heart11,*heart12,*heart13,
                     *dimon1,*dimon2,*dimon3,*dimon4,*dimon5,*dimon6,*dimon7,*dimon8,*dimon9,*dimon10,*dimon11,*dimon12,*dimon13,
                     *poker1,*poker2,*poker3
                    };
    //while(1){
    //clearScreen();
    //Put Image on Screen at coordinates 10,10, ex. show_image(zebra,10,10);
    //show_image(heart1,50,0);
    //show_image(poker1,110,30);
    //drawCmdWindow();  /* update window immediately */
    //Sleep(300); // <--- Sleep()�����Oms, sleep()�����Os
    //}

    //Free you memory before close your program, ex. destroy_image(zebra);
    //destroy_image(heart1);
    return 0;
}

void putString(int x, int y, char *p, int fg_color, int bg_color)
{
    int i;
    for(i=0; i<strlen(p); i++)
    {
        putASCII2(x+i, y, p[i], fg_color, bg_color);
    }
}

Image * read_image(char *pixel_file, char *color_file)
{
    FILE *fid1, *fid2;
    int row, col, i, j;
    Image *p;

    fid1 = fopen(pixel_file, "r");
    fid2 = fopen(color_file, "r");
    if (fid1==NULL || fid2==NULL)
    {
        return NULL;
    }
    else
    {
        fscanf(fid1, "%d%d", &row, &col);
        fscanf(fid2, "%d%d", &row, &col); // supposedly, size should be the same
        p = (Image*) malloc(sizeof(Image));
        p->row = row;
        p->col = col;
        p->pixel = (char*) malloc(sizeof(char)*row*col);
        p->color = (int*) malloc(sizeof(int)*row*col);
        fscanf(fid1, "%*c");
        for (i=0; i<row; i++)
        {
            for (j=0; j<col; j++)
            {
                fscanf(fid1, "%c", & (p->pixel[i*col+j]));
                fscanf(fid2, "%1x", & (p->color[i*col+j]));
            }
            fscanf(fid1, "%*c");
            fscanf(fid2, "%*c");
        }
        fclose(fid1);
        fclose(fid2);
        return p;
    }
}

char getimgpixel(Image *ip, int x, int y)
{
    return ip->pixel[y*ip->col + x];
}

int getimgcolor(Image *ip, int x, int y)
{
    return ip->color[y*ip->col + x];
}

void show_image(Image *ip, int offx, int offy)
{
    int x, y;
    char c;
    for (y=0; y<ip->row; y++)
    {
        for (x=0; x<ip->col; x++)
        {
            c = getimgpixel(ip, x, y);
            if (c!=' ')
                putASCII2( x + offx,
                           y + offy, c, getimgcolor(ip, x, y), 0);
        }
    }
}
void destroy_image(Image *ip)
{
    free(ip->pixel);
    free(ip->color);
    free(ip);
}
