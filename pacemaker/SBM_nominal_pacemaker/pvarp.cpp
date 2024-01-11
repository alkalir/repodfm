#include "mainsystem.h"

////////////////////////////////////////////////////////

//PVARP
void mainsystem::PVARP()
{
	// Temp state variable
	HEPSY_S(PVARP_id) pm_state next_state=ND;

	// Copy of required ppm
	sc_uint<8> puls;

	// PVARP_timer_mng config
	timer_parameters PVARP_timer_cfg;
	HEPSY_S(PVARP_id) PVARP_timer_cfg.granularity=DEFAULT_GRANULARITY;

	// To activate ALT
	HEPSY_S(PVARP_id) NV_DISPATCHER_2_PVARP_4_NV->register_alt();
	HEPSY_S(PVARP_id) PVARP_timer_mng_2_PVARP_4_fired->register_alt();

	HEPSY_S(PVARP_id) 
	while(true)
	{HEPSY_S(PVARP_id) 

		// Activate the PVARP process and read desired ppm
		HEPSY_S(PVARP_id) puls=CORE_2_PVARP_4_start->read();

		// Evaluate timeout (with 60 ppm is 400 ms)
		HEPSY_S(PVARP_id) PVARP_timer_cfg.timeout=sc_time((NORMAL_FREQ*400/puls.to_int()), SC_MS);	

		// Start PVARP_timer_mng with desired timeout and granularity
		HEPSY_S(PVARP_id) PVARP_2_PVARP_timer_mng_4_start->write(PVARP_timer_cfg);

		HEPSY_S(PVARP_id) 
		while(true)
		{HEPSY_S(PVARP_id) 

			// If at least one of the channel is ready...
			HEPSY_S(PVARP_id) 
			if (NV_DISPATCHER_2_PVARP_4_NV->read_test() || PVARP_timer_mng_2_PVARP_4_fired->read_test())
			{
				// If a natural ventricular is ready to be signaled
				HEPSY_S(PVARP_id) 
				if (NV_DISPATCHER_2_PVARP_4_NV->read_test())
				{
					// Read the natural ventricular
					HEPSY_S(PVARP_id) NV_DISPATCHER_2_PVARP_4_NV->read();

					// Debug
					#ifdef DEBUG_PVARP
					cout << "(PVARP) Received NV from dispatcher at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Unblock possible PVARP_timer_mng_2_PVARP_4_fired pending
					//(in the case both the channels are ready at the same time)
					HEPSY_S(PVARP_id) 
					if (PVARP_timer_mng_2_PVARP_4_fired->read_test())
					{
						HEPSY_S(PVARP_id) PVARP_timer_mng_2_PVARP_4_fired->read();

						// Debug
						#ifdef DEBUG_PVARP
						cout << "(PVARP) Removed PVARP timer fired received with NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					else 	// Else stop the timer
					{
						HEPSY_S(PVARP_id) PVARP_2_PVARP_counter_4_stop->write(true);

						// Debug
						#ifdef DEBUG_PVARP
						cout << "(PVARP) PVARP timer stopped at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}

					// Stay in the same state
					HEPSY_S(PVARP_id) next_state=PVARP_state;

					break;
				}
				else // No NV but the timer is ready to fire...
				{
					// Fire!
					HEPSY_S(PVARP_id) PVARP_timer_mng_2_PVARP_4_fired->read();
					
					// Debug
					#ifdef DEBUG_PVARP
					cout << "(PVARP) PVARP timer fired at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Change state
					HEPSY_S(PVARP_id) next_state=AEIr_state;

					break;
				}
			}
			else
			{
				// If none of the channels are ready...
				PRE_WAIT(PVARP_id)
				wait(NV_DISPATCHER_2_PVARP_4_NV->get_alt_event() | PVARP_timer_mng_2_PVARP_4_fired->get_alt_event());
				POST_WAIT(PVARP_id)
			}
		}

		// End of PVARP process (signaling the next state)
		HEPSY_S(PVARP_id) PVARP_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(PVARP_id);
	}
}

////////////////////////////////////////////////////////

//PVARP_timer_mng
void mainsystem::PVARP_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(PVARP_timer_mng_id) 
	while(true)
	{HEPSY_S(PVARP_timer_mng_id) 

		// Set local timer parameters with PVARP_timer_mng ones
		HEPSY_S(PVARP_timer_mng_id) timer=PVARP_2_PVARP_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(PVARP_timer_mng_id) PVARP_timer_mng_2_PVARP_counter_4_start->write(timer);

		// Wait for the counter
		HEPSY_S(PVARP_timer_mng_id) fired=PVARP_counter_2_PVARP_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(PVARP_timer_mng_id) 
		if (fired) PVARP_timer_mng_2_PVARP_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(PVARP_timer_mng_id);
	}
}

//PVARP_counter
void mainsystem::PVARP_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(PVARP_counter_id) 
	while(true)
	{HEPSY_S(PVARP_counter_id) 

		HEPSY_S(PVARP_counter_id) timer=PVARP_timer_mng_2_PVARP_counter_4_start->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(PVARP_counter_id) 
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!PVARP_2_PVARP_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(PVARP_counter_id) 

			HEPSY_S_TIMER(PVARP_counter_id, timer.granularity);
		}

		// If stopped, unblock  PVARP_2_PVARP_counter_4_stop pending
		HEPSY_S(PVARP_counter_id) 
		if (PVARP_2_PVARP_counter_4_stop->read_test())
		{
			HEPSY_S(PVARP_counter_id) 
			PVARP_2_PVARP_counter_4_stop->read();

			HEPSY_S(PVARP_counter_id) 
			PVARP_counter_2_PVARP_timer_mng_4_end->write(false);
		}
		else
		{
			HEPSY_S(PVARP_counter_id) 
			PVARP_counter_2_PVARP_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(PVARP_counter_id);
	}
}

////////////////////////////////////////////////////////
