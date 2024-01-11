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
	// Monitor processes
	void switch_fir8m_fir8e_processes();
	void switch_fir8m_fir8s_processes();
	// Fake processes
	void fir8_evaluation();
	void fir8_shifting();

	// Process
	void fir16_main();
	// Monitor processes
	void switch_fir16m_fir16e_processes();
	void switch_fir16m_fir16s_processes();
	// Fake processes
	void fir16_evaluation();
	void fir16_shifting();

	// Monitor
	void switch_fir8m_fir16m_processes();

	// Process
	void gcd_main();
	// Monitor processes
	void switch_gcdm_gcde_processes();
	// Fake process
	void gcd_evaluation();

	// CHANNELS

	// fir8
	sc_csp_channel< fir8e_parameters > *fir8e_parameters_channel_1;
	sc_csp_channel< fir8e_parameters > *fir8e_parameters_channel_2;

	sc_csp_channel< fir8e_results > *fir8e_results_channel_1;
	sc_csp_channel< fir8e_results > *fir8e_results_channel_2;

	sc_csp_channel< fir8s_parameters > *fir8s_parameters_channel_1;
	sc_csp_channel< fir8s_parameters > *fir8s_parameters_channel_2;

	sc_csp_channel< fir8s_results > *fir8s_results_channel_1;
	sc_csp_channel< fir8s_results > *fir8s_results_channel_2;

	// fir16
	sc_csp_channel< fir16e_parameters > *fir16e_parameters_channel_1;
	sc_csp_channel< fir16e_parameters > *fir16e_parameters_channel_2;

	sc_csp_channel< fir16e_results > *fir16e_results_channel_1;
	sc_csp_channel< fir16e_results > *fir16e_results_channel_2;

	sc_csp_channel< fir16s_parameters > *fir16s_parameters_channel_1;
	sc_csp_channel< fir16s_parameters > *fir16s_parameters_channel_2;

	sc_csp_channel< fir16s_results > *fir16s_results_channel_1;
	sc_csp_channel< fir16s_results > *fir16s_results_channel_2;

	// gcd
	sc_csp_channel< gcde_parameters > *gcde_parameters_channel_1;
	sc_csp_channel< gcde_parameters > *gcde_parameters_channel_2;

	sc_csp_channel< gcde_results > *gcde_results_channel_1;
	sc_csp_channel< gcde_results > *gcde_results_channel_2;

	// Inter-process connections
	sc_csp_channel< sc_uint<8> > *result8_channel_1;
	sc_csp_channel< sc_uint<8> > *result8_channel_2;

	sc_csp_channel< sc_uint<8> >   *result16_channel_1;
	sc_csp_channel< sc_uint<8> >   *result16_channel_2;

	SC_CTOR(mainsystem)
	{
		fir8e_parameters_channel_1= new sc_csp_channel< fir8e_parameters > (0,fir8m_id,s_fir8m_fir8e_id);
		fir8e_parameters_channel_2= new sc_csp_channel< fir8e_parameters > (15,s_fir8m_fir8e_id,fir8e_id);

		fir8e_results_channel_1= new sc_csp_channel< fir8e_results > (1,fir8e_id,s_fir8m_fir8e_id);
		fir8e_results_channel_2= new sc_csp_channel< fir8e_results > (16,s_fir8m_fir8e_id,fir8m_id);

		fir8s_parameters_channel_1= new sc_csp_channel< fir8s_parameters > (2,fir8m_id,s_fir8m_fir8s_id);
		fir8s_parameters_channel_2= new sc_csp_channel< fir8s_parameters > (19,s_fir8m_fir8s_id,fir8s_id);

		fir8s_results_channel_1= new sc_csp_channel< fir8s_results > (3,fir8s_id,s_fir8m_fir8s_id);
		fir8s_results_channel_2= new sc_csp_channel< fir8s_results > (20,s_fir8m_fir8s_id,fir8m_id);

		fir16e_parameters_channel_1= new sc_csp_channel< fir16e_parameters > (4,fir16m_id,s_fir16m_fir16e_id);
		fir16e_parameters_channel_2= new sc_csp_channel< fir16e_parameters > (17,s_fir16m_fir16e_id,fir16e_id);

		fir16e_results_channel_1= new sc_csp_channel< fir16e_results > (5,fir16e_id,s_fir16m_fir16e_id);
		fir16e_results_channel_2= new sc_csp_channel< fir16e_results > (18,s_fir16m_fir16e_id,fir16m_id);

		fir16s_parameters_channel_1= new sc_csp_channel< fir16s_parameters > (6,fir16m_id,s_fir16m_fir16s_id);
		fir16s_parameters_channel_2= new sc_csp_channel< fir16s_parameters > (21,s_fir16m_fir16s_id,fir16s_id);

		fir16s_results_channel_1= new sc_csp_channel< fir16s_results > (7,fir16s_id,s_fir16m_fir16s_id);
		fir16s_results_channel_2= new sc_csp_channel< fir16s_results > (22,s_fir16m_fir16s_id,fir16m_id);

		gcde_parameters_channel_1 = new sc_csp_channel< gcde_parameters > (10,gcdm_id,s_gcdm_gcde_id);
		gcde_parameters_channel_2 = new sc_csp_channel< gcde_parameters > (23,s_gcdm_gcde_id,gcde_id);

		gcde_results_channel_1 = new sc_csp_channel< gcde_results > (11,gcde_id,s_gcdm_gcde_id);
		gcde_results_channel_2 = new sc_csp_channel< gcde_results > (24,s_gcdm_gcde_id,gcdm_id);

		result8_channel_1= new sc_csp_channel< sc_uint<8> > (8,fir8m_id,s_fir8m_fir16m_id);
		result8_channel_2= new sc_csp_channel< sc_uint<8> > (25,s_fir8m_fir16m_id,gcdm_id);

		result16_channel_1= new sc_csp_channel< sc_uint<8> > (9,fir16m_id,s_fir8m_fir16m_id);
		result16_channel_2= new sc_csp_channel< sc_uint<8> > (26,s_fir8m_fir16m_id,gcdm_id);

		SC_THREAD(fir8_main);
		SC_THREAD(switch_fir8m_fir8e_processes);  // Monitor
		SC_THREAD(switch_fir8m_fir8s_processes);  // Monitor
		SC_THREAD(fir8_evaluation);
		SC_THREAD(fir8_shifting);

		SC_THREAD(fir16_main);
		SC_THREAD(switch_fir16m_fir16e_processes); // Monitor
		SC_THREAD(switch_fir16m_fir16s_processes); // Monitor
		SC_THREAD(fir16_evaluation);
		SC_THREAD(fir16_shifting);

		SC_THREAD(switch_fir8m_fir16m_processes); // Monitor

		SC_THREAD(gcd_main);
		SC_THREAD(switch_gcdm_gcde_processes); // Monitor
		SC_THREAD(gcd_evaluation);

	}
};

#endif
