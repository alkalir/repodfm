 
#include "mainsystem.h"

//f8s
void mainsystem::fir8_shifting()
{
	// datatype for channels
	fir8s_parameters fir8s_p;
	fir8s_results fir8s_r;

	// local variables
	sc_uint<8> sample_tmp;
	sc_uint<8> shift[8];

	HEPSY_S(fir8s_id) while(1)
	{HEPSY_S(fir8s_id)
		// read parameters from channel
		HEPSY_S(fir8s_id) fir8s_p=fir8s_parameters_channel->read();

		// fill local variables
		HEPSY_S(fir8s_id) sample_tmp=fir8s_p.sample_tmp;
		HEPSY_S(fir8s_id) for( unsigned j=0; j<TAP8; j++) shift[j]=fir8s_p.shift[j];

		// process

		HEPSY_S(fir8s_id) for(int i=TAP8-2; i>=0; i--)
		{HEPSY_S(fir8s_id)
			HEPSY_S(fir8s_id) shift[i+1] = shift[i];
		HEPSY_S(fir8s_id)}
		HEPSY_S(fir8s_id) shift[0]=sample_tmp;

		// fill datatype
		HEPSY_S(fir8s_id) for( unsigned j=0; j<TAP8; j++) fir8s_p.shift[j]=shift[j];

		// send results by channel
		HEPSY_S(fir8s_id) fir8s_results_channel->write(fir8s_r);

		HEPSY_P(fir8s_id)
	}
}




