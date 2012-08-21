#include <stdlib.h>
#include <ncurses.h>

#include "engine.h"
#include "consoleRenderer.h"

WINDOW *gameWin;

void initConsoleRenderer(int width, int height)
{
	int x;
	int y;

	initscr(); /* Start curses mode 		*/

	// disable line buffering...
	cbreak();

	//keypad(stdscr, TRUE); // enable keypad (f? keys and more)

	printw("Welcome to the SuPong game. Have fun!\n");
	printw("     Hit Ctrl-c to quit the game.");
	move(0, 0);

	refresh();

	// center gamewindow
	x = (COLS - width) / 2; /* of the window		*/
	y = (LINES - height) / 2; /* Calculating for a center placement */

	gameWin = newwin(height, width, y, x);

	// default char for vertical and horizontal lines
	box(gameWin, 0, 0);

	// show window
	wrefresh(gameWin);
}

void consoleRenderer(GameBoard *gameBoard)
{
	INT x, y;

	for (y = 0; y < gameBoard->mHeight; y++)
	{
		for (x = 0; x < gameBoard->mWidth; x++)
		{
			mvwprintw(gameWin, y+1, x+1, ".");
		}
	}

	// players pong...
	{
		Pong *pong;
		pong = gameBoard->mPong1;
		for (x = 0; x < pong->mLength; x++)
		{
			mvwprintw(gameWin, 1, x + 1, "-");
		}

		pong = gameBoard->mPong2;
		for (x = 0; x < pong->mLength; x++)
		{
			mvwprintw(gameWin, gameBoard->mHeight, x + 1, "-");
		}
	}

	// ball
	{
		Ball *ball;
		ball = gameBoard->mBall;
		mvwprintw(gameWin, ball->mY + 1, ball->mX + 1, "B");
	}

	// set the cursor to the middle...
	wmove(gameWin, gameBoard->mHeight / 2, 0);

	// refresh screen
	wrefresh(gameWin);
	refresh();
}

void renderGameEnd(Engine *engine)
{
	char *name = malloc(12);
	sprintf(name, "Player%i won.", engine->state);
	mvprintw(4, 5, name);
	refresh();
}

void shutdownConsoleRenderer()
{
	// end curses mode
	endwin();
}
