#include "state.h"

void do_state(state_s * state, int increase)
{
 	state->count = state->count + increase;
}
