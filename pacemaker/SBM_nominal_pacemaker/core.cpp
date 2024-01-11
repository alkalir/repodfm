#include "mainsystem.h"
#include "define.h"

// Data used to provide debug info
#ifdef DEBUG_OUT
	extern sc_time prev_V, prev_A, prev_S, LRL[100], I1[100], I2[100], I3[100], I4[100], I5[100], I6[100];
	extern unsigned int ilrl, i1, i2, i3, i4, i5, i6;
#endif

////////////////////////////////////////////////////////

//CORE: main FSM
void mainsystem::CORE()
{
	// Default puls (60 ppm)
	HEPSY_S(CORE_id) sc_uint<8> puls=60;

	// State variable
	HEPSY_S(CORE_id) pm_state current_state=ND, next_state=ND;
	//// Start state
	HEPSY_S(CORE_id) current_state=PVARP_state;

	// CORE_timer_mng config
	timer_parameters CORE_timer_cfg;
	HEPSY_S(CORE_id) CORE_timer_cfg.granularity=DEFAULT_GRANULARITY;
	//// Evaluate timeout (with 60 ppm is 110 ms)
	HEPSY_S(CORE_id) CORE_timer_cfg.timeout=sc_time((NORMAL_FREQ*110/puls.to_int()), SC_MS);	

	// Main loop
	HEPSY_S(CORE_id)
	while(true)
	{HEPSY_S(CORE_id) 

		// Read required ppm (if any, otherwise default)
		HEPSY_S(CORE_id)
		if (f->read_test()==true)
		{
			HEPSY_S(CORE_id) puls=f->read();

			// Debug
			#ifdef DEBUG_CORE
			cout << endl << "(CORE) Config pacemaker with " << puls << " ppm at time " << sc_time_stamp() << endl;
			system("pause"); cout << endl;
			#endif

			// Evaluate timeout (with 60 ppm is 110 ms)
			HEPSY_S(CORE_id) CORE_timer_cfg.timeout=sc_time((NORMAL_FREQ*110/puls.to_int()), SC_MS);	
		}

		// Send info about status to NV_DISPATCHER
		HEPSY_S(CORE_id) CORE_2_NV_DISPATCHER_4_NV->write(current_state);
		HEPSY_S(CORE_id) CORE_2_NA_DISPATCHER_4_NA->write(current_state);

		// Debug
		#ifdef DEBUG_CORE
		cout << "(CORE) Sent status to dispatchers at " << sc_time_stamp() << endl;
		system("pause"); cout << endl;
		#endif

		// FSM
		HEPSY_S(CORE_id)
		switch (current_state)
		{
			case PVARP_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered PVARP state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif

				// Activate PVARP process
				HEPSY_S(CORE_id) CORE_2_PVARP_4_start->write(puls);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) PVARP process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=PVARP_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) PVARP process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				#ifdef DEBUG_OUT
					I1[i1++]=sc_time_stamp()-prev_S;
				#endif

				break;

			case AEIr_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered AEIr state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif

				// Activate AEIr process
				HEPSY_S(CORE_id) CORE_2_AEIr_4_start->write(puls);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AEIr process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=AEIr_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AEIr process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				// If needed, start CORE_timer_mng used later by AVIrp with desired timeout and granularity
				HEPSY_S(CORE_id)
				if (next_state==BP_state)
				{
					HEPSY_S(CORE_id) CORE_2_CORE_timer_mng_4_start->write(CORE_timer_cfg);

					// Debug
					#ifdef DEBUG_CORE
					cout << "(CORE) CORE/AVIrp timer started at " << sc_time_stamp() << endl;
					system("pause"); cout << endl;
					#endif
				}

				#ifdef DEBUG_OUT
					I2[i2++]=sc_time_stamp()-prev_S;
				#endif

				break;

			case BP_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered BP state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif

				// Activate BP process
				HEPSY_S(CORE_id) CORE_2_BP_4_start->write(puls);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) BP process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=BP_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) BP process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				#ifdef DEBUG_OUT
					I3[i3++]=sc_time_stamp()-prev_S;
				#endif

				break;

			case CSW_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered CSW state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif
  
				// Activate CSW process
				HEPSY_S(CORE_id) CORE_2_CSW_4_start->write(puls);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) CSW process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=CSW_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) CSW process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				// If not needed by AVIrp (i.e., since we are going from CSW to AVIr, stop CORE_timer_mng)
				HEPSY_S(CORE_id)
				if (next_state==AVIr_state)
				{
					HEPSY_S(CORE_id)
					if (CORE_timer_mng_2_CORE_4_fired->read_test()==false) // If the timer is still running...
					{
						HEPSY_S(CORE_id) CORE_2_CORE_counter_4_stop->write(true); // Stop it!

						// Debug
						#ifdef DEBUG_CORE
						cout << "(CORE) CORE/AVIrp timer stopped at " << sc_time_stamp() << endl;
						system("pause"); cout << endl;
						#endif
					}
					#ifdef DEBUG_DFM
					else // If the timer has already fired (i.e., something is not going on the right way...)
					{
						/*HEPSY_S(CORE_id)*/ // In debug mode time is not considered
						CORE_timer_mng_2_CORE_4_fired->read(); // Ublock it

						//// Debug
						//#ifdef DEBUG_CORE
						cout << "(DFM) CORE: WARNING!!! CORE/AVIrp timer unexpectedly fired at " << sc_time_stamp() << endl;
						#ifdef PAUSE
							system("pause"); cout << endl;
						#endif
						//#endif
					}
					#endif
				}

				#ifdef DEBUG_OUT
					I4[i4++]=sc_time_stamp()-prev_S;
				#endif

				break;

			case AVIr_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered AVIr state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif

				// Activate AVIr process
				HEPSY_S(CORE_id) CORE_2_AVIr_4_start->write(puls);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AVIr process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=AVIr_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AVIr process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				#ifdef DEBUG_OUT
					I5[i5++]=sc_time_stamp()-prev_S;
				#endif

				break;

			case AVIrp_state:

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Entered AVIrp state at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				#if defined DEBUG_VAL || defined DEBUG_OUT
					prev_S = sc_time_stamp();
				#endif

				// Activate AVIrp process
				HEPSY_S(CORE_id) CORE_2_AVIrp_4_start->write(true);  //Note tha puls is NOT sent

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AVIrp process started at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for fired form CORE/AVIrp timer
				HEPSY_S(CORE_id) CORE_timer_mng_2_CORE_4_fired->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) CORE/AVIrp timer fired at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Forward the fired to AVIrp
				HEPSY_S(CORE_id) CORE_2_AVIrp_4_fired->write(true);

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) Forwarded CORE/AVIrp fired from CORE to AVIrp at " << sc_time_stamp() << endl;
				system("pause"); cout << endl;
				#endif

				// Wait for the end and update state
				HEPSY_S(CORE_id) next_state=AVIrp_2_CORE_4_end->read();

				// Debug
				#ifdef DEBUG_CORE
				cout << "(CORE) AVIrp process ended at " << sc_time_stamp() << " - Next state is: " << next_state << endl;
				system("pause"); cout << endl;
				#endif

				#ifdef DEBUG_OUT
					I6[i6++]=sc_time_stamp()-prev_S;
				#endif

				break;

			default:

				// Debug
				#ifdef DEBUG_DFM
				cout << "(DFM) CORE: ERROR!!! Unknown state!" << endl;
				system("pause"); cout << endl;
				#endif
				exit(10);
		}

		#ifdef DEBUG_VAL
			cout << "(VAL) From " << current_state << " to " << next_state << " in " << sc_time_stamp()-prev_S << endl << endl;
		#endif

		// Update state
		HEPSY_S(CORE_id)
		if (current_state!=next_state) current_state=next_state;

		// Profiling
		HEPSY_P(CORE_id);
	}
}

