#ifndef __STATE_H__
#define __STATE_H__

typedef struct
{
	int a;
	int count;
	//unsigned char some_data[1000];
} state_s;

void do_state(state_s * state, int increase);

#endif
