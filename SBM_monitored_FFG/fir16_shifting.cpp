#include "mainsystem.h"

//f16s
void mainsystem::fir16_shifting()
{
	// datatype for channels
	fir16s_parameters fir16s_p;
	fir16s_results fir16s_r;

	// local variables
	sc_uint<8> sample_tmp;
	sc_uint<8> shift[16];

	HEPSY_S(fir16s_id) while(1)
	{HEPSY_S(fir16s_id)

		// read parameters from channel
		HEPSY_S(fir16s_id) fir16s_p=fir16s_parameters_channel_2->read();

		// fill local variables
		HEPSY_S(fir16s_id) sample_tmp=fir16s_p.sample_tmp;
		HEPSY_S(fir16s_id) for( unsigned j=0; j<TAP16; j++) shift[j]=fir16s_p.shift[j];

		// process

		HEPSY_S(fir16s_id) for(int i=TAP16-2; i>=0; i--)
		{HEPSY_S(fir16s_id)
			HEPSY_S(fir16s_id) shift[i+1] = shift[i];
		HEPSY_S(fir16s_id)}

		HEPSY_S(fir16s_id) shift[0]=sample_tmp;

		// fill datatype
		HEPSY_S(fir16s_id) for( unsigned j=0; j<TAP16; j++) fir16s_p.shift[j]=shift[j];

		// send results by channel
		HEPSY_S(fir16s_id) fir16s_results_channel_1->write(fir16s_r);

		HEPSY_P(fir16s_id)
	}
}
/*****************************************************************************/




