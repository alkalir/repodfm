#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <systemc.h>
#include "sc_csp_channel_ifs.h"
#include "datatype.h"

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

	// DFM

	// Unexpected timer firing
	sc_port< sc_csp_channel_in_if< bool > > UTF; 
	// Unexpected Natural Event
	sc_port< sc_csp_channel_in_if< UNE_info > > UNE;
	// Unexpected States Sequence
	sc_port< sc_csp_channel_in_if< bool > > USS; 

	// Main methods

	//// Print SA info
	void SA_output();
	//// Print SV info
	void SV_output();
	//// Print UTF info
	void UTF_output();
	//// Print UNE info
	void UNE_output();
	//// Print USS info
	void USS_output();

	// Constructor
	SC_CTOR(display)
	{
		// Print SA info
		SC_THREAD(SA_output);

		// Print SV info
		SC_THREAD(SV_output);

		// Print UTF info
		SC_THREAD(UTF_output);

		// Print UNE info
		SC_THREAD(UNE_output);

		// Print USS info
		SC_THREAD(USS_output);
	}

};

#endif
