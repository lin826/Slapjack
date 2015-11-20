//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
//陳琦是蠢包!!!!!!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
#include "audio.h"
#include "console_draw2.h"
#include "kb_input2.h"

#define START_PLANE 3
#define WAIT_TIME   1000

/*
putASCII2()  最後兩個參數分別是字元前景和背景的顏色
可以參考下面的顏色值對照表來設定你想要的顏色
   0: 黑     1: 暗藍   2: 暗綠   3: 暗青
   4: 暗紅   5: 暗紫   6: 暗黃   7: 淺灰
   8: 暗灰   9: 亮藍  10: 亮綠  11: 亮青
  12: 亮紅  13: 亮紫  14: 亮黃  15: 白
*/

typedef struct _image
{
    int row;
    int col;
    char *pixel;
    int *color;
} Image;

typedef struct _font
{
    int height;
    int width;
    char *pixel;
} Font;

typedef struct _place
{
    int x;
    int y;
} Place;

Image * read_image(char *pixel_file, char *color_file);
void show_image(Image *ip, int offx, int offy);
void destroy_image(Image *ip);
char getimgpixel(Image *ip, int x, int y);
int getimgcolor(Image *ip, int x, int y);

void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color);

Font * read_font(char *pixel_file);
char getpixel(Font *ip, int x, int y);

void show_font(Font *ip, char letter, int offx, int offy, int fg_color, int bg_color);
void destroy_font(Font *ip);
const char *readLine(FILE *file);


void initAudio();
void initAudioNUM();
void start();
void gameover();
void Loser();
void Winner();
void Winner2(int x,int y);
void Loser2(int x,int y);
void playAudioNUM(int index);

int n=0;
int showingPlane; // 0: 歡迎畫面 1: 主選單 2: 單人 Game 3: 雙人 Game 4: Help
Font *large_font;
int winTimes=0,loseTimes=0;
int count = 0;
int turn=0; // 0:Player 1:AI

Place *poker_place;
Place *counting_place;


//audio
Audio audioWin[2];
Audio audioLose[2];
Audio audioOver[6];
Audio audio[1];

Audio audioNUM[13][2];

Image **poker;
Image *countingNum;

int main(void)
{
    initImage();
    initPlace();

    large_font = read_font("font.txt");
    initAudio();
    initAudioNUM();

    int IsEnding = 0;
    showingPlane = START_PLANE;

    while (!IsEnding)
    {
        clearScreen();

        switch (showingPlane)
        {
        case 0:
            start();
            showingPlane = 1;
            break;
        case 1:
            Menu();
            break;
        case 2:
            SinglePlayer();
            break;
        case 3:
            MuitiplePlayers();
            break;
        case 4:
            ShowHelp();
            showingPlane = 1;
            break;
        }

        drawCmdWindow();

    } /* while (IsEnding) */

    return 0;
}

void Menu(void)
{
    /* 啟動鍵盤控制 */
    initializeKeyInput();
    //show_image(poker[0][3],150,100);


    char ch;
    int place = 0;
    int color1[3];
    int color2[3];

    //initialize bottoms
    int i;
    for( i=0; i<3; i++)
    {
        if(i==n)
        {
            color1[i] = 12;
            color2[i] = 12;
        }
        else
        {
            color1[i] = 2;
            color2[i] = 2;
        }
    }

    putStringLarge(large_font, 100, 20, "MENU", 15, 15);
    putStringLarge(large_font, 50, 30+10*1, "Single Player Mode", color1[0], color2[0]);
    putStringLarge(large_font, 50, 30+10*2, "Two Players Mode", color1[1], color2[1]);
    putStringLarge(large_font, 50, 30+10*3, "Help", color1[2], color2[2]);
    putStringLarge(large_font, 180, 100, "CTRL TO SETECT", 7, 7);

    ch = getKeyEventVirtual();

    switch(ch)
    {
    case VK_UP:
        n = (n+2)%3;
        break;
    case VK_DOWN:
        n = (n+1)%3;
        break;
    case VK_CONTROL:
        switch(n)
        {
        case 0:
            showingPlane = 2;
            break;
        case 1:
            showingPlane = 3;
            break;
        case 2:
            showingPlane = 4;
            break;
        default:
            break;
        }
    }

}

