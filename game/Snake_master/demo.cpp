#include <iostream>
using namespace std;
#include <winbgim.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MINW 20
#define MINH 20
#define MAXW 420
#define MAXH 220
#define MINX 20
#define MINY 20
#define MAXX 420
#define MAXY 220
#define BACKGROUND 15

struct Point
{
    int x, y, x0, y0;
};
struct HighScore {
	int score;
	char name[30];
};

void initGame ();
bool checkPoint ();
void drawPoint (int x,int y,int r);
void moveSnake ();
void drawSnake ();
void drawFood ();
void drawGame ();
void classic();
void modern();
void mainLoop (void (*gloop)());
void run ();
void changeDirecton (int x);
void showHighScore();
void getHighScore();
void checkHighScore(int score);
void initScore();
bool isEmpty();
void showText(int x,int y,char *str);
void showTextBackground(int x,int y,char *str,int color);
void rand_diemTaiXiu();

int level=4;
bool endGame;
int snakeLength, length, score;
int diemCuoc, ketqua=1, chon=1, dem_moi=0;
Point snake[1000];
Point direction;
Point food;
HighScore  highscore[5];
const int DIRECTION = 10;
char *score_str = new char[20], *diemCuoc_str=new char[3], *hscore= new char[20]; 
void initScore()
{
	if (isEmpty())
	{
		for (int i = 0;i < 5;i++)
		{
			strcpy(highscore[i].name,"PLAYER");
			highscore[i].score = 0;
		}
		getHighScore();
	}else
	{
		char arr[20];
		int count = 0;
		FILE *f;
		f = fopen("highscore.txt", "r");
		for (int i = 0;i < 5;)
		{
			while (!feof(f))
			{
				count++;
				fscanf(f, "%s", arr);
				if (count%2 == 1){
				   	strcpy(highscore[i].name,arr);
					//printf ("%s\t",ch);
				}
				else{
					highscore[i].score = atoi(arr);
					i++;
				}
			}
		}
	}
}
bool isEmpty()
{
	FILE *fp;
	long size;
	fp = fopen("highscore.txt","r");
	if(fp)
	{
		fseek (fp, 0, SEEK_END);
        size = ftell(fp);
		fclose(fp);
	}
	return(size == 0);
}

void rand_diemTaiXiu(int x, int y, int *sum) 
{
	srand(time(NULL));
    int r, i=0;
    char *s = new char[5];
    while (i <= 100)
    {
        r = 1 + rand() % 6;
        sprintf(s, "%d", r);
        
        setcolor(13);
 		setlinestyle(0, 0, 3);
    	setfillstyle(SOLID_FILL, 13);
    	circle(x+11, y+12, 30);
		floodfill(x+11, y+12, 13); 
    	setcolor(2);
    	circle(x+11, y+12, 30);
        setbkcolor(13);
        setcolor(4);	
		settextstyle(0, 0, 3);
        outtextxy(x, y, s);
        delay(30);
        i++;
    }
    *sum += r;
    if(*sum>3&&*sum<11) ketqua=-1;
    if(*sum>10&&*sum<18) ketqua=1;
    setlinestyle(0, 0, 1);
	setbkcolor(15);
}

void rand_diemCuoc() 
{
	srand(time(NULL));
    int r, i=0;
    char *s = new char[5];
    while (i <= 50)
    {
        r = 1 + rand() % snakeLength;
        sprintf(s, "%d", r);
        setbkcolor(14);
        setcolor(4);	
		settextstyle(0, 0, 4);
		outtextxy(635, 146, "  ");
		if (r<10)
        	outtextxy(646, 146, s);
        else outtextxy(635, 146, s);
        setbkcolor(15);
        delay(40);
        i++;
    }
    diemCuoc = r;
    sprintf(diemCuoc_str, "%d", diemCuoc);
}

void showTextBackground(int x, int y, char *str, int color)
{
    int bk = getbkcolor();
    setbkcolor(color);
    outtextxy(x, y, str);
    delay(200);
    setbkcolor(bk);
}

void showText(int x, int y, char *str)
{
    int c = getcolor();
    int color = rand() % 16 + 1;
    setcolor(color);
    outtextxy(x + 3, y, str);
    setcolor(c);
    delay(50);
}

