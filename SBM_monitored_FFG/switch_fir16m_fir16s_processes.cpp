#include "mainsystem.h"

// Switch process to count messages exchanged between fir16m and fir16s processes (it automatically counts also messages on involved channels)

void mainsystem::switch_fir16m_fir16s_processes()
{
	fir16s_parameters fir16s_p;
	fir16s_results fir16s_r;
	unsigned int fir16s_parameters_channel_counter = 0; //Counter for messages on fir8e_parameters_channel
	unsigned int fir16s_results_channel_counter = 0; //Counter for messages on fir8e_results_channel
	unsigned int fir16m_fir16s_counter = 0; //Counter for messages between fir8m and fir8e processes (and viceversa)

	// Register ALT
	HEPSY_S(s_fir16m_fir16s_id) fir16s_parameters_channel_1->register_alt(); //original channel splitted in 1 and 2
	HEPSY_S(s_fir16m_fir16s_id) fir16s_results_channel_1->register_alt(); //original channel splitted in 1 and 2

	HEPSY_S(s_fir16m_fir16s_id)
	while (true)
	{HEPSY_S(s_fir16m_fir16s_id)

		// If at least one of the channels 1 is ready...
		HEPSY_S(s_fir16m_fir16s_id)
		if ((fir16s_parameters_channel_1->read_test()) || (fir16s_results_channel_1->read_test()))
		{
			// If fir8e_parameters_channel_1 is ready...
			if (fir16s_parameters_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_parameters_channel_1->read(fir16s_p); //Read from fir8m (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_parameters_channel_counter++; //Increments counter
				HEPSY_S(s_fir16m_fir16s_id)
				fir16m_fir16s_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_parameters_channel_2->write(fir16s_p); //Write to fir8e
				HEPSY_S(s_fir16m_fir16s_id)
				HEPSY_S(s_fir16m_fir16s_id)
			}

			// If fir8e_results_channel_1 is ready...
			if (fir16s_results_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_results_channel_1->read(fir16s_r); //Read from fir8e (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_results_channel_counter++; //Increments counter
				HEPSY_S(s_fir16m_fir16s_id)
				fir16m_fir16s_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir16m_fir16s_id)
				fir16s_results_channel_2->write(fir16s_r); //Write to fir8m
				HEPSY_S(s_fir16m_fir16s_id)
				HEPSY_S(s_fir16m_fir16s_id)
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(s_fir16m_fir16s_id) 
			wait(fir16s_parameters_channel_1->get_alt_event() | fir16s_results_channel_1->get_alt_event());
			POST_WAIT(s_fir16m_fir16s_id) 
		}

	HEPSY_P(s_fir16m_fir16s_id)  
	}
}