void SinglePlayer(void)
{
    /* 啟動鍵盤控制 */
    initializeKeyInput();
    char ch='0';
    winTimes=0;  //Left
    loseTimes=0;
    count = 0;
    int pick = -1;
    int initime=clock();
    int time;

    while(winTimes<3 && loseTimes<3)
    {

        clearScreen();
        if(turn == 0)
        {
            ch = getKeyEventVirtual();
            switch(ch)
            {
            case 0x58: //左方拍桌

                check(pick,initime);
                initime = clock();
                break;
            case 0x5A:
                if(count==pick)
                {
                    Loser();
                }
                else
                    getNewCard();
                initime = clock();
                break;
            }
        }
        else
        {
            if(waitForKeyDown(3.0))
            {
                ch = getKeyEventVirtual();
                if(ch == 0x58){
                    check(pick,initime);
                    initime = clock();
                }
            }
            else //if(tick > WAIT_TIME)
            {
                getNewCard();
                initime = clock();
            }
        }
    }
    if(loseTimes==3)
        gameover();
    showingPlane =2;
}

void check(int pick,int initime)
{
    int time = initime - clock();
    if(count==pick)
    {
        if(time<WAIT_TIME)
        {
            winTimes++;
            changeTurn();
        }
        else
        {
            Loser();
        }
    }
    else
    {
        Loser();
    }
}

void getNewCard(){
    count = count%13 +1;
    int ran = rand()%4;
    int pick = rand()%14+1;
    ran = 13*ran + pick -1;
    show_image(*(poker+ran),(*(poker_place+(count%4))).x,(*(poker_place+(count%4))).y);
    //show_image(*(countingNum+ran),*(counting_place+(count%2)).x,*(poker_place+(count%2)).y);
    temp_ShowCounting(count);
}

void temp_ShowCounting(count)
{
    char *card;
    card = (char*)malloc(sizeof(char));
    *(card+1) = '\0';
    if(count<10)
        *card = ('0'+count);
    else if(count == 11)
        *card = '+';
    else if(count == 11)
        *card = 'J';
    else if(count == 12)
        *card = 'Q';
    else if(count == 13)
        *card = 'K';
    putStringLarge(large_font, 10, 40, "NUM   ", (*(counting_place+(count%2))).x,(*(poker_place+(count%2))).y);
    putStringLarge(large_font, 50, 40, card, (*(counting_place+(count%2))).x+20,(*(poker_place+(count%2))).y);
    drawCmdWindow();
    free(card);
}

void changeTurn()
{
    turn = (turn+1)%2;
}

void showTable()
{
    temp_ShowCounting(count);
    temp_ShowCounting((count+12)%13 +1); //前一個數字
}