void showBackground(int x1, int y1, int x2, int y2, int xchu, int ychu, char *str)
{
    int color = rand() % 15 + 1;
    setfillstyle(1, color); 
    bar(x1, y1, x2, y2);
    setbkcolor(color);
    settextstyle(4, 0, 5);
	setcolor(4);
	outtextxy(xchu, ychu, str);
   	setfillstyle(1, 15); 
   	setlinestyle(0, 0, 1);
	setbkcolor(15);
    delay(100);
}

bool checkPoint()
{
    for (int i = 0; i < snakeLength; i++)
    {
        if (food.x == snake[i].x && food.y == snake[i].y)
            return false;
    }
    return true;
}

void initGame()
{
    setbkcolor(15);
    cleardevice();
    setwindowtitle("SNAKE-Playing....");
    endGame = false;
    setfillstyle(1, 9);
    bar(MINX, MINY, MAXX, MINY + 5);
    bar(MAXX, MINY, MAXX - 5, MAXY);
    bar(MAXX, MAXY, MINX, MAXY - 5);
    bar(MINX, MINY, MINX + 5, MAXY);
    
    // ve ô phím
	setfillstyle(SOLID_FILL, 0);
	setcolor(0);
    bar(80, 380, 150, 420);
    bar(170, 380, 240, 420);
    bar(260, 380, 330, 420);
    bar(170, 320, 240, 360);
    
    // ve huong dan snake
    int bk = getbkcolor();
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    int a[] = {280, 395, 295, 395, 295, 390, 315, 400, 295, 410, 295, 405, 280, 405, 280, 395};
    fillpoly(8, a);
    settextstyle(4, 0, 3);
    int b[] = {100, 400, 115, 390, 115, 395, 130, 395, 130, 405, 115, 405, 115, 410, 100, 400};
    fillpoly(8, b);
    int c[] = {200, 355, 200, 340, 195, 340, 205, 325, 215, 340, 210, 340, 210, 355, 200, 355};
    fillpoly(8, c);
    int d[] = {200, 385, 200, 400, 195, 400, 205, 415, 215, 400, 210, 400, 210, 385, 200, 385};
    fillpoly(8, d);
 
    setfillstyle(SOLID_FILL, 0);
	setcolor(0);
    bar(45, 445, 175, 485);
    setcolor(15);
    settextstyle(1, 0, 1);
    setbkcolor(0);
    outtextxy(60, 455, "SPACE");
    setbkcolor(bk);
    setcolor(0);
    settextstyle(3, 0, 4);
    outtextxy(200, 450, "Pause/Resume");
    
    bar(50, 500, 170, 530);
    setcolor(15);
    settextstyle(1, 0, 1);
    setbkcolor(0);
    outtextxy(80, 505, "ESC");
    setbkcolor(bk);
    setcolor(0);
    settextstyle(3, 0, 4);
    outtextxy(200, 500, "End Game");
    snake[0].x = 70;
    snake[0].y = 50;
    snake[1].x = 60;
    snake[1].y = 50;
    snake[2].x = 50;
    snake[2].y = 50;
    snakeLength = 3;
    setfillstyle(1, BACKGROUND);
    bar(25, 25, 415, 215);
    direction.x = 10;
    direction.y = 0; // Khoi tao di theo huong trai qua phai
    setcolor(2);
    srand(time(NULL));
    // Init food
    do
    {
        food.x = (rand() % (39) + 3) * 10;
        food.y = (rand() % (19) + 3) * 10;
    } while (checkPoint() == false);
}

