#include "mainsystem.h"

////////////////////////////////////////////////////////

void mainsystem::NV_DISPATCHER()
{
	// Current state
	HEPSY_S(NV_DISPATCHER_id) pm_state current_state=ND;

	// Register ALT
	HEPSY_S(NV_DISPATCHER_id) CORE_2_NV_DISPATCHER_4_NV->register_alt();
	HEPSY_S(NV_DISPATCHER_id) NV->register_alt();

	HEPSY_S(NV_DISPATCHER_id)
	while(true)
	{HEPSY_S(NV_DISPATCHER_id) 

		// If at least one of the channels are ready...
		HEPSY_S(NV_DISPATCHER_id) 
		if ((CORE_2_NV_DISPATCHER_4_NV->read_test()) || ((NV->read_test())&&(current_state!=ND))) // To avoid manage NV (i.e., N-V at 0) before that the state is set
		{
			// Update status
			HEPSY_S(NV_DISPATCHER_id) 
			if (CORE_2_NV_DISPATCHER_4_NV->read_test()) current_state=CORE_2_NV_DISPATCHER_4_NV->read();

			// Dispatch NV
			HEPSY_S(NV_DISPATCHER_id) 
			if (NV->read_test())
			{
				// Get NV
				HEPSY_S(NV_DISPATCHER_id) NV->read();

				// Debug
				#ifdef DEBUG_DISPATCHER
				cout << "***(NV_DISPATCHER) Received NV at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				HEPSY_S(NV_DISPATCHER_id) 
				switch(current_state)
				{
					case PVARP_state:

						// Dispatch NV to PVARP
						HEPSY_S(NV_DISPATCHER_id) NV_DISPATCHER_2_PVARP_4_NV->write(true);

						// Debug
						#ifdef DEBUG_DISPATCHER
						cout << "(NV_DISPATCHER) Dispatched NV to PVARP at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break;

					case AEIr_state:

						// Dispatch NV to AEIr
						HEPSY_S(NV_DISPATCHER_id) NV_DISPATCHER_2_AEIr_4_NV->write(true);

						// Debug
						#ifdef DEBUG_DISPATCHER
						cout << "(NV_DISPATCHER) Dispatched NV to AEIr at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break;

					case CSW_state:

						// Dispatch NV to CSW
						HEPSY_S(NV_DISPATCHER_id) NV_DISPATCHER_2_CSW_4_NV->write(true);

						// Debug
						#ifdef DEBUG_DISPATCHER
						cout << "(NV_DISPATCHER) Dispatched NV to CSW at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break;

					case AVIr_state:

						// Dispatch NV to AVIr
						HEPSY_S(NV_DISPATCHER_id) NV_DISPATCHER_2_AVIr_4_NV->write(true);

						// Debug
						#ifdef DEBUG_DISPATCHER
						cout << "(NV_DISPATCHER) Dispatched NV to AVIr at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break;

					default:

						// Debug
						#ifdef DEBUG_DFM
						cout << "(DFM) NV_DISPATCHER: Removed unexpected NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break; // Needed only to avoid error when disabling DEBUG_DFM
				}
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(NV_DISPATCHER_id)
			wait(CORE_2_NV_DISPATCHER_4_NV->get_alt_event() | NV->get_alt_event());
			POST_WAIT(NV_DISPATCHER_id)
		}

		// Profiling
		HEPSY_P(NV_DISPATCHER_id);
	}
}

////////////////////////////////////////////////////////

void mainsystem::NA_DISPATCHER()
{
	// Current state
	HEPSY_S(NA_DISPATCHER_id) pm_state current_state=ND;

	// Register ALT
	HEPSY_S(NA_DISPATCHER_id) CORE_2_NA_DISPATCHER_4_NA->register_alt();
	HEPSY_S(NA_DISPATCHER_id) NA->register_alt();

	HEPSY_S(NA_DISPATCHER_id) 
	while(true)
	{HEPSY_S(NA_DISPATCHER_id) 

		// If at least one of the channels are ready...
		HEPSY_S(NA_DISPATCHER_id) 
		if ((CORE_2_NA_DISPATCHER_4_NA->read_test()) || ((NA->read_test())&&(current_state!=ND))) // To avoid manage NV (i.e., N-V at 0) before that the state is set
		{
			// Update status
			HEPSY_S(NA_DISPATCHER_id) 
			if (CORE_2_NA_DISPATCHER_4_NA->read_test()) current_state=CORE_2_NA_DISPATCHER_4_NA->read();

			// Dispatch NV
			HEPSY_S(NA_DISPATCHER_id) 
			if (NA->read_test())
			{
				// Get NA
				HEPSY_S(NA_DISPATCHER_id) NA->read();

				// Debug
				#ifdef DEBUG_DISPATCHER
				cout << "***(NA_DISPATCHER) Received NA at time \t" << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				HEPSY_S(NA_DISPATCHER_id) 
				switch(current_state)
				{

					case AEIr_state:

						// Dispatch NA to AEIr
						HEPSY_S(NA_DISPATCHER_id) NA_DISPATCHER_2_AEIr_4_NA->write(true);

						// Debug
						#ifdef DEBUG_DISPATCHER
						cout << " (NA_DISPATCHER) Dispatched NA to AEIr at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break;

					default:

						// Debug
						#ifdef DEBUG_DFM
						cout << "(DFM) NA_DISPATCHER: Removed unexpected NA at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif

						break; // Needed only to avoid error when disabling DEBUG_DFM
				}
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(NA_DISPATCHER_id)
			wait(CORE_2_NA_DISPATCHER_4_NA->get_alt_event() | NA->get_alt_event());
			POST_WAIT(NA_DISPATCHER_id)
		}

		// Profiling
		HEPSY_P(NA_DISPATCHER_id);
	}
}

////////////////////////////////////////////////////////
