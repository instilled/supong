#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define MASTER

// TODO: Umbauen
#define SUPONG_SERVER_IP
#define SUPONG_CLIENT_IP 
#define SUPONG_PORT 80

//#define extern

#ifdef MASTER
  #include "master.h"
#else
  #include "slave.h"
#endif 

//#define extern

// Keil: Register definition file for STR912
#include <91x_lib.h>      

//#define extern
#include "ENET.h"         // ethernet packet driver
#include "tcpip.h"
#include "utils.h"
#include "lcd.h"



#endif