void initTaiXiu()
{
	int bk=getcolor();
	setfillstyle(1, 0); 
//	bar(440, 240, 880, 240 + 5);
//    bar(880, 240, 880 - 5, 540);
//    bar(880, 540, 440, 540 - 5);
//    bar(440, 240, 440 + 5, 540);
   
    bar(620, 240, 620+5, 540);
    bar(700, 240, 700-5, 540);
	setlinestyle(3, 0, 15);
	rectangle(440, 240, 880, 540);
    
    //ve ô tong diem
    settextstyle(3, 0, 2);
    setcolor(0);
    outtextxy(638, 475, "SUM");
    setlinestyle(0, 0, 3);
    setcolor(1);
    bar(625, 500, 695, 502);
    //ve 3 ô random
    setcolor(2);   //   xam:8
    circle(660, 285, 30);
    circle(660, 360, 30); 
    circle(660, 435, 30);
    // ve tai xiu
    settextstyle(4, 0, 5);
    setcolor(4);
    outtextxy(475, 365, "TAI");
    outtextxy(730, 365, "XIU");
    // ve ô random to
 	setcolor(14);
 	setlinestyle(0, 0, 3);
    setfillstyle(SOLID_FILL, 14);
    circle(660, 160, 60);
	floodfill(660, 160, 14);
    setcolor(1);
    circle(660,160,60);
    
    setlinestyle(0, 0, 1);
	setcolor(bk);	
}
void clearTaiXiu()
{
	outtextxy(445, 50, "                                              ");
	//  ô random to
	setbkcolor(14);	
	settextstyle(0, 0, 4);
 	outtextxy(635, 146, "  ");
    // o TAI XIU
    setfillstyle(1, 15);
	settextstyle(4, 0, 5);
	setcolor(4);
	setbkcolor(15);
	bar(445, 245, 620, 535);
	outtextxy(475, 365, "TAI");
	bar(700, 245, 875, 535);
	outtextxy(730, 365, "XIU");
    //3 o random
	setbkcolor(13);
	settextstyle(0, 0, 3);
    outtextxy(649, 273, " ");
    outtextxy(649, 348, " ");
    outtextxy(649, 423, " ");
    // o SUM
    bar(625, 502, 695, 535);
    // tra lai mau
    setlinestyle(0, 0, 1);
	setbkcolor(15);
}

