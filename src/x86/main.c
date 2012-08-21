#include <stdio.h>
#include <unistd.h>

// Note: added 'core' dir to compiler include path
#include "engine.h"

#include "renderer/consoleRenderer.h"

void eventHandler(SuPong *suPong)
{
	// TODO handle events
}

int main(void)
{
	int width = 4;
	int height = 16;

	// create two players...
	Player *player1 = createPlayer("Player1");
	Player *player2 = createPlayer("Player2");

	// game logic and the like
	Engine *engine = createEngine(consoleRenderer, eventHandler);

	// initialize renderer
	initConsoleRenderer(width + 2, height + 2);

	while (TRUE)
	{
		// create the game board
		SuPong *suPong = createGame(width, height, player1, player2);
		resetEngine(engine);
		
		// now run the game...
		while (engine->state == RUNNING)
		{
			engineTick(engine, suPong);
			usleep(100000);
		}

		// engine->state now contains the winner...
		// you could for example restart the game for a next match...
		// do this by calling run(engine, suPong) again
		//	engine->state

		renderGameEnd(engine);
		usleep(1000000);
	}

	// shutdown renderer
	shutdownConsoleRenderer();

	return 0;
}

