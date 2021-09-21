#include "mainsystem.h"

////////////////////////////////////////////////////////

//CSW
void mainsystem::CSW()
{
	// Temp state variable
	HEPSY_S(CSW_id) pm_state next_state=ND;

	// Copy of required ppm
	sc_uint<8> puls;

	// CSW_timer_mng config
	timer_parameters CSW_timer_cfg;
	HEPSY_S(CSW_id) CSW_timer_cfg.granularity=DEFAULT_GRANULARITY;

	// To activate ALT
	HEPSY_S(CSW_id) NV_DISPATCHER_2_CSW_4_NV->register_alt();
	HEPSY_S(CSW_id) CSW_timer_mng_2_CSW_4_fired->register_alt();

	HEPSY_S(CSW_id) 
	while(true)
	{HEPSY_S(CSW_id) 

		// Activate the CSW process and read desired ppm
		HEPSY_S(CSW_id) puls=CORE_2_CSW_4_start->read();

		// Evaluate timeout (with 60 ppm is 75 ms)
		HEPSY_S(CSW_id) CSW_timer_cfg.timeout=sc_time((NORMAL_FREQ*75/puls.to_int()), SC_MS);	

		// Start CSW_timer_mng with desired timeout and granularity
		HEPSY_S(CSW_id) CSW_2_CSW_timer_mng_4_start->write(CSW_timer_cfg);

		HEPSY_S(CSW_id) 
		while(true)
		{HEPSY_S(CSW_id) 

			// If at least one of the channel is ready...
			HEPSY_S(CSW_id)
			if (NV_DISPATCHER_2_CSW_4_NV->read_test() || CSW_timer_mng_2_CSW_4_fired->read_test())
			{
				// If a natural ventricular is ready to be signaled
				HEPSY_S(CSW_id)
				if (NV_DISPATCHER_2_CSW_4_NV->read_test())
				{
					// Read the natural ventricular
					HEPSY_S(CSW_id) NV_DISPATCHER_2_CSW_4_NV->read();

					// Debug
					#ifdef DEBUG_CSW
					cout << "(CSW) Received NV from dispatcher at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Unblock possible CSW_timer_mng_2_CSW_4_fired pending
					//(in the case both the channels are ready at the same time)
					HEPSY_S(CSW_id)
					if (CSW_timer_mng_2_CSW_4_fired->read_test())
					{
						HEPSY_S(CSW_id) CSW_timer_mng_2_CSW_4_fired->read();

						// Debug
						#ifdef DEBUG_CSW
						cout << "(CSW) Removed CSW timer fired received with NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					// Else stop the timer
					else
					{
						HEPSY_S(CSW_id) CSW_2_CSW_counter_4_stop->write(true);

						// Debug
						#ifdef DEBUG_CSW
						cout << "(CSW) CSW timer stopped at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}

					// Stay in the same state
					HEPSY_S(CSW_id) next_state=AVIrp_state;

					break;
				}
				else // No NV but the timer is ready to fire...
				{
					// Fire!
					HEPSY_S(CSW_id) CSW_timer_mng_2_CSW_4_fired->read();
					
					// Debug
					#ifdef DEBUG_CSW
					cout << "(CSW) CSW timer fired at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Change state
					HEPSY_S(CSW_id) next_state=AVIr_state;

					break;
				}
			}
			else
			{
				// If none of the channels are ready...
				PRE_WAIT(CSW_id)
				wait(NV_DISPATCHER_2_CSW_4_NV->get_alt_event() | CSW_timer_mng_2_CSW_4_fired->get_alt_event());
				POST_WAIT(CSW_id)
			}
		}

		// End of CSW process (signaling the next state)
		HEPSY_S(CSW_id) CSW_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(CSW_id);
	}
}

////////////////////////////////////////////////////////

//CSW_timer_mng
void mainsystem::CSW_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(CSW_timer_mng_id) 
	while(true)
	{HEPSY_S(CSW_timer_mng_id) 

		// Set local timer parameters with CSW_timer_mng ones
		HEPSY_S(CSW_timer_mng_id) timer=CSW_2_CSW_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(CSW_timer_mng_id) CSW_timer_mng_2_CSW_counter_4_start->write(timer);
		// Wait for the counter
		HEPSY_S(CSW_timer_mng_id) fired=CSW_counter_2_CSW_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(CSW_timer_mng_id)
		if (fired) CSW_timer_mng_2_CSW_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(CSW_timer_mng_id);
	}
}

//CSW_counter
void mainsystem::CSW_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(CSW_counter_id) 
	while(true)
	{HEPSY_S(CSW_counter_id) 

		HEPSY_S(CSW_counter_id) timer=CSW_timer_mng_2_CSW_counter_4_start->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(CSW_counter_id) 
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!CSW_2_CSW_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(CSW_counter_id) 

			HEPSY_S_TIMER(CSW_counter_id,timer.granularity);
		}

		// If stopped, unblock  CSW_2_CSW_counter_4_stop pending
		HEPSY_S(CSW_counter_id)
		if (CSW_2_CSW_counter_4_stop->read_test())
		{
			HEPSY_S(CSW_counter_id)
			CSW_2_CSW_counter_4_stop->read();

			HEPSY_S(CSW_counter_id)
			CSW_counter_2_CSW_timer_mng_4_end->write(false);
		}
		else
		{
			HEPSY_S(CSW_counter_id)
			CSW_counter_2_CSW_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(CSW_counter_id);
	}
}

////////////////////////////////////////////////////////