void drawPoint(int x, int y, int r)
{
    setlinestyle(0, 0, 2);
	circle(x, y, r);
    floodfill(x, y, getcolor());
}
// Snake is moving
void modern()
{
    for (int i = 0; i < snakeLength; i++)
    {
        if (i == 0)
        {
            snake[0].x0 = snake[0].x;
            snake[0].y0 = snake[0].y;
            snake[0].x += direction.x;
            snake[0].y += direction.y;
        }
        else
        {
            snake[i].x0 = snake[i].x;
            snake[i].y0 = snake[i].y;
            snake[i].x = snake[i - 1].x0;
            snake[i].y = snake[i - 1].y0;
        }
        if (snake[0].x < MINX + 5 || snake[0].y < MINY + 5 || snake[0].x > MAXX - 5 || snake[0].y > MAXY - 5)
            endGame = true;
        if (i != 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            endGame = true;
    }
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
    	PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
    	dem_moi++;
    	if (dem_moi % 5==0)
    	{
    		PlaySound(TEXT("MelodiaDlaZuzi.wav"), NULL, SND_ASYNC);
	    	int sum = 0;
	    	int choose=0; //choose = 1 : TAI  ; =2 : XIU
	    	char *scoreTX = new char[3];
	    	clearmouseclick(WM_LBUTTONDOWN);
	        while (!ismouseclick(WM_LBUTTONDOWN))
	        {
	        	settextstyle(4, 0, 3);
	    		setcolor(0);
	        	outtextxy(520, 50, "Click de dat cuoc");
	        	rand_diemCuoc();
	        }
	    	settextstyle(4, 0, 3);
		    setcolor(0);
		    if (diemCuoc < 10) 
				outtextxy(440, 50, "So diem cuoc cua ban la: ");
			else outtextxy(440, 50, "So diem cuoc cua ban la: ");
		    outtextxy(850, 50, diemCuoc_str);
		    delay(1750);
	    	clearmouseclick(WM_LBUTTONDOWN);
			while (!ismouseclick(WM_LBUTTONDOWN) || mousex()<=440 || mousex()>=880 || mousey()<=240 || mousey()>=540 || (mousex()>=620 && mousex()<=700))
	        {
		    	outtextxy(440, 50, " Hay chon so phan cua ban!    ");
		    	delay(100);
		    }
		    if (ismouseclick(WM_LBUTTONDOWN))
		    {
		    	int bk = getbkcolor();
		    	if (440<mousex() && mousex()<620 && 240<mousey() && mousey()<540)   
				{
					setfillstyle(1, 11);
					bar(445, 245, 620, 535);
					settextstyle(4, 0, 5);
				    setcolor(4);
				    setbkcolor(11);
				    outtextxy(475, 365, "TAI");
				    choose = 1;
				    chon=1;
				}
		        if (700<mousex() && mousex()<880 && 240<mousey() && mousey()<540)
		        {
		        	setfillstyle(1, 11);
					bar(700, 245, 875, 535);
					settextstyle(4, 0, 5);
				    setcolor(4);
				    setbkcolor(11);
				    outtextxy(730, 365, "XIU");
				    choose = 2;
				    chon=-1; 
				}
				setbkcolor(bk);
			}
	    	rand_diemTaiXiu(649, 273, &sum);
	    	rand_diemTaiXiu(649, 348, &sum);
	    	rand_diemTaiXiu(649, 423, &sum);
	    	
	    	sprintf(scoreTX, "%d", sum);
	    	settextstyle(0, 0, 3);
	    	if (sum>=10)
	    		outtextxy(638, 506, scoreTX);
	    	else outtextxy(647, 506, scoreTX);
	    	delay(200);
	    	// ktra thang thua
	    	settextstyle(4, 0, 3);
		    setcolor(0);
	    	if (3<=sum && sum<=10) // XIU
	    	{
	    		if (choose == 2) 
	    		{	
					outtextxy(440, 50, "     Thang roi nhe cung!        ");
				}
				else 
				{ 	
					PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);
					outtextxy(440, 50, "  Ban oi dung nghien nua...      "); 
					if (diemCuoc ==  snakeLength) goto x4;	
				}
			} 
			else  // TAI
			{
				if (choose == 1)
	    		{ 	
					outtextxy(440, 50, "     Thang roi nhe cung!        ");
				}
				else 
				{ 		
					PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);
					outtextxy(440, 50, "  Ban oi dung nghien nua...      "); 
					if (diemCuoc ==  snakeLength) goto x4;
				}
			}
			delay(2000);
			while (!kbhit() && snakeLength > 1)
			{
				settextstyle(4, 0, 3);
		    	setcolor(0);
				outtextxy(440, 50, "    An nut bat ki de tiep tuc         ");
				if (3<=sum && sum<=10)
				{
					showBackground(700, 245, 875, 535, 730, 365, "XIU");
				}
				if (11<=sum && sum<=18 && choose == 1)
				{
					showBackground(445, 245, 620, 535, 475, 365, "TAI");
				}
			}
	    	x4: clearTaiXiu();
	    	if (snakeLength==1) diemCuoc = 1;
    	} 
    	
    		snake[snakeLength].x = snake[snakeLength - 1].x0;
	        snake[snakeLength].y = snake[snakeLength - 1].y0;
	        // khoi tao luu diem cu
	        score=snakeLength;
	        sprintf(hscore,"%d",snakeLength);
	        if(dem_moi%5==0) snakeLength += (diemCuoc*chon*ketqua);
	        if(snakeLength==0) endGame = true;
	        PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
	        // Random again food if sanke ate food
	        srand(time(NULL));
	        do
	        {
	            food.x = (rand() % (39) + 3) * 10;
	            food.y = (rand() % (19) + 3) * 10;
	        } while (checkPoint() == false);
    	if(dem_moi%5!=0) snakeLength+=1;
    }
}

void drawSnake()
{
    // ve ran
	setfillstyle(1, 15);
    for (int i = 0; i < snakeLength; i++)
	{ 
		drawPoint(snake[i].x, snake[i].y, 5); 
		setcolor(5);
	}
    // xoa duoi
	for(int i=length; i>=snakeLength-1; i--)
	{
		snake[i+1].x=0;
		snake[i+1].y=0;
		snake[i+1].x0=0;
		snake[i+1].y0=0;
		int x = getcolor();
		setfillstyle(1, BACKGROUND);
		drawPoint(snake[i].x0, snake[i].y0, 5);				
		setcolor(BACKGROUND);
		circle(snake[i].x0, snake[i].y0, 5);
		setcolor(x);
	}
	setfillstyle(1,5);
}

void drawFood()
{
    int x = getcolor();
    int c = rand() % 5 + 10;
    setcolor(c);
    setfillstyle(SOLID_FILL, c);
    drawPoint(food.x, food.y, 5);
    setcolor(x);
    setfillstyle(1, BACKGROUND);
}

