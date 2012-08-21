#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define MASTER

// TODO: Umbauen
//#define SUPONG_SERVER_IP
//#define SUPONG_CLIENT_IP 
#define SUPONG_PORT 80
#define WIDTH 4
#define HEIGHT 16



//#define extern

#ifdef MASTER
  #include "master.h"
#else
  #include "slave.h"
#endif 

//#define extern

#include <91x_lib.h>      // Keil: Register definition file for STR912

//#define extern
#include "ENET.h"         // ethernet packet driver
#include "tcpip.h"
#include "utils.h"
#include "lcd.h"



#endif
