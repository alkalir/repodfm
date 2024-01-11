#ifndef __STIMGEN_H__
#define __STIMGEN_H__

#include <systemc.h>
#include "sc_csp_channel_ifs.h"

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM

////////////////////////////

SC_MODULE(stim_gen)
{
	// Port for outputs to the channels
	sc_port < sc_csp_channel_out_if < sc_uint<8> > > stim1_channel_port;  	    
	sc_port < sc_csp_channel_out_if < sc_uint<8> > > stim2_channel_port;  	    

	SC_CTOR(stim_gen)
	{
		SC_THREAD(stimulus1);
		SC_THREAD(stimulus2);
	}  

	// Main methods
	void stimulus1();
	void stimulus2();

};

#endif