// Ve toan bo giao dien game
void drawGame()
{
    drawSnake();
    drawFood();
    int x = getcolor();
    setcolor(2);
    sprintf(score_str, "%d", snakeLength); // show score
    settextstyle(4, 0, 3);
    outtextxy(20, 250, "SnakeLength: ");
    setcolor(12);
    outtextxy(250, 250, strcat(score_str, "  "));
    setcolor(x);
}

void changeDirecton(int x)
{
    switch (x)
    {
    case 72:
        if (direction.y != DIRECTION)
        {
            PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            direction.y = -DIRECTION;
            direction.x = 0;
        }
        break;
    case 80:
        if (direction.y != -DIRECTION)
        {
            PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            direction.y = DIRECTION;
            direction.x = 0;
        }
        break;
    case 77:
        if (direction.x != -DIRECTION)
        {
            PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            direction.x = DIRECTION;
            direction.y = 0;
        }
        break;
    case 75:
        if (direction.x != DIRECTION)
        {
            PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
            direction.x = -DIRECTION;
            direction.y = 0;
        }
        break;
    case 27:
        endGame = true;
        break;
    }
}

void mainLoop(void (*xxx)())
{
    int x = getcolor();
    if (!kbhit())
    {
        xxx();
    }
    else
    {
        char ch = getch();
        if (ch == -32)
            ch = getch();
        if (ch == 32)
        {
            setcolor(0);
            outtextxy(100, 100, "Game Pause");
            setcolor(x);
            ch = getch();
            while (ch != 32)
            {
                ch = getch();
                delay(0);
            }
            setcolor(BACKGROUND);
            outtextxy(100, 100, "Game Pause");
            setcolor(x);
            delay(200);
        }
        changeDirecton(ch);
        mainLoop(xxx);
    }
}

void showHighScore(){
	FILE *f;
	f = fopen("highscore.txt", "r");
	char ch[20];
	settextstyle (1,0,5);
	setcolor (15);
	outtextxy (150,50,"HIGH SCORE");
	settextstyle (1,0,4);
	int y = 150,count = 0;
	while (!feof(f)){
		if (count == 10) break;
		count++;
		fscanf(f, "%s", ch);
   		if (count%2 == 1){
   			setcolor (10);
   			outtextxy (180,y,ch);
   			y+=50;
		}else{
			setcolor (12);
			outtextxy (500,y-50,ch);	   	
		}
	}
	fclose(f);
}
void getHighScore (){
	FILE *f;
	f = fopen("highscore.txt", "w");
	for (int i = 0;i < 5;i++){
		fputs(highscore[i].name,f);
		fputs(" ",f);
		fprintf(f,"%d",highscore[i].score);
		fputs("\n",f);
	}
	fclose(f);
}
void checkHighScore (int _score)
{
	char _name[20]={""};
	for (int i = 0; i < 5; i++)
	{
		if (_score > highscore[i].score)
		{
			//to do sth
			settextstyle(1,0,3);
				for (int j = 0; j < 30;j++)
				{
					if (j%2 == 0)
					{
						setcolor (14);
						if (i == 0)
						outtextxy(460,100,"BEST SCORE");
						else
						outtextxy(460,100,"HIGH SCORE");
						delay(100);
					}else{
						setcolor (9);
						if (i == 0)
						outtextxy(460,100,"BEST SCORE");
						else
						outtextxy(460,100,"HIGH SCORE");
						delay(100);
					}
				}
				settextstyle(1,0,2);
				setcolor (4);outtextxy(430,150,"Player:");
				delay(100);
				char ch1;
				int x = 0;
				char str[2];
				str[1] = 0;
				while (ch1 != 13 && x < 10){
					do{
						ch1 = getch();
					}while (ch1 < 65 && ch1 >90 || ch1 < 97 && ch1 > 132);
					x++;
					str[0] = ch1;
					strcat(_name,str);
					outtextxy(540,150,_name);
				}
			for (int j = 4;j > i;j--){
				strcpy(highscore[j].name,highscore[j-1].name);
				highscore[j].score = highscore[j-1].score;
			}
			strcpy(highscore[i].name,_name);
			highscore[i].score = _score;
			break;
		}
	}
	getHighScore();
}

