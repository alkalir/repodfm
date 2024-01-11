#include "mainsystem.h"

//gcdm
void mainsystem::gcd_main()
{

	// datatype for channels
	gcde_parameters gcde_p;
	gcde_results gcde_r;

	// local variables
	sc_uint<8> sample1;
	sc_uint<8> sample2;
	sc_uint<8> result;
	bool err;

	// init
	HEPSY_S(gcdm_id) err=false;

	HEPSY_S(gcdm_id) while(1)
	{HEPSY_S(gcdm_id)

		// main functionality

		// Main input from channel

		HEPSY_S(gcdm_id) sample1=result8_channel->read();
		HEPSY_S(gcdm_id) if (sample1==0) err=true;

		HEPSY_S(gcdm_id) sample2=result16_channel->read();
		HEPSY_S(gcdm_id) if (sample2==0) err=true;

		//cout<<"sample1: "<<sample1_tmp<<" sample2: "<<sample2_tmp<<endl;

		HEPSY_S(gcdm_id) if (err==false)
		{HEPSY_S(gcdm_id)  
			// fill datatype
			HEPSY_S(gcdm_id) gcde_p.sample1=sample1;
			HEPSY_S(gcdm_id) gcde_p.sample2=sample2;

			// send parameters and receive results
			HEPSY_S(gcdm_id) gcde_parameters_channel->write(gcde_p);
			HEPSY_S(gcdm_id) gcde_r=gcde_results_channel->read();

			// fill local variables
			HEPSY_S(gcdm_id) result=gcde_r.result;
		HEPSY_S(gcdm_id)}	
		else
		{HEPSY_S(gcdm_id) 
			HEPSY_S(gcdm_id) result=0;
			HEPSY_S(gcdm_id) err=false;
		HEPSY_S(gcdm_id)}

		HEPSY_S(gcdm_id) result_channel_port->write(result);

		//cout << "GCD: \t\t" << result << "\t at time \t" << sc_time_stamp() << endl;

		HEPSY_P(gcdm_id)
	}
}
