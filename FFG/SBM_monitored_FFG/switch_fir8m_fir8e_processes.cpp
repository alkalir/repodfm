#include "mainsystem.h"

// Switch process to count messages exchanged between fir8m and fir8e processes (it automatically counts also messages on involved channels)

void mainsystem::switch_fir8m_fir8e_processes()
{
	fir8e_parameters fir8e_p;
	fir8e_results fir8e_r;
	unsigned int fir8e_parameters_channel_counter = 0; //Counter for messages on fir8e_parameters_channel
	unsigned int fir8e_results_channel_counter = 0; //Counter for messages on fir8e_results_channel
	unsigned int fir8m_fir8e_counter = 0; //Counter for messages between fir8m and fir8e processes (and viceversa)

	// Register ALT
	HEPSY_S(s_fir8m_fir8e_id) fir8e_parameters_channel_1->register_alt(); //original channel splitted in 1 and 2
	HEPSY_S(s_fir8m_fir8e_id) fir8e_results_channel_1->register_alt(); //original channel splitted in 1 and 2

	HEPSY_S(s_fir8m_fir8e_id)
	while (true)
	{HEPSY_S(s_fir8m_fir8e_id)

		// If at least one of the channels 1 is ready...
		HEPSY_S(s_fir8m_fir8e_id)
		if ((fir8e_parameters_channel_1->read_test()) || (fir8e_results_channel_1->read_test()))
		{
			// If fir8e_parameters_channel_1 is ready...
			if (fir8e_parameters_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_parameters_channel_1->read(fir8e_p); //Read from fir8m (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_parameters_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir8e_id)
				fir8m_fir8e_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_parameters_channel_2->write(fir8e_p); //Write to fir8e
				HEPSY_S(s_fir8m_fir8e_id)
				HEPSY_S(s_fir8m_fir8e_id)
			}

			// If fir8e_results_channel_1 is ready...
			if (fir8e_results_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_results_channel_1->read(fir8e_r); //Read from fir8e (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_results_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir8e_id)
				fir8m_fir8e_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir8e_id)
				fir8e_results_channel_2->write(fir8e_r); //Write to fir8m
				HEPSY_S(s_fir8m_fir8e_id)
				HEPSY_S(s_fir8m_fir8e_id)
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(s_fir8m_fir8e_id) 
			wait(fir8e_parameters_channel_1->get_alt_event() | fir8e_results_channel_1->get_alt_event());
			POST_WAIT(s_fir8m_fir8e_id) 
		}

	HEPSY_P(s_fir8m_fir8e_id) 
	}
}




