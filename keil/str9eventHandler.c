#include "str9eventHandler.h"
#include <91x_lib.h>
#include "utils.h"
#include "config.h"

// private prototypes
unsigned int GetAD7Val(void);

void str9eventHandler(SuPong *suPong)
{
	GameBoard *gameBoard = suPong->mGameBoard;
	Pong *pong;
//	int x = 0;
	int newADVal =  GetAD7Val();

#ifdef MASTER // MASTER = player1
	pong = gameBoard->mPong1;
#else // SLAVE = player2
	pong = gameBoard->mPong2;
#endif

	newADVal = (newADVal-512)/50;
	newADVal = newADVal > 1 ? 1 : newADVal;
	newADVal = newADVal < -1 ? -1 : newADVal;

	movePong(pong, suPong->mGameBoard, newADVal);
	
}

unsigned int GetAD7Val(void)
{
	// Keil: function replaced to handle LPC2378 A/D converter.
	unsigned int val;

	val = ADC->CR & ~(0x0007 << 6); // ch = 0
	ADC->CR = val | 0x0001; // Start A/D Conversion
	do
	{
		val = ADC->CR; // Read A/D Control Register
	} while ((val & 0x8000) == 0); // Wait for end of A/D Conversion
	ADC->CR &= ~0x0001; // Stop A/D Conversion
	val = (ADC->DR0) & 0x03FF; // Extract AIN0 Value
	return val; // result of A/D process 
}
