
#include "mainsystem.h"

//f8e
void mainsystem::fir8_evaluation()
{
	// datatype for channels
	fir8e_parameters fir8e_p;
	fir8e_results fir8e_r;

	// local variables
	sc_int<17> pro;
	sc_uint<19> acc;
	sc_uint<9> coef[8];
	sc_uint<8>  sample_tmp;
	sc_uint<8> shift[8];

	HEPSY_S(fir8e_id) while(1)
	{HEPSY_S(fir8e_id)
		// read parameters from channel
		HEPSY_S(fir8e_id) fir8e_p=fir8e_parameters_channel->read();

		// fill local variables
		HEPSY_S(fir8e_id) sample_tmp=fir8e_p.sample_tmp;
		HEPSY_S(fir8e_id) for( unsigned j=0; j<TAP8; j++) coef[j]=fir8e_p.coef[j];
		HEPSY_S(fir8e_id) for( unsigned j=0; j<TAP8; j++) shift[j]=fir8e_p.shift[j];

		// process
		HEPSY_S(fir8e_id) acc=sample_tmp*coef[0];

		HEPSY_S(fir8e_id) for(int i=TAP8-2; i>=0; i--)
		{HEPSY_S(fir8e_id)
			HEPSY_S(fir8e_id) pro=shift[i]*coef[i+1];
			HEPSY_S(fir8e_id) acc += pro;
		HEPSY_S(fir8e_id)}

		// fill datatype
		HEPSY_S(fir8e_id) fir8e_r.acc=acc;

		// send results by channel
		HEPSY_S(fir8e_id) fir8e_results_channel->write(fir8e_r);

		HEPSY_P(fir8e_id)
	}
}



