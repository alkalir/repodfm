#include "mainsystem.h"

////////////////////////////////////////////////////////

//BP
void mainsystem::BP()
{
	// Temp state variable
	HEPSY_S(BP_id) pm_state next_state=ND;

	// Copy of required ppm
	sc_uint<8> puls;

	// BP_timer_mng config
	timer_parameters BP_timer_cfg;
	HEPSY_S(BP_id) BP_timer_cfg.granularity=DEFAULT_GRANULARITY;

	HEPSY_S(BP_id)
	while(true)
	{HEPSY_S(BP_id) 

		// Activate the BP process and read desired ppm
		HEPSY_S(BP_id) puls=CORE_2_BP_4_start->read();

		// Evaluate timeout (with 60 ppm is 25 ms)
		HEPSY_S(BP_id) BP_timer_cfg.timeout=sc_time((NORMAL_FREQ*25/puls.to_int()), SC_MS);	

		// Start BP_timer_mng with desired timeout and granularity
		HEPSY_S(BP_id) BP_2_BP_timer_mng_4_start->write(BP_timer_cfg);

		HEPSY_S(BP_id) BP_timer_mng_2_BP_4_fired->read();

		// Debug
		#ifdef DEBUG_BP
		cout << "(BP) BP timer fired at time \t" << sc_time_stamp() << endl;
		system("pause"); cout << endl;
		#endif

		// Change state
		HEPSY_S(BP_id) next_state=CSW_state;

		// End of BP process (signaling the next state)
		HEPSY_S(BP_id) BP_2_CORE_4_end->write(next_state);

		// Profiling
		HEPSY_P(BP_id);
	}
}

////////////////////////////////////////////////////////

//BP_timer_mng
void mainsystem::BP_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(BP_timer_mng_id)
	while(true)
	{HEPSY_S(BP_timer_mng_id) 

		// Set local timer parameters with BP_timer_mng ones
		HEPSY_S(BP_timer_mng_id) timer=BP_2_BP_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(BP_timer_mng_id) BP_timer_mng_2_BP_counter_4_start->write(timer);
		// Wait for the counter
		HEPSY_S(BP_timer_mng_id) fired=BP_counter_2_BP_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(BP_timer_mng_id)
		if (fired) BP_timer_mng_2_BP_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(BP_timer_mng_id);
	}
}

//BP_counter
void mainsystem::BP_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(BP_counter_id)
	while(true)
	{HEPSY_S(BP_counter_id) 

		HEPSY_S(BP_counter_id) timer=BP_timer_mng_2_BP_counter_4_start->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(BP_counter_id)
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!BP_2_BP_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(BP_counter_id) 

			HEPSY_S_TIMER(BP_counter_id,timer.granularity);
		}

		// If stopped, unblock  BP_2_BP_counter_4_stop pending
		HEPSY_S(BP_counter_id)
		if (BP_2_BP_counter_4_stop->read_test())
		{
			HEPSY_S(BP_counter_id)
			BP_2_BP_counter_4_stop->read();

			HEPSY_S(BP_counter_id)
			BP_counter_2_BP_timer_mng_4_end->write(false);
		}
		else
		{
			HEPSY_S(BP_counter_id) 
			BP_counter_2_BP_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(BP_counter_id);
	}
}

////////////////////////////////////////////////////////
