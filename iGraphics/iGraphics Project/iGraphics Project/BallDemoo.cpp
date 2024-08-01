# include "iGraphics.h"
#include<math.h>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<cstdlib>

#define totalBricks 8 * 11

struct brickStructure
{
    int brick_x;
    int brick_y;
    int brick_dx;
    int brick_dy;
    bool show;
    int red;
    int blue;
    int green;

    // Constructor to initialize the members
    brickStructure()
        : brick_dx(100), brick_dy(30), show(true), red(0), blue(0), green(0)
    {
    }
};

brickStructure bricks[totalBricks];//bricks is a variable of structure.jar totalbrick sonkhok array ase 

int screen_width = 1280;
int screen_height = 720;

int ball_x = 480;//initially ball er stage
int y_axis_margin = 90;//margin ,jar niche gele game over 
int ball_y = y_axis_margin;
int ball_radius = 10;
int ball_speed = 20;
int ball_dx = 9; //ball er cholar way
int ball_dy = 6;

int paddle_x = ball_x - 70;
int paddle_y = ball_y - 30;
int paddle_width = 150;
int paddle_height = 20;
bool game_started = false;

int a; //for color -black code is setted 
int b;
int c;

bool musicOn = 0;

int power_speed = 5;//powerups
int powerups_exist = 0;
int powerups_x = 0;
int powerups_y = 0;
int powerup_active = 0;
int powerup_width = 75;
int random_number;

int lives = 3;
int score = 0;
char score_string[100];

char str[100], str2[100];//FOR NAME INPUT 
int len;
int mode;

struct player
{
	char name[15];
	int pscore;
}player[10];
int n = 0;

char background[4][20] = { "images\\finalbg.bmp" };
int backgroundIndex = 0;

int screen = 0;
int line_dist = 0;

void getHighScore();
void saveHighScore();

void ballMovement();
void reSetBall();
void brickFoundation();
void lifePlus();
void paddlePlus();
void ballSlow();
void lifeMinus();
void paddleMinus();
void ballSpeed();
void ballBig();
void ballSmall();


