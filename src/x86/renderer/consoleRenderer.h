#ifndef CONSOLERENDERER_H_
#define CONSOLERENDERER_H_

void initConsoleRenderer(int width, int height);
void consoleRenderer(GameBoard *gameBoard);
void renderGameEnd(Engine *engine);
void shutdownConsoleRenderer();

#endif /*CONSOLERENDERER_H_*/
