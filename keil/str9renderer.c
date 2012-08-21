#include "str9renderer.h"
#include "lcd.h"

#include "engine.h"
#include "config.h"

#include <stdio.h>

void str9Renderer(GameBoard *gameBoard)
{
	int x,y;
	int startx, stopx;
	char board[4][16];
	
	
	for(y = 0; y < gameBoard->mHeight; y++)
	{
		for(x = 0; x < gameBoard->mWidth; x++)
		{
			//set_cursor(y,x);
			//lcd_print("x");
			board[x][y] = ' ';
			//DoNetworkStuff();
		}		
	}	
	
	{
		Pong *pong;
		pong = gameBoard->mPong1;
		for(x = 0 ;x < pong->mLength; x++)
		{
			board[pong->mX + x][0] = '|';
		}
		
		pong = gameBoard->mPong2;
		for(x = 0 ;x < pong->mLength; x++)
		{
			board[pong->mX + x][gameBoard->mHeight-1] = '|';
		}
	}
	
	{
		Ball *ball;
		ball = gameBoard->mBall;
		board[ball->mX][ball->mY] = 'O';
	}
	
	#ifdef MASTER
		startx = 0;
		stopx = 2;
	#else
		startx = 2;
		stopx = 4;
	#endif
	
	for(y = 0; y < gameBoard->mHeight; y++)
	{
		for(x = startx; x < stopx; x++)
		{
			int disx;
			int disy;
			#ifdef MASTER
				disx = y;
				disy = 1-x;
			#else
				disx = 15-y;
				disy = x-2;
			#endif
			set_cursor(disx,disy);
			lcd_putchar(board[x][y]);
			DoNetworkStuff();
		}		
	}
	set_cursor(1,17);
}

 
void str9renderGameEnd(Engine *engine)
{
	char msg[16];
	lcd_clear();
	sprintf(msg, "Player%i won.", engine->state);
	set_cursor(0, 0);
	lcd_print(msg);
}
