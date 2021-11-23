/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"

int ball_x=100, ball_y=300;
int dx=7, dy=5;
int a=255; //for color 
int b=255;
int c=255;
bool musicOn=true;
int box_x=40,box_y=0;
int box_width=100;
int box_height=15;


/* 
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here	
	 iClear();
	
	iSetColor (a,b,c);
    iFilledCircle(ball_x, ball_y, 10,1000);

	iFilledRectangle(box_x,box_y,box_width,box_height );
	

	
	iText(80,340, "Press HOME for random color");
	iText(60, 380, "Press a, b or c for color change ");
	iSetColor(0, 0,255 );
	iText(70,40, "Hit m for start or stop music");
	iSetColor(255, 215,0 );
	iText(ball_x-15, ball_y-30, "BALL");
	iSetColor(255, 0,0 );
	iText(20, 10, "Press p for pause, r for resume, END for exit.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iPassiveMouse() is called when the user moves the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iPassiveMouse(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{ 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if (key=='p')
		iPauseTimer(0);
	if (key=='r')
		iResumeTimer(0);
	if (key=='a') //pink
	{
		a =255;
	    b=182;
	    c=193;
	}
	else if (key=='b') //golden 
	{	
		a =255;
	    b=215;
	    c=0;
	}
	else if (key=='c') //sky blue 
	 {	
		a =135;
	    b=206;
	    c=235;
	}	
	if(key =='m')//for music on off with one button
	{  
		if(musicOn)
		{
			musicOn=false ;
			PlaySound(0,0,0);
		}
		else
		{
			musicOn=true;
			PlaySound("Music\\doublebass.wav",NULL,SND_LOOP|SND_ASYNC);
		}
	}




	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key) 
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}



	if(key == GLUT_KEY_LEFT)
	{
		box_x-=5;	
	}

	if(key == GLUT_KEY_RIGHT)
	{
		box_x+=5;	
	}           

	if(key == GLUT_KEY_INSERT)
	{
		a =0;
	    b=0;
	    c=0;	
	}

	if(key == GLUT_KEY_HOME)
	{
		a =rand()%255;
	    b=rand()%255;
	    c=rand()%255;	
	}


	//place your codes for other keys here
}

 
void ballChange (){

	ball_x=ball_x+dx;
	ball_y=ball_y+dy;
		
		/*a =rand()%255; //for random color change 
	    b=rand()%255;
	    c=rand()%255; */

	if (ball_x+10>400  || ball_x-10<0 )
		dx=-dx; 
	if(ball_y+10>400 || ball_y-10<0 )
		dy=-dy;
	
}

int main()
{
	//place your own initialization codes here. 
	iSetTimer(80,ballChange);
	if(musicOn)
	{
	  PlaySound("Music\\doublebass.wav",NULL,SND_LOOP|SND_ASYNC);
	}
	 
	
	iInitialize(400, 400, "Ball Demo");
	iStart();


	return 0;
}

