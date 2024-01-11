#include "mainsystem.h"

////////////////////////////////////////////////////////

// COLLECTOR
void mainsystem::SV_COLLECTOR()
{
	// Current state
	HEPSY_S(SV_COLLECTOR_id) pm_state current_state=ND;

	// Register ALT
	HEPSY_S(SV_COLLECTOR_id) AVIrp_2_SV_COLLECTOR_4_SV->register_alt();
	HEPSY_S(SV_COLLECTOR_id) AVIr_2_SV_COLLECTOR_4_SV->register_alt();

	HEPSY_S(SV_COLLECTOR_id)
	while(true)
	{HEPSY_S(SV_COLLECTOR_id)

		// If at least one of the channels are ready...
		HEPSY_S(SV_COLLECTOR_id)
		if ((AVIrp_2_SV_COLLECTOR_4_SV->read_test()) || (AVIr_2_SV_COLLECTOR_4_SV->read_test()))
		{
			HEPSY_S(SV_COLLECTOR_id)
			if (AVIrp_2_SV_COLLECTOR_4_SV->read_test())
			{
				// Collect SV from AVIrp
				HEPSY_S(SV_COLLECTOR_id) AVIrp_2_SV_COLLECTOR_4_SV->read();

				// Debug
				#ifdef DEBUG_COLLECTOR
				cout << "(SV_COLLECTOR) Received SV form AVIrp at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Send to DISPLAY
				HEPSY_S(SV_COLLECTOR_id) SV->write(true);

				// Debug
				#ifdef DEBUG_COLLECTOR
				cout << "(SV_COLLECTOR) Sent SV to DISPLAY at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif
			}

			// Since it is possible to have both no else...
			HEPSY_S(SV_COLLECTOR_id)
			if (AVIr_2_SV_COLLECTOR_4_SV->read_test())
			{
				// Collect S-V from AVIr
				HEPSY_S(SV_COLLECTOR_id) AVIr_2_SV_COLLECTOR_4_SV->read();

				// Debug
				#ifdef DEBUG_COLLECTOR
				cout << "(SV_COLLECTOR) Received SV form AVIr at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Send to DISPLAY
				HEPSY_S(SV_COLLECTOR_id) SV->write(true);

				// Debug
				#ifdef DEBUG_COLLECTOR
				cout << "(SV_COLLECTOR) Sent SV to DISPLAY at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif
			}
		}
		else
		{
			PRE_WAIT(SV_COLLECTOR_id)
			wait(AVIrp_2_SV_COLLECTOR_4_SV->get_alt_event() | AVIr_2_SV_COLLECTOR_4_SV->get_alt_event());
			POST_WAIT(SV_COLLECTOR_id)
		}

		// Profiling
		HEPSY_P(SV_COLLECTOR_id);
	}
}

//////////////////////////////////////////////////////////
