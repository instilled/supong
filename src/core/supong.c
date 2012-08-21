#include <stdlib.h>
#include <stdio.h>
#include "supong.h"
#include <string.h>

Player* createPlayer(const char *name)
{
	Player *player;

	player = malloc(sizeof(Player));

	//player->mName = name;
	memcpy(player->mName,name,NAMELENGTH);
	player->mPoints = 0;

	return player;
}

SuPong* createGame(INT width, INT height, Player *player1, Player *player2)
{
	SuPong *suPong;
	suPong = malloc(sizeof(SuPong));

	suPong->mPlayer1 = player1;
	suPong->mPlayer2 = player2;

	{ // gameboard stuff
		GameBoard *gameBoard;
		gameBoard = malloc(sizeof(GameBoard));
		gameBoard->mWidth = width;
		gameBoard->mHeight = height;

		{ // pongs
			Pong *pong;

			pong = malloc(sizeof(Pong));
			pong->mLength = 1;
			pong->mX = width / 2;

			pong->mY = 0;
			gameBoard->mPong1 = pong;

			pong = malloc(sizeof(Pong));
			pong->mLength = 1;
			pong->mX = width / 2;
			// set the pongs place to height...
			pong->mY = height - 1;
			gameBoard->mPong2 = pong;
		}

		{ // set the ball
			Ball *ball;

			ball = malloc(sizeof(Ball));
			ball->mX = width / 2;
			ball->mY = height / 2;
			ball->mDirX = 1;
			ball->mDirY = 1;
			gameBoard->mBall = ball;
		}

		suPong->mGameBoard = gameBoard;
	}

	return suPong;
}
