#ifndef SUPONG_H_
#define SUPONG_H_

#include "types.h"
#define NAMELENGTH 3
/**
 * This struct represents the players bar
 */
typedef struct
{
	INT mX;
	INT mY;
	INT mLength;
} Pong;

/**
 * The ball in the game.
 */
typedef struct
{
	INT mX;
	INT mY;

	INT mDirX;
	INT mDirY;
} Ball;

/**
 * The player struct keeps track of the points and
 * the pong.
 */
typedef struct
{
	INT mPoints;
	CHAR mName[NAMELENGTH];

} Player;

/**
 * The GameBoard. It's size and other properties.
 */
typedef struct
{
	INT mWidth;
	INT mHeight;

	Ball *mBall;

	Pong *mPong1;
	Pong *mPong2;

} GameBoard;

/**
 * SuPong holds it all together.
 */
typedef struct
{
	Player *mPlayer1;
	Player *mPlayer2;

	int packetCounter;

	GameBoard *mGameBoard; // the board
} SuPong;

// prototypes
Player* createPlayer(const char * name);
SuPong* createGame(INT width, INT height, Player *player1, Player *player2);

#endif /*SUPONG_H_*/
