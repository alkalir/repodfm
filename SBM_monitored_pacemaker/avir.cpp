#include "mainsystem.h"

////////////////////////////////////////////////////////

//AVIr
void mainsystem::AVIr()
{
	// Temp state variable
	HEPSY_S(AVIr_id) pm_state next_state=ND;

	// Copy of required ppm
	sc_uint<8> puls;

	// AVIr_timer_mng config
	timer_parameters AVIr_timer_cfg;
	HEPSY_S(AVIr_id) AVIr_timer_cfg.granularity=DEFAULT_GRANULARITY;

	// To activate ALT
	HEPSY_S(AVIr_id) NV_DISPATCHER_2_AVIr_4_NV->register_alt();
	HEPSY_S(AVIr_id) AVIr_timer_mng_2_AVIr_4_fired->register_alt();

	HEPSY_S(AVIr_id)
	while(true)
	{HEPSY_S(AVIr_id) 

		// Activate the AVIr process and read desired ppm
		HEPSY_S(AVIr_id) puls=CORE_2_AVIr_4_start->read();

		// Evaluate timeout (with 60 ppm is 400 ms)
		HEPSY_S(AVIr_id) AVIr_timer_cfg.timeout=sc_time((NORMAL_FREQ*100/puls.to_int()), SC_MS);	

		// Start AVIr_timer_mng with desired timeout and granularity
		HEPSY_S(AVIr_id) AVIr_2_AVIr_timer_mng_4_start->write(AVIr_timer_cfg);

		HEPSY_S(AVIr_id)
		while(true)
		{HEPSY_S(AVIr_id) 

			// If at least one of the channel is ready...
			HEPSY_S(AVIr_id)
			if (NV_DISPATCHER_2_AVIr_4_NV->read_test() || AVIr_timer_mng_2_AVIr_4_fired->read_test())
			{
				// If a natural ventricular is ready to be signaled
				HEPSY_S(AVIr_id)
				if (NV_DISPATCHER_2_AVIr_4_NV->read_test())
				{
					// Get the natural ventricular
					HEPSY_S(AVIr_id) NV_DISPATCHER_2_AVIr_4_NV->read();

					// Debug
					#ifdef DEBUG_AVIr
					cout << "(AVIr) Received NV from dispatcher at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Unblock possible AVIr_timer_mng_2_AVIr_4_fired pending
					//(in the case both the channels are ready at the same time)
					HEPSY_S(AVIr_id) 
					if (AVIr_timer_mng_2_AVIr_4_fired->read_test())
					{
						HEPSY_S(AVIr_id) AVIr_timer_mng_2_AVIr_4_fired->read();

						// Debug
						#ifdef DEBUG_AVIr
						cout << "(AVIr) Removed AVIr timer fired received with NV at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					// Else stop the timer
					else
					{
						HEPSY_S(AVIr_id) AVIr_2_AVIr_counter_4_stop->write(true);

						// Debug
						#ifdef DEBUG_AVIr
						cout << "(AVIr) AVIr timer stopped at time \t" << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}

					// New state
					HEPSY_S(AVIr_id) next_state=PVARP_state;

					break;
				}
				else // No NV but the timer is ready to fire...
				{
					// Fire!
					HEPSY_S(AVIr_id) AVIr_timer_mng_2_AVIr_4_fired->read();
					
					// Debug
					#ifdef DEBUG_PVARP
					cout << "(AVIr) AVIr timer fired at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Generate stimulated atrial
					HEPSY_S(AVIr_id) AVIr_2_SV_COLLECTOR_4_SV->write(true);

					// Debug
					#ifdef DEBUG_PVARP
					cout << "(AVIr) Sent SV to collector at time \t" << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif

					// Change state
					HEPSY_S(AVIr_id) next_state=PVARP_state;

					break;
				}
			}
			else
			{
				// If none of the channels are ready...
				PRE_WAIT(AVIr_id)
				wait(NV_DISPATCHER_2_AVIr_4_NV->get_alt_event() | AVIr_timer_mng_2_AVIr_4_fired->get_alt_event());
				POST_WAIT(AVIr_id)
			}
		}

		// End of AVIr process (signaling the next state)
		HEPSY_S(AVIr_id) AVIr_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(AVIr_id);
	}
}

////////////////////////////////////////////////////////

//AVIr_timer_mng
void mainsystem::AVIr_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(AVIr_timer_mng_id)
	while(true)
	{HEPSY_S(AVIr_timer_mng_id) 

		// Set local timer parameters with AVIr_timer_mng ones
		HEPSY_S(AVIr_timer_mng_id) timer=AVIr_2_AVIr_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(AVIr_timer_mng_id) AVIr_timer_mng_2_AVIr_counter_4_fired->write(timer);
		// Wait for the counter
		HEPSY_S(AVIr_timer_mng_id) fired=AVIr_counter_2_AVIr_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(AVIr_timer_mng_id)
		if (fired) AVIr_timer_mng_2_AVIr_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(AVIr_timer_mng_id);
	}
}

//AVIr_counter
void mainsystem::AVIr_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(AVIr_counter_id)
	while(true)
	{HEPSY_S(AVIr_counter_id) 

		HEPSY_S(AVIr_counter_id) timer=AVIr_timer_mng_2_AVIr_counter_4_fired->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(AVIr_counter_id)
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!AVIr_2_AVIr_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(AVIr_counter_id) 

			HEPSY_S_TIMER(AVIr_counter_id,timer.granularity);
		}

		// If stopped, unblock  AVIr_2_AVIr_counter_4_stop pending
		HEPSY_S(AVIr_counter_id)
		if (AVIr_2_AVIr_counter_4_stop->read_test())
		{
			HEPSY_S(AVIr_counter_id)
			AVIr_2_AVIr_counter_4_stop->read();

			HEPSY_S(AVIr_counter_id)
			AVIr_counter_2_AVIr_timer_mng_4_end->write(false);
		}
		else
		{
			HEPSY_S(AVIr_counter_id)
			AVIr_counter_2_AVIr_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(AVIr_counter_id);
	}
}

////////////////////////////////////////////////////////
