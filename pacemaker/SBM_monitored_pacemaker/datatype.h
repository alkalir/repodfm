#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <systemc.h>
#include "define.h"

//////////////////////////////
// DATATYPES (i.e., MESSAGES) USED BY THE CHANNELS
//////////////////////////////

// Timer
struct timer_parameters
{
	// Time interval measured by the (countdown) timer
	sc_time timeout;  // 16 bit
	// Granularity used to decrease the timer
	sc_time granularity; // 8 bit
};

// Unexpected Natural Event
struct UNE_info
{
	// NA (0) or NV (1)
	bool UNE_type;

	// State in which the event is happened
	pm_state UNE_state;
};

#endif