////////////////////////////////////////////////////////

//CORE_timer_mng
void mainsystem::CORE_timer_mng()
{
	// Local timer parameters
	timer_parameters timer;
	bool fired;

	HEPSY_S(CORE_timer_mng_id) 
	while(true)
	{HEPSY_S(CORE_timer_mng_id) 

		// Set local timer parameters with CORE_timer_mng ones
		HEPSY_S(CORE_timer_mng_id) timer=CORE_2_CORE_timer_mng_4_start->read();

		// Start counter
		HEPSY_S(CORE_timer_mng_id) CORE_timer_mng_2_CORE_counter_4_start->write(timer);

		// Wait for the counter
		HEPSY_S(CORE_timer_mng_id) fired=CORE_counter_2_CORE_timer_mng_4_end->read();

		// Check timeout
		HEPSY_S(CORE_timer_mng_id) 
		if (fired) CORE_timer_mng_2_CORE_4_fired->write(true); // Fire!

		// Profiling
		HEPSY_P(CORE_timer_mng_id);
	}
}

//CORE_counter
void mainsystem::CORE_counter()
{
	// Local timer parameters
	timer_parameters timer;
	sc_time t; // Temp

	HEPSY_S(CORE_counter_id) 
	while(true)
	{HEPSY_S(CORE_counter_id) 

		// Set counter
		HEPSY_S(CORE_counter_id) timer=CORE_timer_mng_2_CORE_counter_4_start->read();

		// Decrease the counter until 0 or stopped
		HEPSY_S(CORE_counter_id) 
		for(t=timer.timeout; (t>sc_time(0, SC_MS)) && (!CORE_2_CORE_counter_4_stop->read_test()); t=t-timer.granularity)
		{HEPSY_S(CORE_counter_id) 

			HEPSY_S_TIMER(CORE_counter_id,timer.granularity)
		}

		// If stopped, unblock  CORE_2_CORE_counter_4_stop pending and exit with false
		HEPSY_S(CORE_counter_id)
		if (CORE_2_CORE_counter_4_stop->read_test())
		{
			HEPSY_S(CORE_counter_id)
			CORE_2_CORE_counter_4_stop->read();

			HEPSY_S(CORE_counter_id)
			CORE_counter_2_CORE_timer_mng_4_end->write(false);
		}
		else //fired
		{
			HEPSY_S(CORE_counter_id)
			CORE_counter_2_CORE_timer_mng_4_end->write(true); // Fire!
		}

		// Profiling
		HEPSY_P(CORE_counter_id);
	}
}

////////////////////////////////////////////////////////
