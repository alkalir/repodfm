#include "mainsystem.h"

////////////////////////////////////////////////////////

//AVIrp
void mainsystem::AVIrp()
{
	// Temp state variable
	HEPSY_S(AVIrp_id) pm_state next_state=ND;

	HEPSY_S(AVIrp_id) 
	while(true)
	{HEPSY_S(AVIrp_id) 

		// Activate the AVIrp process
		HEPSY_S(AVIrp_id) CORE_2_AVIrp_4_start->read();

		// Wait fire by CORE
		HEPSY_S(AVIrp_id) CORE_2_AVIrp_4_fired->read();

		// Debug
		#ifdef DEBUG_AVIrp
		cout << "(CORE/AVIrp) CORE/AVIrp timer fired at time \t" << sc_time_stamp() << endl;
		system("pause"); cout << endl;
		#endif

		// Generate stimulated atrial
		HEPSY_S(AVIrp_id) AVIrp_2_SV_COLLECTOR_4_SV->write(true);

		// Debug
		#ifdef DEBUG_AVIrp
		cout << "(AVIrp) Sent SV to collector at time \t" << sc_time_stamp() << endl;
		system("pause"); cout << endl;
		#endif

		// Change state
		HEPSY_S(AVIrp_id) next_state=PVARP_state;

		// End of AVIrp process (signaling the next state)
		HEPSY_S(AVIrp_id) AVIrp_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(AVIrp_id);
	}
}

////////////////////////////////////////////////////////
