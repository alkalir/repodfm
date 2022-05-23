
#include "mainsystem.h"

//f16e
void mainsystem::fir16_evaluation()
{
	// datatype for channels
	fir16e_parameters fir16e_p;
	fir16e_results fir16e_r;

	// local variables
	sc_int<17> pro;
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8>  sample_tmp;
	sc_uint<8> shift[16];

	HEPSY_S(fir16e_id) while(1)
	{HEPSY_S(fir16e_id)

		// read parameters from channel
		HEPSY_S(fir16e_id) fir16e_p=fir16e_parameters_channel_2->read();

		// fill local variables
		HEPSY_S(fir16e_id) sample_tmp=fir16e_p.sample_tmp;
		HEPSY_S(fir16e_id) for( unsigned j=0; j<TAP16; j++) coef[j]=fir16e_p.coef[j];
		HEPSY_S(fir16e_id) for( unsigned j=0; j<TAP16; j++) shift[j]=fir16e_p.shift[j];

		// process
		HEPSY_S(fir16e_id) acc=sample_tmp*coef[0];

		HEPSY_S(fir16e_id) for(int i=TAP16-2; i>=0; i--)
		{HEPSY_S(fir16e_id)
			HEPSY_S(fir16e_id) pro=shift[i]*coef[i+1];
			HEPSY_S(fir16e_id) acc += pro;
		HEPSY_S(fir16e_id)}

		// fill datatype
		HEPSY_S(fir16e_id) fir16e_r.acc=acc;

		// send results by channel
		HEPSY_S(fir16e_id) fir16e_results_channel_1->write(fir16e_r);

		HEPSY_P(fir16e_id)
	}
}




