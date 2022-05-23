#include "mainsystem.h"

// Switch process to count messages exchanged between gcdm and gcde processes (it automatically counts also messages on involved channels)

void mainsystem::switch_gcdm_gcde_processes()
{
	gcde_parameters gcde_p;
	gcde_results gcde_r;
	unsigned int gcde_parameters_channel_counter = 0; //Counter for messages on gcde_parameters_channel
	unsigned int gcde_results_channel_counter = 0; //Counter for messages on gcde_results_channel
	unsigned int gcdm_gcde_counter = 0; //Counter for messages between fir8m and gcde processes (and viceversa)

	// Register ALT
	HEPSY_S(s_gcdm_gcde_id) gcde_parameters_channel_1->register_alt(); //original channel splitted in 1 and 2
	HEPSY_S(s_gcdm_gcde_id) gcde_results_channel_1->register_alt(); //original channel splitted in 1 and 2

	HEPSY_S(s_gcdm_gcde_id)
	while (true)
	{HEPSY_S(s_gcdm_gcde_id)

		// If at least one of the channels 1 is ready...
		HEPSY_S(s_gcdm_gcde_id)
		if ((gcde_parameters_channel_1->read_test()) || (gcde_results_channel_1->read_test()))
		{
			// If gcde_parameters_channel_1 is ready...
			if (gcde_parameters_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_gcdm_gcde_id)
				gcde_parameters_channel_1->read(gcde_p); //Read from fir8m (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_gcdm_gcde_id)
				gcde_parameters_channel_counter++; //Increments counter
				HEPSY_S(s_gcdm_gcde_id)
				gcdm_gcde_counter++; //Increments counter

				//Write
				HEPSY_S(s_gcdm_gcde_id)
				gcde_parameters_channel_2->write(gcde_p); //Write to gcde
				HEPSY_S(s_gcdm_gcde_id)
				HEPSY_S(s_gcdm_gcde_id)
			}

			// If gcde_results_channel_1 is ready...
			if (gcde_results_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_gcdm_gcde_id)
				gcde_results_channel_1->read(gcde_r); //Read from gcde (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_gcdm_gcde_id)
				gcde_results_channel_counter++; //Increments counter
				HEPSY_S(s_gcdm_gcde_id)
				gcdm_gcde_counter++; //Increments counter

				//Write
				HEPSY_S(s_gcdm_gcde_id)
				gcde_results_channel_2->write(gcde_r); //Write to fir8m
				HEPSY_S(s_gcdm_gcde_id)
				HEPSY_S(s_gcdm_gcde_id)
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(s_gcdm_gcde_id) 
			wait(gcde_parameters_channel_1->get_alt_event() | gcde_results_channel_1->get_alt_event());
			POST_WAIT(s_gcdm_gcde_id) 
		}

	HEPSY_P(s_gcdm_gcde_id) 
	}
}




