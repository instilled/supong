#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lcd.h"
#include "utils.h"
#include "../core/engine.h"

void str9renderer(SuPong *suPong)
{
	GameBoard *gameBoard = suPong->mGameBoard;
	INT x, y;

	// clear LCD STR9
	// function lcd_clear does not work with network stuff
	// why????
	//	for (y = 0; y < gameBoard->mHeight; y++)
	//	{
	//		for (x = 0; x < gameBoard->mWidth; x++)
	//		{
	lcd_clear();
//	set_cursor(0, 0);
//	lcd_print("asdfasdf");
//	sleep(1000);
	
	//set_cursor(0,1);
	//lcd_print("asdfasdf");
	//sleep(10000);
	//	set_cursor(0, 1);
	//	lcd_print("                ");
	//		}
	//	}

	// players pong...
	{
		INT i;
		Pong *pong;
		pong = suPong->mPlayer1->mPong;
		for (i = 0; i < pong->mLength; i++)
		{
			y = 0 * gameBoard->mWidth;
			set_cursor(y, 1 - pong->mX + i);
			lcd_print("|");
		}

		pong = suPong->mPlayer2->mPong;
		for (i = 0; i < pong->mLength; i++)
		{
			y = (gameBoard->mHeight -1) * gameBoard->mWidth;
			set_cursor(y, 1 - pong->mX + i);
			lcd_print("|");
		}
	}

	// ball
	{
		Ball *ball;
		ball = suPong->mBall;

		// coordinate system transformation for str9 display
		x = ball->mY;
		y = 1 - ball->mX;
		set_cursor(x, y);
		lcd_print("X");
	}

	// remove Cursor from Display
	// TODO disable curser in display... maybe
	set_cursor(1, 17);
}