void MuitiplePlayers(void)
{
    Font *large_font = read_font("font.txt");
    /* 啟動鍵盤控制 */
    initializeKeyInput();
    char ch,prech='0';
    char *card;
    card = (char*)malloc(sizeof(char));
    *(card+1) = '\0';

    int isWin=0,isLose=0;
    int count = 0, pick;
    int initime =clock(), time;
    int turn=2; // 1:Right 2:Left

    while(isWin<3 && isLose<3)
    {
        clearScreen();
        time = clock() - initime;

        ch = getKeyEventVirtual();
        switch(ch)
        {
        case VK_LEFT: //右方拍桌
            if(( count==pick && time<10 )|| count==14)
            {
                //win(10);
                putStringLarge(large_font, 200, 20, "YOU WIN!!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 2;
                time = 0;
                isLose++;
            }
            else if(count==pick)
            {//show_image(*(poker+1),0,0);
    //drawCmdWindow();
                //AIwin();
                putStringLarge(large_font, 200, 20, "YOU LOSE! How slow you are!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 1;
                time = 0;
                isWin++;
            }

            else
            {
                //lose(10);
                putStringLarge(large_font, 200, 20, "YOU LOSE! Watch out the number!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 1;
                time = 0;
                isWin++;
            }
            break;

            break;
        case 0x58: //左方拍桌
            if(( count==pick && time<10 )|| count==14)
            {
                //win(10);
                putStringLarge(large_font, 10, 20, "YOU WIN!!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 1;
                time = 0;
                isWin++;
            }
            else if(count==pick)
            {
                //AIwin();
                putStringLarge(large_font, 10, 20, "YOU LOSE! How slow you are!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 2;
                time = 0;
                isLose++;
            }

            else
            {
                //lose(10);
                putStringLarge(large_font, 10, 20, "YOU LOSE! Watch out the number!", 15, 15);
                drawCmdWindow();//show_image(*(poker+1),0,0);
    //drawCmdWindow();
                Sleep(200);
                turn = 2;
                time = 0;
                isLose++;
            }
            break;

        case 0x5A: //左方發牌
            if(count==pick|| count==14)
            {
                putStringLarge(large_font, 10, 20, "YOU LOSE! Watch out the number!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 2;
                time = 0;
                isLose++;
            }
            else if(turn == 2)
            {
                count = count%13 +1;
                if(count<11)
                    *card = ('0'+count);
                else if(count == 11)
                    *card = 'J';
                else if(count == 12)
                    *card = 'Q';
                else if(count == 13)
                    *card = 'K';
                putStringLarge(large_font, 100, 40, "NUM   ", 0, 15);
                putStringLarge(large_font, 150, 40, card, 0, 15);
                pick = (rand()%13)+1;
                if(pick<11)
                    *card = ('0'+pick);
                else if(pick == 11)
                    *card = 'J';
                else if(pick == 12)
                    *card = 'Q';
                else if(pick == 13)
                    *card = 'K';
                else if(pick == 14)
                    *card = 'P';
                putStringLarge(large_font, 100, 50, "CARD  ", 0, 15);
                putStringLarge(large_font, 150, 50, card, 0, 15);
                time = 0;
                turn = 1;
                int ran = (rand()%4)+1;
                //show_image(poker[0][0],100,20);
                drawCmdWindow();
            }//show_image(*(poker+1),0,0);
    //drawCmdWindow();
            break;
        case VK_DOWN: //右方發牌
            if(count==pick|| count==14)
            {
                putStringLarge(large_font, 200, 20, "YOU LOSE! Watch out the number!", 15, 15);
                drawCmdWindow();
                Sleep(200);
                turn = 1;
                time = 0;
                isWin++;
            }
            else if(turn == 1)
            {
                count = count%13 +1;
                if(count<11)
                    *card = ('0'+count);
                else if(count == 11)
                    *card = 'J';
                else if(count == 12)
                    *card = 'Q';
                else if(count == 13)
                    *card = 'K';
                putStringLarge(large_font, 100, 40, "NUM   ", 0, 15);
                putStringLarge(large_font, 150, 40, card, 0, 15);
                pick = (rand()%13)+1;
                if(pick<11)
                    *card = ('0'+pick);
                else if(pick == 11)
                    *card = 'J';
                else if(pick == 12)
                    *card = 'Q';
                else if(pick == 13)
                    *card = 'K';
                else if(pick == 14)
                    *card = 'P';
                putStringLarge(large_font, 100, 50, "CARD  ", 0, 15);
                putStringLarge(large_font, 150, 50, card, 0, 15);
                time = 0;
                turn = 2;
                int ran = (rand()%4)+1;
                //show_image(poker[0][0],100,20);
                drawCmdWindow();
            }
            break;//show_image(*(poker+1),0,0);
    //drawCmdWindow();

        case VK_ESCAPE:
            break;
        }

    }
    if(winTimes==3)
    {
        Loser2(50,35);//send location
        Winner2(300,35);//send location
        showingPlane =1;
    }
    else if(loseTimes==3)
    {
        Loser2(300,35);//send location
        Winner2(50,35);//send location
        showingPlane =1;
    }
}

void ShowHelp(void)
{
    clearScreen();
    Image *help = read_image("help.pixel","help.color");
    show_image(help,100,10);
    drawCmdWindow();  /* update window immediately */
    Sleep(500); // <--- Sleep()單位是ms, sleep()單位是s

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
    drawCmdWindow();
}
void destroy_image(Image *ip)
{
    free(ip->pixel);
    free(ip->color);
    free(ip);
}

void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color)
{
    int i;
    for(i=0; i<strlen(p); i++)
    {
        show_font(fp,  p[i], x+i*fp->width, y, fg_color, bg_color);
    }
}

Font * read_font(char *pixel_file)
{
    FILE *fid;
    int height, width, num, i, j, k;
    Font *p;

    fid = fopen(pixel_file, "r");

    if (fid==NULL)
    {
        return NULL;
    }
    else
    {
        fscanf(fid, "%d%d%d", &height, &width, &num);
        p = (Font*) malloc(sizeof(Font));
        p->height = height;
        p->width = width;
        p->pixel = (char*) malloc(sizeof(char)*height*width*num);
        fscanf(fid, "%*c");
        for (k=0; k<num; k++)
        {
            for (i=0; i<height; i++)
            {
                for (j=0; j<width; j++)
                {
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
    if (isdigit(letter))
    {
        shift = ip->height*(26 + letter-'0');
    }
    else
    {
        shift = ip->height*(toupper(letter)-'A');
    }
    for (y=0; y<ip->height; y++)
    {
        for (x=0; x<ip->width; x++)
        {
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

const char *readLine(FILE *file)
{

    if (file == NULL)
    {
        printf("Error: file pointer is null.");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL)
    {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF))
    {
        if (count == maximumLineLength)
        {
            maximumLineLength += 128;
            lineBuffer = realloc(lineBuffer, maximumLineLength);
            if (lineBuffer == NULL)
            {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        }
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';
    char line[count + 1];
    strncpy(line, lineBuffer, (count + 1));
    free(lineBuffer);
    const char *constLine = line;
    return constLine;
}

void initImage()
{
    poker = (Image**)malloc(sizeof(Image*));
    *poker = (Image*)malloc(sizeof(Image)*56);
    countingNum = (Image*)malloc(sizeof(Image)*13);
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

    *(poker+0) = peach1;
    *(poker+1) = peach2;
    *(poker+2) = peach3;
    *(poker+3) = peach4;
    *(poker+4) = peach5;
    *(poker+5) = peach6;
    *(poker+6) = peach7;
    *(poker+7) = peach8;
    *(poker+8) = peach9;
    *(poker+9) = peach10;
    *(poker+10) = peach11;
    *(poker+11) = peach12;
    *(poker+12) = peach13;
    *(poker+13) = poker3;
    *(poker+14) = heart1;
    *(poker+15) = heart2;
    *(poker+16) = heart3;
    *(poker+17) = heart4;
    *(poker+18) = heart5;
    *(poker+19) = heart6;
    *(poker+20) = heart7;
    *(poker+21) = heart8;
    *(poker+22) = heart9;
    *(poker+23) = heart10;
    *(poker+24) = heart11;
    *(poker+25) = heart12;
    *(poker+26) = heart13;
    *(poker+27) = poker1;
    *(poker+28) = dimon1;
    *(poker+29) = dimon2;
    *(poker+30) = dimon3;
    *(poker+31) = dimon4;
    *(poker+32) = dimon5;
    *(poker+33) = dimon6;
    *(poker+34) = dimon7;
    *(poker+35) = dimon8;
    *(poker+36) = dimon9;
    *(poker+37) = dimon10;
    *(poker+38) = dimon11;
    *(poker+39) = dimon12;
    *(poker+40) = dimon13;
    *(poker+41) = poker2;
    *(poker+42) = clubs1;
    *(poker+43) = clubs2;
    *(poker+44) = clubs3;
    *(poker+45) = clubs4;
    *(poker+46) = clubs5;
    *(poker+47) = clubs6;
    *(poker+48) = clubs7;
    *(poker+49) = clubs8;
    *(poker+50) = clubs9;
    *(poker+51) = clubs10;
    *(poker+52) = clubs11;
    *(poker+53) = clubs12;
    *(poker+54) = clubs13;
    *(poker+55) = poker3;
}

void initAudio()
{
    //win
    openAudioFile("applaus.wav", &audioWin[0]);
    openAudioFile("ccheer.wav", &audioWin[1]);

    //lose
    openAudioFile("fart.wav", &audioLose[0]);
    openAudioFile("fart2.wav", &audioLose[1]);

    //game over
    openAudioFile("falling.wav", &audioOver[0]);
    openAudioFile("Hahaha.wav", &audioOver[1]);
    openAudioFile("laughcartoon.wav", &audioOver[2]);
    openAudioFile("manha.wav", &audioOver[3]);
    openAudioFile("scream.wav", &audioOver[4]);
    openAudioFile("tarzan.wav", &audioOver[5]);

    //start heart
    openAudioFile("heart.wav", &audio[0]);
}

void initAudioNUM()
{

    openAudioFile("1.wav", &audioNUM[0][0]);
    openAudioFile("1_2.wav", &audioNUM[0][1]);

    openAudioFile("2.wav", &audioNUM[1][0]);
    openAudioFile("2_1.wav", &audioNUM[1][1]);

    openAudioFile("3.wav", &audioNUM[2][0]);
    openAudioFile("3.wav", &audioNUM[2][1]);

    openAudioFile("4.wav", &audioNUM[3][0]);
    openAudioFile("4_1.wav", &audioNUM[3][1]);

    openAudioFile("5.wav", &audioNUM[4][0]);
    openAudioFile("5_1.wav", &audioNUM[4][1]);

    openAudioFile("6.wav", &audioNUM[5][0]);
    openAudioFile("6.wav", &audioNUM[5][1]);

    openAudioFile("7.wav", &audioNUM[6][0]);
    openAudioFile("7.wav", &audioNUM[6][1]);

    openAudioFile("8.wav", &audioNUM[7][0]);
    openAudioFile("8_1.wav", &audioNUM[7][1]);

    openAudioFile("9.wav", &audioNUM[8][0]);
    openAudioFile("9_1.wav", &audioNUM[8][1]);

    openAudioFile("10.wav", &audioNUM[9][0]);
    openAudioFile("10_1.wav", &audioNUM[9][1]);

    openAudioFile("11.wav", &audioNUM[10][0]);
    openAudioFile("11.wav", &audioNUM[10][1]);

    openAudioFile("12.wav", &audioNUM[11][0]);
    openAudioFile("12_1.wav", &audioNUM[11][1]);

    openAudioFile("13.wav", &audioNUM[12][0]);
    openAudioFile("13.wav", &audioNUM[12][1]);
}

void playAudioNUM(int index)
{

    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    for(i=0; i<1; i++)
    {
        playAudio(&audioNUM[index][ran]);
        Sleep(0);
    }


}

void pauseAudioNUM(int index)
{
    pauseAudio(&audioNUM[index][0]);
    pauseAudio(&audioNUM[index][1]);

}

void start()
{
    int count=1;
    int ok=0;
    Image *start;
    int time=20;//29
    while(time--)
    {

        clearScreen();
        switch(count)
        {
        case 1:
            start= read_image("start1.pixel","start1.color");
            break;
        case 2:
            start= read_image("start2.pixel","start2.color");
            break;
        case 3:
            start= read_image("start3.pixel","start3.color");
            break;
        case 4:
            start= read_image("start4.pixel","start4.color");
            break;
        case 5:
            start= read_image("start5.pixel","start5.color");
            break;
        case 6:
            start= read_image("start6.pixel","start6.color");
            break;
        case 7:
            start= read_image("start7.pixel","start7.color");
            break;
        case 8:
            start= read_image("start8.pixel","start8.color");
            break;
        case 9:
            start= read_image("start9.pixel","start9.color");
            break;
        case 10:
            start= read_image("start10.pixel","start10.color");
            break;
        case 11:
            start= read_image("start11.pixel","start11.color");
            break;
        case 12:
            start= read_image("start12.pixel","start12.color");
            break;
        case 13:
            start= read_image("start13.pixel","start13.color");
            break;
        case 14:
            start= read_image("start14.pixel","start14.color");
            break;
        case 15:
            start= read_image("start15.pixel","start15.color");
            break;
        case 16:
            start= read_image("start16.pixel","start16.color");
            break;
        default:
            break;


        }

        if(count==16)
        {
            ok=1;
        }
        if(ok)
        {
            // count=(count+1)%16+10;
            if(count==15)
            {
                count=16;
            }
            else
            {
                count=15;
            }

        }
        else
        {
            count++;
        }
        show_image(start,125,35);
        drawCmdWindow();
        int i=0;
        for(i=0; i<1; i++)
        {
            playAudio(&audio[0]);
            //Sleep(500);
        }

        Sleep(500);
    }
    destroy_image(start);

}

void gameover()
{
    int count=2;
    Image *gameover;

    int ran,i;
    srand( time(NULL) );
    ran=rand()%6;

    while(count<=11)
    {

        clearScreen();
        switch(count)
        {

        case 2:
            gameover= read_image("gameover2.pixel","gameover2.color");
            break;
        case 3:
            gameover= read_image("gameover3.pixel","gameover3.color");
            break;
        case 4:
            gameover= read_image("gameover4.pixel","gameover4.color");
            break;
        case 5:
            gameover= read_image("gameover5.pixel","gameover5.color");
            break;
        case 6:
            gameover= read_image("gameover6.pixel","gameover6.color");
            break;
        case 7:
            gameover= read_image("gameover7.pixel","gameover7.color");
            break;
        case 8:
            gameover= read_image("gameover8.pixel","gameover8.color");
            break;
        case 9:
            gameover= read_image("gameover9.pixel","gameover9.color");
            break;
        case 10:
            gameover= read_image("gameover10.pixel","gameover10.color");
            break;
        case 11:
            gameover= read_image("gameover11.pixel","gameover11.color");
            break;
        default:
            break;


        }
        count++;
        show_image(gameover,120,35);
        drawCmdWindow();


        if(count%4==0)
        {
            for(i=0; i<2; i++)
            {
                playAudio(&audioOver[ran]);
                //Sleep(300);
            }
        }
        Sleep(300);
    }
    destroy_image(gameover);

}

void Loser()
{
    loseTimes++;
    int count=1;
    Image *loser;
    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    while(count<=6)
    {

        clearScreen();
        switch(count)
        {

        case 1:
            loser= read_image("Loser1.pixel","Loser1.color");
            break;
        case 2:
            loser= read_image("Loser2.pixel","Loser2.color");
            break;
        case 3:
            loser= read_image("Loser3.pixel","Loser3.color");
            break;
        case 4:
            loser= read_image("Loser4.pixel","Loser4.color");
            break;
        case 5:
            loser= read_image("Loser5.pixel","Loser5.color");
            break;
        case 6:
            loser= read_image("Loser6.pixel","Loser6.color");
        default:
            break;


        }
        count++;
        show_image(loser,120,35);
        drawCmdWindow();  /* update window immediately */


        for(i=0; i<1; i++)
        {
            playAudio(&audioLose[ran]);
            //Sleep(100);
        }

        Sleep(300);
    }
    destroy_image(loser);
    showTable();
}

void Loser2(int x,int y)  //small lose send location
{
    int count=1;
    Image *loser;
    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    while(count<=6)
    {

        clearScreen();
        switch(count)
        {

        case 1:
            loser= read_image("Loser21.pixel","Loser21.color");
            break;
        case 2:
            loser= read_image("Loser22.pixel","Loser22.color");
            break;
        case 3:
            loser= read_image("Loser23.pixel","Loser23.color");
            break;
        case 4:
            loser= read_image("Loser24.pixel","Loser24.color");
            break;
        case 5:
            loser= read_image("Loser25.pixel","Loser25.color");
            break;
        case 6:
            loser= read_image("Loser26.pixel","Loser26.color");
        default:
            break;


        }
        count++;
        show_image(loser,x,y);
        drawCmdWindow();  /* update window immediately */


        for(i=0; i<1; i++)
        {
            playAudio(&audioLose[ran]);
            //Sleep(300);
        }

        Sleep(300);
    }
    destroy_image(loser);

}

void Winner()
{
    int count=1;
    Image *winner;
    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    int time=7;
    while(time--)
    {
        clearScreen();
        switch(count)
        {
        case 1:
            winner= read_image("Winner1.pixel","Winner1.color");
            break;
        case 2:
            winner= read_image("Winner2.pixel","Winner2.color");
            break;
        case 3:
            winner= read_image("Winner3.pixel","Winner3.color");
            break;
        default:
            break;
        }

        count=(count+1)%4;
        show_image(winner,120,35);
        drawCmdWindow();  /* update window immediately */

        for(i=0; i<1; i++)
        {
            playAudio(&audioWin[ran]);
            //Sleep(300);
        }
        Sleep(200);
    }
    destroy_image(winner);
}

void Winner2(int x,int y)
{
    int count=1;
    Image *winner;
    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    int time=7;
    while(time--)
    {
        clearScreen();
        switch(count)
        {
        case 1:
            winner= read_image("Winner21.pixel","Winner21.color");
            break;
        case 2:
            winner= read_image("Winner22.pixel","Winner22.color");
            break;
        case 3:
            winner= read_image("Winner23.pixel","Winner23.color");
            break;
        default:
            break;
        }

        count=(count+1)%4;
        show_image(winner,x,y);
        drawCmdWindow();  /* update window immediately */

        for(i=0; i<1; i++)
        {
            playAudio(&audioWin[ran]);
            //Sleep(300);
        }

        Sleep(200);
    }
    destroy_image(winner);
}

void initPlace()
{
    poker_place = (Place*)malloc(sizeof(Place)*4);
    (*(poker_place+0)).x=100;
    (*(poker_place+1)).x=120;
    (*(poker_place+2)).x=100;
    (*(poker_place+3)).x=120;
    (*(poker_place+0)).y=70;
    (*(poker_place+1)).y=70;
    (*(poker_place+2)).y=70;
    (*(poker_place+3)).y=70;

    counting_place = (Place*)malloc(sizeof(Place)*2);
    (*(counting_place+0)).x=0;
    (*(counting_place+1)).x=400;
    (*(poker_place+0)).y=0;
    (*(poker_place+1)).y=0;
}
