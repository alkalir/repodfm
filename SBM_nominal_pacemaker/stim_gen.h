#ifndef __STIMGEN_H__
#define __STIMGEN_H__

#include <systemc.h>
#include "sc_csp_channel_ifs.h"

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM

////////////////////////////

SC_MODULE(stim_gen)
{
	// Ports for outputs to the channels

	//// CONFIG
	//// Requested ppm
	sc_port < sc_csp_channel_out_if < sc_uint<8> > > f;  	    

	//// HEART
	//// Natural atrial
	sc_port < sc_csp_channel_out_if < bool > > NA;  	    
	//// Natural ventricular
	sc_port < sc_csp_channel_out_if < bool > > NV;  	    

	// Main methods
	
	//// Set the requested ppm
	void config();
	//// Generate natural stimulus
	void stimulus();
	
	// Reference bpm
	unsigned int ref_bpm;

	// Constructor
	SC_CTOR(stim_gen)
	{
		// Set the requested ppm
		SC_THREAD(config);

		// Generate natural stimulus
		SC_THREAD(stimulus);

		// To be changed as needed
		//ref_bpm=40;
		ref_bpm=60;
		//ref_bpm=180;
	}  

};

#endif
