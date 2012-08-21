#include <stdlib.h>
#include "engine.h"
#include "math.h"
#include <string.h>

// private prototypes (visible only in this file)
void defaultUpdate(void *, SuPong *);
MoveState moveBall(GameBoard *);
BOOL onPong(Pong *, Ball *);

Engine* createEngine(void(*renderer)(GameBoard *gameBoard), //
		void(*eventHandler)(SuPong *suPong))
{
	Engine *engine;
	engine = malloc(sizeof(Engine));
	engine->update = defaultUpdate;
	engine->renderer = renderer;
	engine->eventHandler = eventHandler;
	engine->state = RUNNING;
	return engine;
}

void resetEngine(Engine *engine)
{
	engine->state = RUNNING;
}

void engineTick(Engine *engine, SuPong *suPong)
{
	engine->update(engine, suPong);
	engine->renderer(suPong->mGameBoard);
	engine->eventHandler(suPong);
}

// ###-> private functions

/**
 * The default game logic implementation.
 */
void defaultUpdate(void *eng, SuPong *suPong)
{
	// tell the IDE what type eng is...
	Engine *engine = eng;
	
	MoveState moveState = HIT_NOTHING;
	Ball ball;
	memcpy(&ball, suPong->mGameBoard->mBall,sizeof(Ball));
	moveState = moveBall(suPong->mGameBoard);
	switch (moveState)
	{
	case HIT_BOTTOM:
		if (onPong(suPong->mGameBoard->mPong1, &ball) == 0)
		{
			engine->state = WIN_PLAYER2;
		} 
		break;
	case HIT_TOP:
		if (onPong(suPong->mGameBoard->mPong2, &ball) == 0)
		{
			engine->state = WIN_PLAYER1;
		}
		break;
	default:
		;
	}
}

/**
 * MoveBall moves the ball and does nothing 
 * else (no checking of player pongs and the 
 * like). 
 * 
 * @suPong Pointer to the SuPong structure
 */
MoveState moveBall(GameBoard *gameBoard)
{
	Ball *ball = gameBoard->mBall;

	int newX = ball->mX + ball->mDirX;
	int newY = ball->mY + ball->mDirY;

	MoveState state = HIT_NOTHING;

	// check x
	if (-1 < newX && newX < gameBoard->mWidth)
	{
		ball->mX = newX;
		state = HIT_NOTHING;
	}
	else
	{
		// new pos is "out of screen"
		// update pos accordingly (bouncing on wall)
		if (newX < 1)
		{
			newX = 1;
			state = HIT_LEFT;
		}
		else if (newX > gameBoard->mWidth - 2)
		{
			newX = gameBoard->mWidth - 2;
			state = HIT_RIGHT;
		}

		// switch direction x
		ball->mDirX = -(ball->mDirX);
	}

	// y
	if (-1 < newY && newY < gameBoard->mHeight)
	{ // still within screen
		ball->mY = newY;
		state = HIT_NOTHING;
	}
	else
	{
		// new pos is "out of screen"
		// update pos accordingly (bouncing on wall)
		if (newY < 1)
		{
			newY = 1;
			state = HIT_BOTTOM;
		}
		else if (newY > gameBoard->mHeight - 2)
		{
			newY = gameBoard->mHeight - 2;
			state = HIT_TOP;
		}

		// switch direction y
		ball->mDirY = -(ball->mDirY);
	}

	// now set the new position...
	ball->mX = newX;
	ball->mY = newY;

	return state;
}

/**
 * Checks if a ball hits a player's pong.
 * Assumes that ball and player's pong are
 * both on the GameBoard. 
 */
BOOL onPong(Pong *pong, Ball *ball)
{
	int i;
	int y;

	
	/*if(ball->mY>8)
	{
		y = 15;
	} else
	{
		y = 0;
	}*/

	//if (pong->mY == ball->mY)
	{
		for (i = 0; i < pong->mLength; i++)
		{
			if (pong->mX + i == ball->mX)
			{
				return 1;
			}
		}
	}

	return 0;
}

/**
* Moves a pong. New x and y are relative to previous x and y. 
*/
void movePong(Pong *pong, GameBoard *gameBoard, int x)
{
	int newX = pong->mX + x;

	// x 
	if (newX < 0)
	{
		newX = 0;
	}
	else if (newX + pong->mLength > gameBoard->mWidth - 1)
	{
		newX = gameBoard->mWidth - pong->mLength;
	}
	
	pong->mX = newX;
}
