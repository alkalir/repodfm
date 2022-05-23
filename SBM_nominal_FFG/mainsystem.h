#ifndef __MAINSYSTEM_H__
#define __MAINSYSTEM_H__

#include "sc_csp_channel_ifs.h"
#include "sc_csp_channel.h"
#include "datatype.h"
#include "define.h"

SC_MODULE(mainsystem)
{
	// Ports for testbench connections
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > stim1_channel_port;
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > stim2_channel_port;
	sc_port< sc_csp_channel_out_if< sc_uint<8> > > result_channel_port;

	// PROCESSES

	// Process
	void fir8_main();
	// Fake processes
	void fir8_evaluation();
	void fir8_shifting();

	// Process
	void fir16_main();
	// Fake processes
	void fir16_evaluation();
	void fir16_shifting();

	// Process
	void gcd_main();
	// Fake process
	void gcd_evaluation();

	// CHANNELS

	// fir8
	sc_csp_channel< fir8e_parameters > *fir8e_parameters_channel;
	sc_csp_channel< fir8e_results > *fir8e_results_channel;

	sc_csp_channel< fir8s_parameters > *fir8s_parameters_channel;
	sc_csp_channel< fir8s_results > *fir8s_results_channel;

	// fir16
	sc_csp_channel< fir16e_parameters > *fir16e_parameters_channel;
	sc_csp_channel< fir16e_results > *fir16e_results_channel;
	sc_csp_channel< fir16s_parameters > *fir16s_parameters_channel;
	sc_csp_channel< fir16s_results > *fir16s_results_channel;

	// gcd
	sc_csp_channel< gcde_parameters > *gcde_parameters_channel;
	sc_csp_channel< gcde_results > *gcde_results_channel;

	// Inter-process connections
	sc_csp_channel< sc_uint<8> > *result8_channel;
	sc_csp_channel< sc_uint<8> >   *result16_channel;

	SC_CTOR(mainsystem)
	{

		fir8e_parameters_channel= new sc_csp_channel< fir8e_parameters > (0,fir8m_id,fir8e_id);
		fir8e_results_channel= new sc_csp_channel< fir8e_results > (1,fir8e_id,fir8m_id);
		fir8s_parameters_channel= new sc_csp_channel< fir8s_parameters > (2,fir8m_id,fir8s_id);
		fir8s_results_channel= new sc_csp_channel< fir8s_results > (3,fir8s_id,fir8m_id);

		fir16e_parameters_channel= new sc_csp_channel< fir16e_parameters > (4,fir16m_id,fir16e_id);
		fir16e_results_channel= new sc_csp_channel< fir16e_results > (5,fir16e_id,fir16m_id);
		fir16s_parameters_channel= new sc_csp_channel< fir16s_parameters > (6,fir16m_id,fir16s_id);
		fir16s_results_channel= new sc_csp_channel< fir16s_results > (7,fir16s_id,fir16m_id);

		gcde_parameters_channel = new sc_csp_channel< gcde_parameters > (10,gcdm_id,gcde_id);
		gcde_results_channel = new sc_csp_channel< gcde_results > (11,gcde_id,gcdm_id);

		result8_channel= new sc_csp_channel< sc_uint<8> > (8,fir8m_id,gcdm_id);
		result16_channel= new sc_csp_channel< sc_uint<8> > (9,fir16m_id,gcdm_id);

		SC_THREAD(fir8_main);
		SC_THREAD(fir8_evaluation);
		SC_THREAD(fir8_shifting);

		SC_THREAD(fir16_main);
		SC_THREAD(fir16_evaluation);
		SC_THREAD(fir16_shifting);

		SC_THREAD(gcd_main);
		SC_THREAD(gcd_evaluation);

	}

};

#endif
