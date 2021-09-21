#include "mainsystem.h"

////////////////////////////////////////////////////////

//AEIr
void mainsystem::AEIr()
{
	// Temp state variable
	HEPSY_S(AEIr_id) pm_state next_state=ND;

	// Copy of required ppm
	sc_uint<8> puls;

	// AEIr_timer_mng config
	timer_parameters AEIr_timer_cfg;
	HEPSY_S(AEIr_id) AEIr_timer_cfg.granularity=DEFAULT_GRANULARITY;

	// To activate ALT
	HEPSY_S(AEIr_id) NV_DISPATCHER_2_AEIr_4_NV->register_alt();
	HEPSY_S(AEIr_id) NA_DISPATCHER_2_AEIr_4_NA->register_alt();
	HEPSY_S(AEIr_id) AEIr_timer_mng_2_AEIr_4_fired->register_alt();

	HEPSY_S(AEIr_id) 
	while(true)
	{
		// Activate the AEIr process and read desired ppm
		HEPSY_S(AEIr_id) puls=CORE_2_AEIr_4_start->read();

		// Evaluate timeout (with 60 ppm is 400 ms)
		HEPSY_S(AEIr_id) AEIr_timer_cfg.timeout=sc_time((NORMAL_FREQ*400/puls.to_int()), SC_MS);	

		// Start AEIr_timer_mng with desired timeout and granularity
		HEPSY_S(AEIr_id) AEIr_2_AEIr_timer_mng_4_start->write(AEIr_timer_cfg);

		HEPSY_S(AEIr_id) 
		while(true)
		{HEPSY_S(AEIr_id)

			// If at least one of the channel is ready...
			HEPSY_S(AEIr_id)
			if (NV_DISPATCHER_2_AEIr_4_NV->read_test() || NA_DISPATCHER_2_AEIr_4_NA->read_test() || AEIr_timer_mng_2_AEIr_4_fired->read_test())
			{

				// If a natural ventricular is ready to be signaled
				HEPSY_S(AEIr_id)
				if (NV_DISPATCHER_2_AEIr_4_NV->read_test())
				{
					// Get the natural ventricular
					HEPSY_S(AEIr_id) NV_DISPATCHER_2_AEIr_4_NV->read();

					// Debug
					#ifdef DEBUG_AEIR
					cout << "(AEIr) Received NV from dispatcher at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Unblock possible AEIr_timer_mng_2_AEIr_4_fired pending
					//(in the case both the channels are ready at the same time)
					HEPSY_S(AEIr_id)
					if (AEIr_timer_mng_2_AEIr_4_fired->read_test())
					{
						HEPSY_S(AEIr_id) AEIr_timer_mng_2_AEIr_4_fired->read();

						// Debug
						#ifdef DEBUG_AEIR
						cout << "(AEIr) Removed AEIr timer fired received with NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					else // Else stop the timer
					{
						HEPSY_S(AEIr_id) AEIr_2_AEIr_counter_4_stop->write(true);

						// Debug
						#ifdef DEBUG_AEIR
						cout << "(AEIr) AEIr timer stopped at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}

					// If also NA ready, ERROR! Remove it
					#ifdef DEBUG_DFM
					/*HEPSY_S(AEIr_id)*/ // In debug mode time is not considered
					if (NA_DISPATCHER_2_AEIr_4_NA->read_test())
					{
						/*HEPSY_S(AEIr_id)*/ // In debug mode time is not considered
						NA_DISPATCHER_2_AEIr_4_NA->read();

						//// Debug
						//#ifdef DEBUG_AEIR
						cout << "(DFM) AEIr: WARNING!!! Unexpected NA received and removed at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						//#endif
					}
					#endif

					// New state
					HEPSY_S(AEIr_id) next_state=PVARP_state;

					break;
				}
				// If a natural atrial is ready to be signaled
				else if (NA_DISPATCHER_2_AEIr_4_NA->read_test())
				{HEPSY_S(AEIr_id) 

					// Get the natural atrial
					HEPSY_S(AEIr_id) NA_DISPATCHER_2_AEIr_4_NA->read();

					// Debug
					#ifdef DEBUG_AEIR
					cout << "(AEIr) Received NA from dispatcher at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Unblock possible AEIr_timer_mng_2_AEIr_4_fired pending
					//(in the case both the channels are ready at the same time)
					HEPSY_S(AEIr_id)
					if (AEIr_timer_mng_2_AEIr_4_fired->read_test())
					{
						HEPSY_S(AEIr_id) AEIr_timer_mng_2_AEIr_4_fired->read();

						// Debug
						#ifdef DEBUG_AEIR
						cout << "(AEIr) Removed AEIr timer fired received with NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					else // Else stop the timer
					{
						HEPSY_S(AEIr_id) AEIr_2_AEIr_counter_4_stop->write(true);

						// Debug
						#ifdef DEBUG_AEIR
						cout << "(AEIr) AEIr timer stopped at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}

					// New state
					HEPSY_S(AEIr_id) next_state=BP_state;

					break;
				}
				else // No NV/NA but the timer is ready to fire...
				{
					// Fire!
					HEPSY_S(AEIr_id) AEIr_timer_mng_2_AEIr_4_fired->read();
					
					// Debug
					#ifdef DEBUG_AEIR
					cout << "(AEIr) AEIr timer fired at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Generate stimulated atrial
					HEPSY_S(AEIr_id) SA->write(true);

					// Change state
					HEPSY_S(AEIr_id) next_state=BP_state;

					break;
				}
			}
			else
			{
				// If none of the channels are ready...
				PRE_WAIT(AEIr_id)
				wait(NV_DISPATCHER_2_AEIr_4_NV->get_alt_event() | NA_DISPATCHER_2_AEIr_4_NA->get_alt_event() | AEIr_timer_mng_2_AEIr_4_fired->get_alt_event());
				POST_WAIT(AEIr_id)
			}
		}

		// End of AEIr process (signaling the next state)
		HEPSY_S(AEIr_id) AEIr_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(AEIr_id);
	}
}

////////////////////////////////////////////////////////

//AEIr_timer_mng
void mainsystem::AEIr_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(AEIr_timer_mng_id) 
	while(true)
	{HEPSY_S(AEIr_timer_mng_id) 

		// Set local timer parameters with AEIr_timer_mng ones
		HEPSY_S(AEIr_timer_mng_id) timer=AEIr_2_AEIr_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(AEIr_timer_mng_id) AEIr_timer_mng_2_AEIr_counter_4_start->write(timer);
		// Wait for the counter
		HEPSY_S(AEIr_timer_mng_id) fired=AEIr_counter_2_AEIr_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(AEIr_timer_mng_id) 
		if (fired) AEIr_timer_mng_2_AEIr_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(AEIr_timer_mng_id);
	}
}

//AEIr_counter
void mainsystem::AEIr_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(AEIr_counter_id) 
	while(true)
	{HEPSY_S(AEIr_counter_id)

		HEPSY_S(AEIr_counter_id)timer=AEIr_timer_mng_2_AEIr_counter_4_start->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(AEIr_counter_id)
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!AEIr_2_AEIr_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(AEIr_counter_id)

			HEPSY_S_TIMER(AEIr_counter_id,timer.granularity);
		}

		// If stopped, unblock  AEIr_2_AEIr_counter_4_stop pending
		HEPSY_S(AEIr_counter_id)
		if (AEIr_2_AEIr_counter_4_stop->read_test())
		{
			HEPSY_S(AEIr_counter_id)
			AEIr_2_AEIr_counter_4_stop->read();

			HEPSY_S(AEIr_counter_id)
			AEIr_counter_2_AEIr_timer_mng_4_end->write(false);
		}
		else
		{
			HEPSY_S(AEIr_counter_id) 
			AEIr_counter_2_AEIr_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(AEIr_counter_id);
	}
}

//////////////////////////////////////////////////////////
