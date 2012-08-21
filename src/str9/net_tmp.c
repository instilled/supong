//#include <stdlib.h>
//#include <stdio.h>
#include <string.h>

#include "config.h"

#include "state.h"

void send_state(state_s * state)
{
	memcpy(TCP_TX_BUF,state,sizeof(state_s));
	TCPTxDataCount = sizeof(state_s);	
	TCPTransmitTxBuffer();
}

void recieve_state(state_s * state)
{
	memcpy(state,TCP_RX_BUF,sizeof(state_s));
	TCPReleaseRxBuffer();
}
