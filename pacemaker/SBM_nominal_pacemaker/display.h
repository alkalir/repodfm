#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <systemc.h>
#include "sc_csp_channel_ifs.h"

////////////////////////////

// DISPLAY: PRINTS TO THE SCREEN OUTPUT DATA FROM THE SYSTEM

////////////////////////////

SC_MODULE(display)
{

	// Ports for input by channel

	//// Stimulated atrial
	sc_port< sc_csp_channel_in_if< bool > > SA;
	//// Stimulated ventricular
	sc_port< sc_csp_channel_in_if< bool > > SV;

	// Main methods

	//// Print SA info
	void SA_output();
	//// Print SV info
	void SV_output();

	// Constructor
	SC_CTOR(display)
	{
		// Print SA info
		SC_THREAD(SA_output);

		// Print SV info
		SC_THREAD(SV_output);
	}

};

#endif

/////////////////////////////////
