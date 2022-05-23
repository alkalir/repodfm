#include "mainsystem.h"

//gcde
void mainsystem::gcd_evaluation()
{
	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8>  sample1;
	sc_uint<8>  sample2;

	HEPSY_S(gcde_id) while(1)
	{HEPSY_S(gcde_id)

		// read parameters from channel
		HEPSY_S(gcde_id) gcde_p=gcde_parameters_channel_2->read();

		// fill local variables
		HEPSY_S(gcde_id) sample1=gcde_p.sample1;
		HEPSY_S(gcde_id) sample2=gcde_p.sample2;

		HEPSY_S(gcde_id) while(sample1!=sample2)
		{HEPSY_S(gcde_id)
			HEPSY_S(gcde_id) if (sample1>sample2)
			{HEPSY_S(gcde_id)
				HEPSY_S(gcde_id) sample1=sample1-sample2;
			HEPSY_S(gcde_id)}
			else
			{HEPSY_S(gcde_id)
				HEPSY_S(gcde_id) sample2= sample2-sample1;
			HEPSY_S(gcde_id)}
		HEPSY_S(gcde_id)}

		// fill datatype
		HEPSY_S(gcde_id) gcde_r.result=sample1;

		// send results to channel
		HEPSY_S(gcde_id) gcde_results_channel_1->write(gcde_r);

		HEPSY_P(gcde_id)
	}
}

/*****************************************************************************/




