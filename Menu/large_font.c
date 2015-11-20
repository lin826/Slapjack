#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw2.h"
/*
putASCII2()  �̫��ӰѼƤ��O�O�r���e���M�I�����C��
�i�H�ѦҤU�����C��ȹ�Ӫ�ӳ]�w�A�Q�n���C��
   0: ��     1: �t��   2: �t��   3: �t�C
   4: �t��   5: �t��   6: �t��   7: �L��
   8: �t��   9: �G��  10: �G��  11: �G�C
  12: �G��  13: �G��  14: �G��  15: ��
*/
typedef struct _font {
    int height;
    int width;
    char *pixel;
} Font;

void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color);

Font * read_font(char *pixel_file);
char getpixel(Font *ip, int x, int y);

void show_font(Font *ip, char letter, int offx, int offy, int fg_color, int bg_color);
void destroy_font(Font *ip);

int main(void)
{
    Font *large_font = read_font("font.txt");

            putStringLarge(large_font, 10, 10, "SAMPLE PROGRAM", 10, 1);
            putStringLarge(large_font, 10, 16, "h", 10, 4);
            putStringLarge(large_font, 18, 16, "e", 10, 6);
            putStringLarge(large_font, 26, 16, "l", 10, 2);
            putStringLarge(large_font, 34, 16, "l", 10, 1);
            putStringLarge(large_font, 42, 16, "0", 10, 5);

            drawCmdWindow();  /* update window immediately */

    return 0;
}

void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color)
{
    int i;
    for(i=0; i<strlen(p); i++) {
        show_font(fp,  p[i], x+i*fp->width, y, fg_color, bg_color);
    }
}


Font * read_font(char *pixel_file)
{
    FILE *fid;
    int height, width, num, i, j, k;
    Font *p;

    fid = fopen(pixel_file, "r");

    if (fid==NULL) {
        return NULL;
    } else {
        fscanf(fid, "%d%d%d", &height, &width, &num);
        p = (Font*) malloc(sizeof(Font));
        p->height = height;
        p->width = width;
        p->pixel = (char*) malloc(sizeof(char)*height*width*num);
        fscanf(fid, "%*c");
        for (k=0; k<num; k++) {
            for (i=0; i<height; i++) {
                for (j=0; j<width; j++) {
                    fscanf(fid, "%c", & (p->pixel[k*width*height+i*width+j]));
                }
                fscanf(fid, "%*c");
            }
        }
        fclose(fid);

        return p;
    }
}

char getpixel(Font *ip, int x, int y)
{
    return ip->pixel[y*ip->width + x];
}



void show_font(Font *ip, char letter, int offx, int offy, int fg_color, int bg_color)
{
    int x, y;
    char c;
    int shift;
    if (letter==' ') return;
    if (isdigit(letter)) {
        shift = ip->height*(26 + letter-'0');
    } else {
        shift = ip->height*(toupper(letter)-'A');
    }
    for (y=0; y<ip->height; y++) {
            for (x=0; x<ip->width; x++) {
            c = getpixel(ip, x, y+shift);
            if (c!=' ')
            putASCII2( x + offx,
                y + offy, '@', fg_color, bg_color);
            }
    }
}

void destroy_font(Font *ip)
{
    free(ip->pixel);
    free(ip);
}