void iDraw()
{
	//place your drawing codes here	
	iClear();


	//menu
	if (screen == 0)/////////////////////////
	{

		iShowBMP(0, 0, "images\\menu1.bmp");
		iShowBMP(100, 120, "images\\exit.bmp");
		iShowBMP(100, 235, "images\\highscore.bmp");
		iShowBMP(100, 350, "images\\instruction.bmp");
		iShowBMP(100, 465, "images\\newgame.bmp");

		iShowBMP(900, 235, "images\\credit.bmp");
		iShowBMP(900, 350, "images\\extrememode.bmp");

		iShowBMP(905, 60, "images\\micon.bmp");
		iShowBMP(980, 60, "images\\micoff.bmp");
	}

	//new game
	if (screen == 1)////////////////////////
	{

		{
			//background
			iShowBMP(0, 0, background[backgroundIndex]);
			//ball
			iSetColor(204, 255, 0);//84,22,180-for violet 
			iFilledCircle(ball_x, ball_y, ball_radius, 100);
			//paddle
			iSetColor(a, b, c);
			iFilledRectangle(paddle_x, paddle_y, paddle_width, paddle_height);
			//bricks
			for (int i = 0; i < totalBricks; i++)
			{
				if (bricks[i].show)
				{
					iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
					iFilledRectangle(bricks[i].brick_x, bricks[i].brick_y, bricks[i].brick_dx, bricks[i].brick_dy);
				}

			}

			//life
			if (lives == 3) {
				iShowBMP(1200, 15, "images\\life3.bmp");
				iShowBMP(1145, 14, "images\\life2.bmp");
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			if (lives == 2) {
				iShowBMP(1145, 14, "images\\life2.bmp");
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			if (lives == 1) {
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			//score
			iSetColor(75, 0, 130);
			iText(245, 22, score_string, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}


	//extreme mode
	if (screen == 2)////////////////////////
	{

		{
			//background
			iShowBMP(0, 0, background[backgroundIndex]);
			//ball
			iSetColor(255, 215, 0);//84,22,180-for violet 
			iFilledCircle(ball_x, ball_y, ball_radius, 100);
			//paddle
			iSetColor(a, b, c);
			iFilledRectangle(paddle_x, paddle_y, paddle_width, paddle_height);
			//bricks
			for (int i = 0; i < totalBricks; i++)
			{
				if (bricks[i].show)
				{
					iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
					iFilledRectangle(bricks[i].brick_x, bricks[i].brick_y, bricks[i].brick_dx, bricks[i].brick_dy);
				}
			}
			//powerups
			if (powerup_active == 1)
			{
				if (random_number == 0) iShowBMP(powerups_x, powerups_y, "images\\life+.bmp");
				if (random_number == 1) iShowBMP(powerups_x, powerups_y, "images\\pddl+.bmp");
				if (random_number == 2) iShowBMP(powerups_x, powerups_y, "images\\smallbl.bmp");
				if (random_number == 3) iShowBMP(powerups_x, powerups_y, "images\\lf-.bmp");
				if (random_number == 4) iShowBMP(powerups_x, powerups_y, "images\\pddl-.bmp");
				if (random_number == 5) iShowBMP(powerups_x, powerups_y, "images\\speedbl.bmp");
				if (random_number == 6) iShowBMP(powerups_x, powerups_y, "images\\megab.bmp");
				if (random_number == 7) iShowBMP(powerups_x, powerups_y, "images\\slowbl.bmp");
			}
			//life
			if (lives == 3) {
				iShowBMP(1200, 15, "images\\life3.bmp");
				iShowBMP(1145, 14, "images\\life2.bmp");
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			if (lives == 2) {
				iShowBMP(1145, 14, "images\\life2.bmp");
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			if (lives == 1) {
				iShowBMP(1095, 15, "images\\life.bmp");
			}
			//score
			iSetColor(75, 0, 130);
			iText(245, 22, score_string, GLUT_BITMAP_TIMES_ROMAN_24);

		}
	}

	//instruction
	if (screen == 3)////////////////////
	{
		iShowBMP(0, 0, "images\\instructions.bmp");
	}

	//scoreboard
	if (screen == 4)//////////////////
	{

		iShowBMP(0, 0, "images\\scoreboard.bmp");
		//	iSetColor(255, 0, 0);
		for (int i = 0; i<10; i++){
			iText(300, 460 - line_dist, player[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
			//Score
				//sprintf(str2, "%d", player[i].pscore);
			itoa(player[i].pscore, str2, 10);
			iText(1040, 460 - line_dist, str2, GLUT_BITMAP_TIMES_ROMAN_24);


			line_dist += 40;
		}

		line_dist = 1;
		iSetColor(255, 255, 255);
	}



	//credits
	if (screen == 5)/////////////////
	{
		iShowBMP(0, 0, "images\\cre.bmp");
	}

	//gameover
	if (screen == 7)/////////////////////
	{
		iShowBMP(0, 0, "images\\gameover.bmp");
		iSetColor(255, 255, 255);
		iText(520, 480, score_string, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(520, 380, str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void iMouseMove(int mx, int my)
{
	//ball_x = ball_x - dx;
}


void iPassiveMouse(int mx, int my)
{
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	//axis dimension
	printf("%d %d\n", mx, my);

	if (screen == 0)//menu//////////////////
	{
		if (mx >= 100 && mx <= 325 && my >= 465 && my <= 515)
		{
			screen = 1;//new game//////////////
			score = 0;
			itoa(0, score_string, 10);

			ball_x = 480;
			y_axis_margin = 90;
			ball_y = y_axis_margin;
			ball_radius = 10;
			
			paddle_x = ball_x - 70;
			paddle_y = ball_y - 30;
			paddle_height = 20;
			paddle_width = 150;
			game_started = false;

			lives = 3;

			for (int i = 0; i < totalBricks; i++)
			{
				bricks[i].show = 1;
			}

		}
		if (mx >= 900 && mx <= 1125 && my >= 350 && my <= 400)
		{
			screen = 2;//extreme mode ///////////////////
			score = 0;
			itoa(0, score_string, 10);

			powerup_active = 0;

			ball_x = 480;
			y_axis_margin = 90;
			ball_y = y_axis_margin;
			ball_radius = 10;

			paddle_x = ball_x - 70;
			paddle_y = ball_y - 30;
			paddle_height = 20;
			paddle_width = 150;

			 powerup_active = 0;
			 musicOn = 0;

			game_started = false;

			lives = 3;

			for (int i = 0; i < totalBricks; i++)
			{
				bricks[i].show = 1;
			}
		}
		if (mx >= 100 && mx <= 325 && my >= 350 && my <= 400)
		{
			screen = 3;//instructions///////////////
		}
		if (mx >= 100 && mx <= 325 && my >= 235 && my <= 285)
		{
			//saveHighScore();
			getHighScore();
			screen = 4;//high scores////////////////////

		}
		if (mx >= 900 && mx <= 1125 && my >= 235 && my <= 285)
		{
			screen = 5;//credits///////////////////
		}

		if (mx >= 100 && mx <= 325 && my >= 120 && my <= 170)
		{
			exit(0);///////
		}
		if (mx >= 905 && mx <= 945 && my >= 60 && my <= 100)
		{
			if (!musicOn)//////
			{

				musicOn = true;
				PlaySound("Music\\doublebass.wav", NULL, SND_LOOP | SND_ASYNC);

			}
		}
		if (mx >= 980 && mx <= 1020 && my >= 60 && my <= 100)
		{
			if (musicOn)
			{
				musicOn = false;
				PlaySound(0, 0, 0);
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mx >= 500 && mx <= 1000 && my >= 350 && my <= 425 && mode == 0)
		{
			mode = 1;
		}
	}
	
}


void iKeyboard(unsigned char key)
{
	if (key == 'p')
		iPauseTimer(0);

	if (key == 'r')
		iResumeTimer(0);
	int k;
	if (mode = 1)
	{
		if (key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			for (k = 0; k < len; k++)
				str[k] = 0;
			len = 0;
			saveHighScore();
			screen = 0;
		}
		else{

			str[len] = key;
			len++;
		}



		if (key == ' ')
		{
			if (screen == 1 || screen == 2)
			{
				if (game_started == false)
				{
					game_started = true;
				}
			}
		}

	}
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_HOME)
	{
		if (screen == 7)
		{
			screen = 0;
		}
		if (screen == 1)
		{
			screen = 0;
		}
		if (screen == 2)
		{
			screen = 0;
		}
		if (screen == 4)
		{
			screen = 0;
		}
		if (screen == 3)
		{
			screen = 0;
		}
		if (screen == 5)
		{
			screen = 0;
		}
	}



	if (key == GLUT_KEY_LEFT)
	{
		if (paddle_x > 0)
		{
			paddle_x -= 30;
			if (game_started == false)
			{
				ball_x -= 30;
			}
		}
	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (paddle_x < screen_width - paddle_width)
		{
			paddle_x += 30;
			if (game_started == false)
			{
				ball_x += 30;
			}
		}
	}

}

void ballMovement()
{
	if (screen == 1)//////////////////////
	{
		if (game_started)
		{
			ball_x = ball_x + ball_dx;
			ball_y = ball_y + ball_dy;

			if (ball_x + 10 > screen_width || ball_x - 10 < 0)
				ball_dx = -ball_dx;
			if (ball_y + 10 > screen_height || ball_y - 10 < 0)
				ball_dy = -ball_dy;

			//BRICK COLLISION

			for (int i = 0; i < totalBricks; i++)
			{



				if (bricks[i].show == 1 && (ball_x + ball_radius >= bricks[i].brick_x && ball_x - ball_radius <= bricks[i].brick_x + bricks[i].brick_dx) && (ball_y + ball_radius >= bricks[i].brick_y && ball_y - ball_radius <= bricks[i].brick_y + bricks[i].brick_dy))
				{

					bricks[i].show = 0;
					PlaySound("music\\boop1.wav", NULL, SND_FILENAME | SND_ASYNC);
					ball_dy = -ball_dy;
					itoa(score + 100, score_string, 10);
					score = score + 100;

				}

			}

		}
		//paddle ball collusion
		if (ball_x  >= paddle_x && ball_x  <= paddle_x + paddle_width && ball_y  >= paddle_y && ball_y  <= paddle_y + paddle_height)
		{
			PlaySound("music\\boop1.wav", NULL, SND_LOOP || SND_ASYNC);
			ball_dy = -ball_dy;			
		}
		else
		{
			if (ball_y<paddle_y - 50)
			{
				PlaySound("music\\fall.wav", NULL, SND_LOOP || SND_ASYNC);
				reSetBall();
				lives--;
				if (lives == 0)
				{
					screen = 7;
					musicOn = 0;
				}
			}
		}

	}

	if (screen == 2)///////////////////////
	{


		if (game_started)
		{
			ball_x = ball_x + ball_dx;//BALL_X HHOSSE QUARDENT .MANE QUARDENT BORABOR DX KORE BARSE 
			ball_y = ball_y + ball_dy;

			if (ball_x + 10 > screen_width || ball_x - 10 < 0)
				ball_dx = -ball_dx;
			if (ball_y + 10 > screen_height || ball_y - 10 < 0)
				ball_dy = -ball_dy;


			//powerups
			if (powerup_active == 1 && powerups_y >= 0){
				powerups_y -= power_speed;
			}
			if (powerup_active == 1 && powerups_y < 0){
				//powerups_exist=0;
				powerup_active = 0;
				powerups_y = 720;

			}
			//BLOCK COLLISION
			for (int i = 0; i < totalBricks; i++)
			{
				if (bricks[i].show == 1 && (ball_x + ball_radius >= bricks[i].brick_x && ball_x - ball_radius <= bricks[i].brick_x + bricks[i].brick_dx) && (ball_y + ball_radius >= bricks[i].brick_y && ball_y - ball_radius <= bricks[i].brick_y + bricks[i].brick_dy))
				{
					ball_dy = -ball_dy;

					//powerups

					if (powerup_active == 0){

						random_number = rand() % 8;
						powerups_exist = 1;
						powerup_active = 1;


						powerups_x = bricks[i].brick_x;
						//powerups_y=blocks[i][j].y;
						powerups_y = 600;

					}
					bricks[i].show = 0;
					itoa(score + 100, score_string, 10);
					score = score + 100;
					//printf("%d\n",++score);

					PlaySound("music\\boop1.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				//cOLLISION WITH POWERUP
				if (powerup_active == 1 && (powerups_x + powerup_width >= paddle_x && powerups_x - powerup_width <= paddle_x + paddle_width) && (powerups_y == paddle_y + paddle_height))
				{
					//powerups_exist=0;

					powerup_active = 0;

					powerups_y = 720;
					PlaySound("music\\eat.wav", NULL, SND_FILENAME | SND_ASYNC);

					if (random_number == 0) lifePlus();
					if (random_number == 1) paddlePlus();
					if (random_number == 7) ballSlow();
					if (random_number == 3) lifeMinus();
					if (random_number == 4) paddleMinus();
					if (random_number == 5) ballSpeed();
					if (random_number == 6) ballBig();
					if (random_number == 2) ballSmall();
				}
			}

		}
		//paddle ball collusion
		if (ball_x >= paddle_x && ball_x <= paddle_x + paddle_width && ball_y >= paddle_y && ball_y <= paddle_y + paddle_height)
		{
			ball_dy = -ball_dy;
			PlaySound("music\\boop1.wav", NULL, SND_LOOP || SND_ASYNC);
		}
		else
		{
			if (ball_y < paddle_y - 50)
			{
				PlaySound("music\\fall.wav", NULL, SND_LOOP || SND_ASYNC);
				reSetBall();
				powerup_active = 0;
				musicOn = 0;
				lives--;
				if (lives == 0)
				{
					screen = 7;
					musicOn = 0;
				}
			}
		}
	}
}

void reSetBall()
{
	ball_x = 480;//initially ball er stage
	y_axis_margin = 90;//margin ,jar niche gele game over 
	ball_y = y_axis_margin;

	paddle_x = ball_x - 70;
	paddle_y = ball_y - 30;

	game_started = false;

}

void brickFoundation()
{                         
	int sum_x = 100;
	int sum_y = 400;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks[i].red = rand() % 1;
		bricks[i].green = rand() % 220;
		bricks[i].blue = rand() % 255;

		bricks[i].brick_x = sum_x;
		bricks[i].brick_y = sum_y;
		sum_x += 100;
		if (sum_x>1100)
		{
			sum_x = 100;
			sum_y += 30;
		}
	}
}

//FUNCTIONS FOR POWERUPS
void paddlePlus()
{
	if (paddle_width<150)
	{
		paddle_width = 150;
	}
	else
	{
		paddle_width = 250;
		//paddle_height = 35;
	} 
	
}
void paddleMinus()
{
	
	if (paddle_width > 150)
	{
		paddle_width = 150;
	}
	else if (paddle_width == 150)
	{
		paddle_width = 100;
	}
	else
		paddle_width = 50;

}
void ballSpeed()
{
	if ( ball_dx>0)ball_dx = 10;
	if ( ball_dy>0)ball_dy = 10;

	

}
void ballSlow()
{
	if (ball_dx>0)ball_dx = 5;
	if (ball_dy>0)ball_dy = 5;

}
void lifePlus()
{
	if (lives<3) lives++;
}
void lifeMinus()
{
	lives--;
	if (lives == 0)
	{
		screen == 7;
	}
}
void ballSmall()
{
	ball_radius = 5;
}
void ballBig()
{	
	ball_radius = 20;
}


void getHighScore()
{
	FILE* highscore;
	highscore = fopen("highscore.txt", "r+");
	if (!highscore)
	{
		printf("unable to open");

	}
	int i = 0;
	while (!feof(highscore))
	{

		fscanf(highscore, "%d %s", &player[i].pscore, player[i].name);
		i++;		
	}
	fclose(highscore);
}

void saveHighScore()
{
	FILE* highscore;
	highscore = fopen("highscore.txt", "r+");
	if (!highscore)
	{
		printf("unable to open");

	}

	int i = 0;
	while (!feof(highscore))
	{
		fscanf(highscore, "%d %s", &player[i].pscore, player[i].name);
		i++;

	}
	highscore = fopen("highscore.txt", "w+");
	fprintf(highscore, "%d %s\n", score, str2);
	for (int i = 0; i < 10; i++)
	{
		fprintf(highscore, "%d %s\n", player[i].pscore, player[i].name);

	}
	fclose(highscore);
}

int main()
{

	brickFoundation();
	iSetTimer(ball_speed, ballMovement);
	iInitialize(screen_width, screen_height, "Blaster Ball");
	iStart();

	return 0;
}

