#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw2.h"
#include "kb_input2.h"

#include "audio.h"
#include <time.h>

typedef struct _image {
    int row;
    int col;
    char *pixel;
    int *color;
} Image;

void destroy_image(Image *ip);
Image * read_image(char *pixel_file, char *color_file);
void show_image(Image *ip, int offx, int offy);
void destroy_image(Image *ip);
char getpixel(Image *ip, int x, int y);
int getcolor(Image *ip, int x, int y);

void initAudio();
void initAudioNUM();
void start();
void gameover();
void Loser();
void Winner();
void Winner2(int x,int y);
void Loser2(int x,int y);
void playAudioNUM(int index);
//audio
Audio audioWin[2];
Audio audioLose[2];
Audio audioOver[6];
Audio audio[1];


Audio audioNUM[13][2];

int main(void){
    initAudio();
    initAudioNUM();

    playAudioNUM(11);
    //start();
    //gameover();
    //Loser();
    //Winner();

    //Loser2(50,35);//send location
    //Winner2(300,35);//send location


    //ran=(rand()%2);//win
   // int  ran,i ;
   // for( i = 0 ; i < 5 ; i++ ) {

  // }
  /*
srand( time(NULL) );
 ran=rand()%8;
 */
/*
int i=0;

        for(i=0;i<1;i++){
                playAudio(&audioNUM[11][1]);
                  Sleep(7000);
        }


*/




    //playAudio(&audio[0]);

    return 0;
}
void initAudio(){
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

void initAudioNUM(){

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

void playAudioNUM(int index){

    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
    for(i=0;i<1;i++){
        playAudio(&audioNUM[index][ran]);
        Sleep(7000);
    }


}

void start(){
     int count=1;
     int ok=0;
     Image *start;
     int time=20;//29
     while(time--){

        clearScreen();
        switch(count){
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

        if(count==16){
            ok=1;
        }
        if(ok){
           // count=(count+1)%16+10;
           if(count==15){
            count=16;
           }else{
            count=15;
           }

        }else{
         count++;
        }
        show_image(start,125,35);
        drawCmdWindow();
        int i=0;
        for(i=0;i<1;i++){
            playAudio(&audio[0]);
           //Sleep(500);
        }

        Sleep(500);
    }
    destroy_image(start);

}

void gameover(){
     int count=2;
     Image *gameover;

      int ran,i;
        srand( time(NULL) );
        ran=rand()%6;

     while(count<=11){

        clearScreen();
        switch(count){

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


        if(count%4==0){
            for(i=0;i<2;i++){
                playAudio(&audioOver[ran]);
                Sleep(300);
            }
        }
        Sleep(300);
    }
    destroy_image(gameover);

}

void Loser(){
     int count=1;
     Image *loser;
    int ran,i;
    srand( time(NULL) );
    ran=rand()%2;
     while(count<=6){

        clearScreen();
        switch(count){

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


        for(i=0;i<1;i++){
            playAudio(&audioLose[ran]);
            Sleep(100);
        }


        Sleep(300);
    }
    destroy_image(loser);
}

void Loser2(int x,int y){ //small lose send location
     int count=1;
     Image *loser;
     int ran,i;
        srand( time(NULL) );
        ran=rand()%2;
     while(count<=6){

        clearScreen();
        switch(count){

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


        for(i=0;i<1;i++){
            playAudio(&audioLose[ran]);
            Sleep(300);
        }

        Sleep(300);
    }
    destroy_image(loser);

}

void Winner(){
     int count=1;
     Image *winner;
      int ran,i;
        srand( time(NULL) );
        ran=rand()%2;
    int time=7;
     while(time--){
        clearScreen();
        switch(count){
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

        for(i=0;i<1;i++){
            playAudio(&audioWin[ran]);
            Sleep(300);
        }
        Sleep(200);
    }
    destroy_image(winner);
}

void Winner2(int x,int y){
     int count=1;
     Image *winner;
      int ran,i;
        srand( time(NULL) );
        ran=rand()%2;
        int time=7;
     while(time--){
        clearScreen();
        switch(count){
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

        for(i=0;i<1;i++){
            playAudio(&audioWin[ran]);
            Sleep(300);
        }

        Sleep(200);
    }
    destroy_image(winner);
}

void putString(int x, int y, char *p, int fg_color, int bg_color)
{
    int i;
    for(i=0; i<strlen(p); i++) {
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
    if (fid1==NULL || fid2==NULL) {
        return NULL;
    } else {
        fscanf(fid1, "%d%d", &row, &col);
        fscanf(fid2, "%d%d", &row, &col); // supposedly, size should be the same
        p = (Image*) malloc(sizeof(Image));
        p->row = row;
        p->col = col;
        p->pixel = (char*) malloc(sizeof(char)*row*col);
        p->color = (int*) malloc(sizeof(int)*row*col);
        fscanf(fid1, "%*c");
        for (i=0; i<row; i++) {
            for (j=0; j<col; j++) {
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

char getpixel(Image *ip, int x, int y)
{
    return ip->pixel[y*ip->col + x];
}

int getcolor(Image *ip, int x, int y)
{
    return ip->color[y*ip->col + x];
}

void show_image(Image *ip, int offx, int offy)
{
    int x, y;
    char c;
    for (y=0; y<ip->row; y++) {
            for (x=0; x<ip->col; x++) {
            c = getpixel(ip, x, y);
            if (c!=' ')
            putASCII2( x + offx,
                y + offy, c, getcolor(ip, x, y), 0);
            }
    }
}
void destroy_image(Image *ip)
{
    free(ip->pixel);
    free(ip->color);
    free(ip);
}
