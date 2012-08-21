
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define extern            // Keil: Line added for modular project management

#include "easyweb.h"

#include "ENET.h"         // Keil: *.c -> *.h    // ethernet packet driver
#include "tcpip.h"        // Keil: *.c -> *.h    // easyWEB TCP/IP stack
#include <91x_lib.h>      // Keil: Register definition file for STR912

#include "webpage.h"                             // webside for our HTTP server (HTML)

#include "utils.h"
#include "lcd.h"

#include "config.h"
#include "engine.h"
#include "str9renderer.h"
#include "network.h"
#include "str9eventHandler.h"


int main(void)
{
  int isActive=0;
  char text[17];
  data_s * datap = malloc(sizeof(data_s));
  int i = 0;
//  SuPongNet suPongNet;
  
  Player *player1;
  Player *player2;
  Engine *engine;
  SuPong *suPong;
  
  datap->a = 17;
  datap->count =0;
  
  initLCD();
  set_cursor(0,0);
  lcd_print("Booting...");
  GPIO_Write(GPIO7, 0x00);
  GPIO_WriteBit(GPIO7, WHOAMI_LED, Bit_SET);
  
  	// create two players...
	player1 = createPlayer("Player1");
	player2 = createPlayer("Player2");

	// game logic and the like
	engine = createEngine(str9Renderer, str9eventHandler);
	suPong = createGame(WIDTH, HEIGHT, player1, player2);
	resetEngine(engine);
	// initialize renderer
	//initConsoleRenderer(width + 2, height + 2);

  TCPLowLevelInit();
  DoNetworkStuff();
  
  TCPLocalPort = TCP_PORT_HTTP;                  // set port we want to listen to
  TCPRemotePort = TCP_PORT_HTTP;
  
  #ifdef MASTER
  	isActive = 0;
  #else
    *(unsigned char *)RemoteIP = 192;            
 	*((unsigned char *)RemoteIP + 1) = 168;     
  	*((unsigned char *)RemoteIP + 2) = 2;       
  	*((unsigned char *)RemoteIP + 3) = 180;
	TCPActiveOpen();
	DoNetworkStuff();
	
	isActive = 2;
  #endif
  
  set_cursor(0,0);
  lcd_print(WHOAMI);
  
  while(engine->state == RUNNING)
  //while (1)                                      // repeat forever
  {
  	i++;

  	#ifdef MASTER
    	if (!(SocketStatus & SOCK_ACTIVE)) 
			{
				TCPPassiveOpen();   // listen for incoming TCP-connection
				DoNetworkStuff();
			} 
    #endif
	DoNetworkStuff();                                      // handle network and easyWEB-stack
    DoNetworkStuff();                                                       // events
														   
	if(isActive)
	{	
		engineTick(engine, suPong);	
		send_data(suPong);
		isActive--;
		//Todo delete the next Line!!!
		sprintf(text,"tx i: %i, a: %i", datap->count, datap->a); //Has to be here. Is a very important function. Everbody needs that
		toggleGPIO7(GPIO_Pin_3);
	}else if(isActive == 0)
	{			
		if(SocketStatus & SOCK_CONNECTED)
		{
			if(SocketStatus & SOCK_DATA_AVAILABLE)	
			{
				recieve_data(suPong);
				//Todo delete the next Line!!!
				sprintf(text,"rx i: %i, a: %i",datap->count, datap->a);
				isActive = 1;
				toggleGPIO7(GPIO_Pin_4);
				//engine->renderer(suPong->mGameBoard);
			}
		}
	}
	toggleGPIO7(GPIO_Pin_7);
	for(i = 0; i<160;i++)
	{
		sleep(1000);
		DoNetworkStuff();
	}
  }
  str9renderGameEnd(engine);
  while(1);
}

