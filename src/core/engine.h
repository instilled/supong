#ifndef ENGINE_H_
#define ENGINE_H_

#include "types.h"
#include "supong.h"
#include "ui.h"

/**
 * This is where all the magic (logic) happens.
 */

/**
 * States of the engine.  
 */
typedef enum
{
	STOPPED,
	RUNNING,
	//	PAUSE,
	WIN_PLAYER1 = 1,
	WIN_PLAYER2 = 2
} EngineState;

typedef enum
{
	HIT_NOTHING,
	HIT_LEFT,
	HIT_RIGHT,
	HIT_BOTTOM,
	HIT_TOP
} MoveState;

typedef struct
{
	/**
	 * This is the main game logic. It will be initialized
	 * with a default function. If you want to change the
	 * behaviour of the game, this is a good point to start.
	 * Make sure you first call createEngine(...) and then 
	 * alter the pointer to point to your tick function.
	 * 
	 * @engine Pointer type void because
	 * 		   struct Engine not yet defined
	 * @supong The SuPong struct. 
	 */
	void (*update)(void *engine, SuPong *supong);
	
	/**
	 * The SuPong renderer.
	 */
	void (*renderer)(GameBoard *gameBoard);
	
	/**
	 * Handles suPong events and the like.
	 */
	void (*eventHandler)(SuPong *suPong);
	
	/**
	 * Calling run starts the game. If the games
	 * terminates state contains the end state
	 * (WIN_PLAYER1 or WIN_PLAYER2).
	 */
	EngineState state;
	
} Engine;

// prototypes
Engine* createEngine(void(*renderer)(GameBoard *gameBoard), //
		void(*eventHandler)(SuPong *suPong));
void resetEngine(Engine *engine);
void engineTick(Engine *engine, SuPong *suPong);
void movePong(Pong *pong, GameBoard *gameBoard, int x);

#endif /*ENGINE_H_*/
