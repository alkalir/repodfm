#include "mainsystem.h"

// Switch process to count messages exchanged between fir8m and fir8s processes (it automatically counts also messages on involved channels)

void mainsystem::switch_fir8m_fir8s_processes()
{
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;
	unsigned int fir8s_parameters_channel_counter = 0; //Counter for messages on fir8e_parameters_channel
	unsigned int fir8s_results_channel_counter = 0; //Counter for messages on fir8e_results_channel
	unsigned int fir8m_fir8s_counter = 0; //Counter for messages between fir8m and fir8e processes (and viceversa)

	// Register ALT
	HEPSY_S(s_fir8m_fir8s_id) fir8s_parameters_channel_1->register_alt(); //original channel splitted in 1 and 2
	HEPSY_S(s_fir8m_fir8s_id) fir8s_results_channel_1->register_alt(); //original channel splitted in 1 and 2

	HEPSY_S(s_fir8m_fir8s_id)
	while (true)
	{HEPSY_S(s_fir8m_fir8s_id)

		// If at least one of the channels 1 is ready...
		HEPSY_S(s_fir8m_fir8s_id)
		if ((fir8s_parameters_channel_1->read_test()) || (fir8s_results_channel_1->read_test()))
		{
			// If fir8e_parameters_channel_1 is ready...
			if (fir8s_parameters_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_parameters_channel_1->read(fir8s_p); //Read from fir8m (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_parameters_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir8s_id)
				fir8m_fir8s_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_parameters_channel_2->write(fir8s_p); //Write to fir8e
				HEPSY_S(s_fir8m_fir8s_id)
				HEPSY_S(s_fir8m_fir8s_id)
			}

			// If fir8e_results_channel_1 is ready...
			if (fir8s_results_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_results_channel_1->read(fir8s_r); //Read from fir8s (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_results_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir8s_id)
				fir8m_fir8s_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir8s_id)
				fir8s_results_channel_2->write(fir8s_r); //Write to fir8m
				HEPSY_S(s_fir8m_fir8s_id)
				HEPSY_S(s_fir8m_fir8s_id)
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(s_fir8m_fir8s_id) 
			wait(fir8s_parameters_channel_1->get_alt_event() | fir8s_results_channel_1->get_alt_event());
			POST_WAIT(s_fir8m_fir8s_id) 
		}

	HEPSY_P(s_fir8m_fir8s_id)  
	}
}




