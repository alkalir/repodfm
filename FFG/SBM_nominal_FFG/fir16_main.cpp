#include "mainsystem.h"

//f16m
void mainsystem::fir16_main()
{
	// datatype for channels
	fir16e_parameters fir16e_p;
	fir16e_results fir16e_r;
	fir16s_parameters fir16s_p;
	fir16s_results fir16s_r;

	// local variables
	sc_uint<8>  sample_tmp;
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8> shift[16];

	// init
	HEPSY_S(fir16m_id) coef[0] = 6;
	HEPSY_S(fir16m_id) coef[1] = 4;
	HEPSY_S(fir16m_id) coef[2] = 13;
	HEPSY_S(fir16m_id) coef[3] = 16;
	HEPSY_S(fir16m_id) coef[4] = 18;
	HEPSY_S(fir16m_id) coef[5] = 41;
	HEPSY_S(fir16m_id) coef[6] = 23;
	HEPSY_S(fir16m_id) coef[7] = 154;
	HEPSY_S(fir16m_id) coef[8] = 222;
	HEPSY_S(fir16m_id) coef[9] = 154;
	HEPSY_S(fir16m_id) coef[10] = 23;
	HEPSY_S(fir16m_id) coef[11] = 41;
	HEPSY_S(fir16m_id) coef[12] = 18;
	HEPSY_S(fir16m_id) coef[13] = 16;
	HEPSY_S(fir16m_id) coef[14] = 13;
	HEPSY_S(fir16m_id) coef[15] = 4;

	HEPSY_S(fir16m_id) for (unsigned int i=0; i<TAP16; i++)
	{HEPSY_S(fir16m_id)
		HEPSY_S(fir16m_id) shift[i] = 0;
	HEPSY_S(fir16m_id)}

	// main functionality

	HEPSY_S(fir16m_id) while(1)
	{HEPSY_S(fir16m_id)
		// Main input from channel
		HEPSY_S(fir16m_id) sample_tmp=stim2_channel_port->read();
		
		//fir16e

		// fill datatype
		HEPSY_S(fir16m_id) fir16e_p.acc=acc;
		HEPSY_S(fir16m_id) for( unsigned j=0; j<TAP16; j++) fir16e_p.coef[j]=coef[j];
		HEPSY_S(fir16m_id) fir16e_p.sample_tmp=sample_tmp;
		HEPSY_S(fir16m_id) for( unsigned j=0; j<TAP16; j++) fir16e_p.shift[j]=shift[j];

		// send parameters and receive results
		HEPSY_S(fir16m_id) fir16e_parameters_channel->write(fir16e_p);
		HEPSY_S(fir16m_id) fir16e_r=fir16e_results_channel->read();

		// fill local variables
		HEPSY_S(fir16m_id) acc=fir16e_r.acc;

		//fir16s

		// fill datatype
		HEPSY_S(fir16m_id) fir16s_p.sample_tmp=sample_tmp;
		HEPSY_S(fir16m_id) for( unsigned j=0; j<TAP16; j++) fir16s_p.shift[j]=shift[j];

		// send parameters and receive results
		HEPSY_S(fir16m_id) fir16s_parameters_channel->write(fir16s_p);
		HEPSY_S(fir16m_id) fir16s_r=fir16s_results_channel->read();

		// fill local variables
		HEPSY_S(fir16m_id) for( unsigned j=0; j<TAP16; j++) shift[j]=fir16s_r.shift[j];
		
		// write output values on channel
		HEPSY_S(fir16m_id) result16_channel->write(acc);
		
		// debug
		// cout << "FIR16: \t\t" << acc << "\t at time \t" << sc_time_stamp() << endl;
		
		HEPSY_P(fir16m_id)
	}
}