void run()
{
    initwindow(915, 600);
    initScore();
    PlaySound(TEXT("avenger.wav"), NULL, SND_ASYNC);
    int x = 0;
    char *s = new char[5];
    while (x <= 100)
    {
        cleardevice();
        setcolor(10);
        settextstyle(4, 0, 5);
        outtextxy(110, 240, "Game Loading...");
        sprintf(s, "%d", x);
        setcolor(4);
        outtextxy(600, 240, strcat(s, "%"));
        if (x == 100)
            delay(500);
        delay(20);
        x++;
    }
    while (true)
    {
    x1:
        int bk = getbkcolor();
        cleardevice();
        setbkcolor(0);
        cleardevice();
        clearmouseclick(WM_LBUTTONDOWN);
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            settextstyle(1, 0, 6);
            setcolor(10);
            outtextxy(170, 70, "GAME MENU");
            settextstyle(10, 0, 5);
            showText(270, 200, "NEW GAME");
            showText(270, 270, "HIGH SCORE");
            showText(270, 340,"QUIT GAME");
        }
        clearmouseclick(WM_LBUTTONDOWN);
        if (mousey() <= 255)
        {
            showTextBackground(270, 200, "NEW GAME", 15);
            
        	x2:
            setbkcolor(0);
            cleardevice();
            int nameFunction;
            clearmouseclick(WM_LBUTTONDOWN);
            PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
            initGame();
            initTaiXiu();
            
            while (!endGame)
	        {
	            // Change delay folow level
	            delay(250 - (level - 1) * 40);
	            if(length<snakeLength) length=snakeLength;
				mainLoop(modern);
	            drawGame();
	            if(snakeLength==0) break;
	        }
            
            PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);
            settextstyle(1, 0, 4);
            setcolor(0);
            outtextxy(100, 110, "GAME OVER!");
            setcolor(8);
            settextstyle(1, 0, 2);
            outtextxy(100, 160, "Your Score : ");
            setcolor(10);
            //check score
            if(dem_moi%5==0 && snakeLength==0)
			{
				outtextxy(300, 160, hscore);
				checkHighScore(score);
			} 										// show diem cu neu cuoc thua
            else{
				outtextxy(300, 160, score_str);
				checkHighScore(snakeLength);
            }
            
            setcolor(10);
            settextstyle(4, 0, 5);
            outtextxy(100, 200, "Play Again ?");
            settextstyle(4, 0, 3);
            setcolor(1);
            clearmouseclick(WM_LBUTTONDOWN);
            while (!ismouseclick(WM_LBUTTONDOWN))
	            {
	                showTextBackground(150, 270, "YES", 12);
	                showTextBackground(300, 270, "NO", 7);
	            }
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                if (mousex() >= 140 && mousex() <= 230 && mousey() >= 260 && mousey() <= 310)
                {
                    showTextBackground(150, 270, "YES", 7);
                    delay(100);
                    // xoa duoi sau khi choi lai
                    for(int i=length;i>=3;i--)
						{
							snake[i+1].x=0;
						    snake[i+1].y=0;
						    snake[i+1].x0=0;
						    snake[i+1].y0=0;
							int x = getcolor();
						    setfillstyle(1, BACKGROUND);
						    drawPoint(snake[i].x0, snake[i].y0, 5);				
						    setcolor(BACKGROUND);
						    circle(snake[i].x0, snake[i].y0, 5);
						    setcolor(x);
						}
					dem_moi=1;
                    goto x2;
                }
                else if (mousex() >= 290 && mousex() <= 360 && mousey() >= 260 && mousey() <= 310)
                {
                    showTextBackground(300, 270, "NO", 12);
                    delay(100);
                    goto x1;
                }   
            }
        }
        else if (mousey() <= 320)
	        { 
	        	showTextBackground(270, 270,"HIGH SCORE", 15);
				cleardevice();
				showHighScore();
				while (!ismouseclick(WM_LBUTTONDOWN)){
					delay(0);
				}
				goto x1;
	        }
	    else if (mousey() <= 370)
			{
	            showTextBackground(270, 340, "QUIT GAME", 15);	
	            exit(0);
			}
        else
			{
	            cleardevice();
	            settextstyle(1, 0, 4);
	            setcolor(15);
	            int x = getcolor();
	            setcolor(x);
	            settextstyle(1, 0, 2);
	            setcolor(4);
	            goto x1;
	    	}
    }
}
int main()
{
    run();
    // Giai phong bo nho con tro;
    delete score_str;
    delete diemCuoc_str;
    getch();
    closegraph();
    return 0;
}
