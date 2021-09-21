#include "stim_gen.h"
#include "define.h"

// Data used to provide debug info
#ifdef DEBUG_OUT
	extern sc_time prev_V, prev_A, prev_S, LRL[100], I1[100], I2[100], I3[100], I4[100], I5[100], I6[100];
	extern unsigned int ilrl, i1, i2, i3, i4, i5, i6;
#endif

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM

////////////////////////////

// Set the requested ppm
void stim_gen::config()
{
	// Setup
	f->write(ref_bpm);
}

// Generate natural stimulus
void stim_gen::stimulus()
{

///////////////////////
// Reference Inputs
///////////////////////

	// COMMENT/DECOMMENT WHAT NEEDED

	//////////// Regular cycle

	while(1)
	{
		wait(60*800/ref_bpm, SC_MS); // WARNING: 799 -> vedi analyzer
		NA->write(true);
		// Write output
		cout << "(STIMULUS) NA at time \t" << sc_time_stamp() << endl;

		#ifdef DEBUG_VAL
			cout << "(VAL) Delta A = " << sc_time_stamp()-prev_A << endl << endl;
			prev_A = sc_time_stamp();
		#endif

		#ifdef PAUSE
			system("pause"); cout << endl;
		#endif

		wait(60*200/ref_bpm, SC_MS);
		NV->write(true);
		// Write output
		cout << "(STIMULUS) NV at time \t" << sc_time_stamp() << endl;

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

	///////////////////////

	////// Artificial cycle

	// No stimulus from the earth

	///////////////////////

	//// Ony NA

	//while(1)
	//{
	//	wait(60*800/ref_bpm, SC_MS); // WARNING: 799 -> vedi analyzer
	//	NA->write(true);
	//	// Write output
	//	cout << "(STIMULUS) NA at time \t" << sc_time_stamp() << endl;

	//	#ifdef DEBUG_VAL
	//		cout << "(VAL) Delta A = " << sc_time_stamp()-prev_A << endl << endl;
	//		prev_A = sc_time_stamp();
	//	#endif

	//	#ifdef PAUSE
	//		system("pause"); cout << endl;
	//	#endif

	//	wait(60*200/ref_bpm, SC_MS);
	//}

	///////////////////////

}

// END
 