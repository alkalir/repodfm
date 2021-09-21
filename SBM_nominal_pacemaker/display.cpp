#include "display.h"
#include "define.h"

// Data used to provide debug info
#ifdef DEBUG_OUT
	extern sc_time prev_V, prev_A, prev_S, LRL[100], I1[100], I2[100], I3[100], I4[100], I5[100], I6[100];
	extern unsigned int ilrl, i1, i2, i3, i4, i5, i6;
#endif

////////////////////////////

// DISPLAY: PRINTS TO THE SCREEN DATA FROM THE SYSTEM

////////////////////////////

// Print S-A info
void display::SA_output()
{

	while(true)
	{
		// Read from channel
		SA->read();

		// Write output
		cout << "(DISPLAY) Received SA at time \t" << sc_time_stamp() << endl;

		#ifdef DEBUG_VAL
			cout << "(VAL) Delta A = " << sc_time_stamp()-prev_A << endl << endl;
			prev_A = sc_time_stamp();
		#endif

		#ifdef PAUSE
			system("pause"); cout << endl;
		#endif
	}
}

// Print S-V info
void display::SV_output()
{

	while(true)
	{
		// Read from channel
		SV->read();

		// Write output
		cout << "(DISPLAY) Received SV at time \t" << sc_time_stamp() << endl;

		#ifdef DEBUG_OUT
			LRL[ilrl++]=sc_time_stamp()-prev_V;
		#endif

		#ifdef DEBUG_VAL
			cout << "(VAL) Delta V = " << sc_time_stamp()-prev_V << endl << endl;
		#endif

		#if defined DEBUG_VAL || defined DEBUG_OUT
			prev_V = sc_time_stamp();
		#endif

		#ifdef PAUSE
			system("pause"); cout << endl;
		#endif
	}
}

////////////////////////////

