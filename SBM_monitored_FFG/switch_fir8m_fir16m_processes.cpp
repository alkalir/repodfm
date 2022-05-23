#include "mainsystem.h"

// Switch process to count messages exchanged between fir8m and fir8e processes (it automatically counts also messages on involved channels)

void mainsystem::switch_fir8m_fir16m_processes()
{
	// local variables
	sc_uint<8> sample1;
	sc_uint<8> sample2;

	unsigned int result8_channel_counter = 0; //Counter for messages on fir8e_parameters_channel
	unsigned int result16_channel_counter = 0; //Counter for messages on fir8e_results_channel
	unsigned int fir8m_fir16m_counter = 0; //Counter for messages between fir8m and fir8e processes (and viceversa)

	// Register ALT
	HEPSY_S(s_fir8m_fir16m_id) result8_channel_1->register_alt(); //original channel splitted in 1 and 2
	HEPSY_S(s_fir8m_fir16m_id) result16_channel_1->register_alt(); //original channel splitted in 1 and 2

	HEPSY_S(s_fir8m_fir16m_id)
	while (true)
	{HEPSY_S(s_fir8m_fir16m_id)

		// If at least one of the channels 1 is ready...
		HEPSY_S(s_fir8m_fir16m_id)
		if ((result8_channel_1->read_test()) && (result16_channel_1->read_test()))
		{
			// If result8_channel_1 is ready...
			if (result8_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir16m_id)
				sample1=result8_channel_1->read(); //Read from fir8m (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir16m_id)
				result8_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir16m_id)
				fir8m_fir16m_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir16m_id)
				result8_channel_2->write(sample1); //Write to fir8e
				HEPSY_S(s_fir8m_fir16m_id)
				HEPSY_S(s_fir8m_fir16m_id)
			}

			// If result16_channel_1 is ready...
			if (result16_channel_1->read_test())
			{
				//Read
				HEPSY_S(s_fir8m_fir16m_id)
				sample2=result16_channel_1->read(); //Read from fir8e (original channel splitted in 1 and 2)

				//Update counters
				HEPSY_S(s_fir8m_fir16m_id)
				result16_channel_counter++; //Increments counter
				HEPSY_S(s_fir8m_fir16m_id)
				fir8m_fir16m_counter++; //Increments counter

				//Write
				HEPSY_S(s_fir8m_fir16m_id)
				result16_channel_2->write(sample2); //Write to fir8m
				HEPSY_S(s_fir8m_fir16m_id)
				HEPSY_S(s_fir8m_fir16m_id)
			}
		}
		// Else wait for a channel...
		else
		{
			PRE_WAIT(s_fir8m_fir16m_id) 
			wait(result8_channel_1->get_alt_event() | result16_channel_1->get_alt_event());
			POST_WAIT(s_fir8m_fir16m_id)
		}

	HEPSY_P(s_fir8m_fir16m_id) 
	}
}




