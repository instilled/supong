
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define extern		//Has to be here. Can't exactly say why. Something with the Network Stuff. :(


#include "config.h"

#include "state.h"
#include "net_tmp.h"
#include "str9renderer.h"

void SCU_Configuration(void);
 
int main() 
{
	// TODO Remove this Variable again
	int isActive;
	char text[] = "                ";
	//state_s state;
	state_s * statep = malloc(sizeof(state_s));

	SuPong *suPong = createGame(2, 16); // create the game board
	UI ui; // our ui
	Engine *engine = createEngine(suPong, &ui); // game logic and the like

	#ifdef MASTER
		isActive = 0;
	#else
		isActive = 2;
	#endif

	SCU_Configuration();

	initLCD();
	lcd_init();
  	lcd_clear();

    set_cursor(0,1);
    lcd_print("  The F-Team");

	TCPLowLevelInit();

	DoNetworkStuff();

	TCPLocalPort = SUPONG_PORT;
  	TCPRemotePort = SUPONG_PORT;
  	

	
	#ifdef MASTER
	#else
		*(unsigned char *)RemoteIP = 192;            
  		*((unsigned char *)RemoteIP + 1) = 168;     
  		*((unsigned char *)RemoteIP + 2) = 1;       
  		*((unsigned char *)RemoteIP + 3) = 180;
		TCPActiveOpen();
		DoNetworkStuff();

	#endif

	set_cursor(0,0);
	lcd_print(WHOAMI);

	#ifdef MASTER
	  //main_master();
	#else
	  //main_slave();
	#endif 
	
	while(1)
	{

				
		#ifdef MASTER
			if (!(SocketStatus & SOCK_ACTIVE)) 
	   		{
				TCPPassiveOpen();   // listen for incoming TCP-connection
	   		}
		#endif
	   	DoNetworkStuff();

		if(isActive)
		{
			#ifdef MASTER
				do_state(statep,1000);
			#else
				do_state(statep,1);
			#endif
			send_state(statep);
			isActive--;
//			set_cursor(0,1);
//			sprintf(text,"tx i: %i, a: %i", statep->count, statep->a);
//			lcd_print(text);
		}

		if(isActive == 0)
		{
			
			if(SocketStatus & SOCK_CONNECTED)
			{
				if(SocketStatus & SOCK_DATA_AVAILABLE)	
				{
					recieve_state(statep);
//					set_cursor(0,0);
//					sprintf(text,"rx i: %i, a: %i",statep->count, statep->a);
//					lcd_print(text);
					isActive = 1;
				}
			}
		}
		DoNetworkStuff();
		sleep(2000);
		//tick(engine);
		//str9renderer(engine->mSuPong);				
	}
}


void SCU_Configuration(void)
{
  // interrupt works without initialising 
  // SCU_APBPeriphClockConfig(__GPIO3 ,ENABLE);
  /* Enable GPIO7 clock*/
  SCU_APBPeriphClockConfig(__GPIO7 ,ENABLE);
  GPIO_DeInit(GPIO7);

  /* Enable WIU clock */
  SCU_APBPeriphClockConfig(__WIU, ENABLE);
  WIU_DeInit();

  /* Enable VIC clock */
  SCU_AHBPeriphClockConfig(__VIC,ENABLE);
  VIC_DeInit();
}
