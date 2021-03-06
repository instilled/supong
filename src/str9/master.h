#ifndef __MASTER_H__
#define __MASTER_H__

	//Set IP Adress
	#define MYIP_1               192         
	#define MYIP_2               168
	#define MYIP_3               1
	#define MYIP_4               180

	#define MYMAC_1         0x00            /* our ethernet (MAC) address        */
	#define MYMAC_2         0x30            /* (MUST be unique in LAN!)          */
	#define MYMAC_3         0x6C
	#define MYMAC_4         0x00
	#define MYMAC_5         0x00
	#define MYMAC_6         0x02


	#define SUBMASK_1            255                 // subnet mask
	#define SUBMASK_2            255
	#define SUBMASK_3            255
	#define SUBMASK_4            0

	#define GWIP_1               192                 // standard gateway (used if remote
	#define GWIP_2               168                 // IP is no part of our subnet)
	#define GWIP_3               0
	#define GWIP_4               254

	#define WHOAMI	"SuPong Master"

	// prototypes
	void main_master(void);

#endif
