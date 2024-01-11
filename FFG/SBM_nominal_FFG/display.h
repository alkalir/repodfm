#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <systemc.h>
#include "sc_csp_channel_ifs.h"

////////////////////////////

// DISPLAY: PRINTS TO THE SCREEN DATA FROM THE SYSTEM

////////////////////////////

SC_MODULE(display)
{

	// Port for input by channel
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > result_channel_port;

	SC_CTOR(display)
	{
		SC_THREAD(output);
	}

	// Main method
	void output();
};

#endif
