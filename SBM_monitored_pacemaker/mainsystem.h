#ifndef __MAINSYSTEM_H__
#define __MAINSYSTEM_H__

#include "sc_csp_channel_ifs.h"
#include "sc_csp_channel.h"
#include "datatype.h"
#include "define.h"

SC_MODULE(mainsystem)
{
	// PORTS for testbench connections
	
	//// From Stimulus
	sc_port< sc_csp_channel_in_if< bool > > NA; // Natural atrtial
	sc_port< sc_csp_channel_in_if< bool > > NV; // NAtural ventricular
	sc_port< sc_csp_channel_in_if< sc_uint<8> > > f; // Required ppm

	//// To display
	sc_port< sc_csp_channel_out_if< bool > > SA; // Stimulated atrial
	sc_port< sc_csp_channel_out_if< bool > > SV; // Stimulated ventricular

	// DFM
	sc_port< sc_csp_channel_out_if< bool > > UTF; // Unexpected timer firing
	sc_port< sc_csp_channel_out_if< UNE_info > > UNE; // Unexpected Natural Event
	sc_port< sc_csp_channel_out_if< bool > > USS; // Unexpected states sequence

	// PROCESSES

	//// Main FSM
	void CORE();
	void CORE_timer_mng();
	void CORE_counter();

	//// Dispatcher and collector
	void NV_DISPATCHER();
	void NA_DISPATCHER();
	void SV_COLLECTOR();

	//// PVARP
	void PVARP();
	void PVARP_timer_mng();
	void PVARP_counter();

	//// AEIr
	void AEIr();
	void AEIr_timer_mng();
	void AEIr_counter();

	//// BP
	void BP();
	void BP_timer_mng();
	void BP_counter();

	//// CSW
	void CSW();
	void CSW_timer_mng();
	void CSW_counter();

	//// AEIr
	void AVIrp();

	//// AVIr
	void AVIr();
	void AVIr_timer_mng();
	void AVIr_counter();

	//// DFM

	// Unexpected CORE/AVIrp timer fired
	void DFM_UTF();
	// Unexpected Natural Event
	void DFM_UNE();
	// Unexpected States Sequence
	void DFM_USS();

	// CHANNELS

	//// Connections between CORE and PVARP processes
	sc_csp_channel< sc_uint<8> > *CORE_2_PVARP_4_start;
	sc_csp_channel< pm_state > *PVARP_2_CORE_4_end;

	//// Connections between CORE and AEIr processes
	sc_csp_channel< sc_uint<8> > *CORE_2_AEIr_4_start;
	sc_csp_channel< pm_state > *AEIr_2_CORE_4_end;

	//// Connections between CORE and BP processes
	sc_csp_channel< sc_uint<8> > *CORE_2_BP_4_start;
	sc_csp_channel< pm_state > *BP_2_CORE_4_end;

	//// Connections between CORE and CSW processes
	sc_csp_channel< sc_uint<8> > *CORE_2_CSW_4_start;
	sc_csp_channel< pm_state > *CSW_2_CORE_4_end;

	//// Connections between CORE and AVIrp processes
	sc_csp_channel< bool > *CORE_2_AVIrp_4_start;
	sc_csp_channel< pm_state > *AVIrp_2_CORE_4_end;
	sc_csp_channel< bool > *CORE_2_AVIrp_4_fired;

	//// Connections between CORE and AVIr processes
	sc_csp_channel< sc_uint<8> > *CORE_2_AVIr_4_start;
	sc_csp_channel< pm_state > *AVIr_2_CORE_4_end;

	// Connections among the dispatcher, the core and the processes that need NV or NA
	sc_csp_channel< pm_state > *CORE_2_NV_DISPATCHER_4_NV;
	sc_csp_channel< pm_state > *CORE_2_NA_DISPATCHER_4_NA;
	sc_csp_channel< bool > *NV_DISPATCHER_2_PVARP_4_NV;
	sc_csp_channel< bool > *NV_DISPATCHER_2_AEIr_4_NV;
	sc_csp_channel< bool > *NV_DISPATCHER_2_CSW_4_NV;
	sc_csp_channel< bool > *NV_DISPATCHER_2_AVIr_4_NV;
	sc_csp_channel< bool > *NA_DISPATCHER_2_AEIr_4_NA;

	// Connections among the collector, the display and the processes that generate SV
	sc_csp_channel< bool > *AVIrp_2_SV_COLLECTOR_4_SV;
	sc_csp_channel< bool > *AVIr_2_SV_COLLECTOR_4_SV;

	//// Connections between CORE process and CORE timer
	sc_csp_channel< timer_parameters > *CORE_2_CORE_timer_mng_4_start;
	sc_csp_channel< bool > *CORE_2_CORE_counter_4_stop;
	sc_csp_channel< bool > *CORE_timer_mng_2_CORE_4_fired;

	//// Connections between CORE timer and CORE counter
	sc_csp_channel< timer_parameters > *CORE_timer_mng_2_CORE_counter_4_start;
	sc_csp_channel< bool > *CORE_counter_2_CORE_timer_mng_4_end;

	//// Connections between PVARP process and PVARP timer
	sc_csp_channel< timer_parameters > *PVARP_2_PVARP_timer_mng_4_start;
	sc_csp_channel< bool > *PVARP_2_PVARP_counter_4_stop;
	sc_csp_channel< bool > *PVARP_timer_mng_2_PVARP_4_fired;

	//// Connections between PVARP timer and PVARP counter
	sc_csp_channel< timer_parameters > *PVARP_timer_mng_2_PVARP_counter_4_start;
	sc_csp_channel< bool > *PVARP_counter_2_PVARP_timer_mng_4_end;

	//// Connections between AEIr process and AEIr timer
	sc_csp_channel< timer_parameters > *AEIr_2_AEIr_timer_mng_4_start;
	sc_csp_channel< bool > *AEIr_2_AEIr_counter_4_stop;
	sc_csp_channel< bool > *AEIr_timer_mng_2_AEIr_4_fired;

	//// Connections between AEIr timer and AEIr counter
	sc_csp_channel< timer_parameters > *AEIr_timer_mng_2_AEIr_counter_4_start;
	sc_csp_channel< bool > *AEIr_counter_2_AEIr_timer_mng_4_end;

	//// Connections between BP process and BP timer
	sc_csp_channel< timer_parameters > *BP_2_BP_timer_mng_4_start;
	sc_csp_channel< bool > *BP_2_BP_counter_4_stop;
	sc_csp_channel< bool > *BP_timer_mng_2_BP_4_fired;

	//// Connections between BP timer and BP counter
	sc_csp_channel< timer_parameters > *BP_timer_mng_2_BP_counter_4_start;
	sc_csp_channel< bool > *BP_counter_2_BP_timer_mng_4_end;

	//// Connections between CSW process and CSW timer
	sc_csp_channel< timer_parameters > *CSW_2_CSW_timer_mng_4_start;
	sc_csp_channel< bool > *CSW_2_CSW_counter_4_stop;
	sc_csp_channel< bool > *CSW_timer_mng_2_CSW_4_fired;

	//// Connections between CSW timer and CSW counter
	sc_csp_channel< timer_parameters > *CSW_timer_mng_2_CSW_counter_4_start;
	sc_csp_channel< bool > *CSW_counter_2_CSW_timer_mng_4_end;

	//// Connections between AVIr process and AVIr timer
	sc_csp_channel< timer_parameters > *AVIr_2_AVIr_timer_mng_4_start;
	sc_csp_channel< bool > *AVIr_2_AVIr_counter_4_stop;
	sc_csp_channel< bool > *AVIr_timer_mng_2_AVIr_4_fired;

	//// Connections between AVIr timer and AVIr counter
	sc_csp_channel< timer_parameters > *AVIr_timer_mng_2_AVIr_counter_4_fired;
	sc_csp_channel< bool > *AVIr_counter_2_AVIr_timer_mng_4_end;

	//// DFM

	// Connections between CORE and DFM_UTF
	sc_csp_channel< bool > *CORE_2_DFM_UTF_4_UTF;

	// Connections between NV_DISPATCHER and DFM_UNE
	sc_csp_channel< UNE_info > *NV_DISPATCHER_2_DFM_UNE_4_UNE;

	// Connections between NA_DISPATCHER and DFM_UNE
	sc_csp_channel< UNE_info > *NA_DISPATCHER_2_DFM_UNE_4_UNE;

	// Connections between CORE and DFM_USS
	sc_csp_channel< pm_state > *CORE_2_DFM_USS_4_USS;

	// Connections between AEIr and DFM_UNE
	sc_csp_channel< UNE_info > *AEIr_2_DFM_UNE_4_UNE;

	// Constructor

	SC_CTOR(mainsystem)
	{
		// Channels instantiation

		//// Connections between CORE and PVARP processes
		CORE_2_PVARP_4_start = new sc_csp_channel< sc_uint<8> >(5,CORE_id,PVARP_id);
		PVARP_2_CORE_4_end = new sc_csp_channel< pm_state > (6,PVARP_id,CORE_id);

		//// Connections between CORE and AEIr processes
		CORE_2_AEIr_4_start = new sc_csp_channel< sc_uint<8> >(7,CORE_id,AEIr_id);
		AEIr_2_CORE_4_end = new sc_csp_channel< pm_state > (8,AEIr_id,CORE_id);

		//// Connections between CORE and BP processes
		CORE_2_BP_4_start = new sc_csp_channel< sc_uint<8> > (9,CORE_id,BP_id);
		BP_2_CORE_4_end = new sc_csp_channel< pm_state > (10,BP_id,CORE_id);

		//// Connections between CORE and CSW processes
		CORE_2_CSW_4_start = new sc_csp_channel< sc_uint<8> > (11,CORE_id,CSW_id);
		CSW_2_CORE_4_end = new sc_csp_channel< pm_state > (12,CSW_id,CORE_id);

		//// Connections between CORE and AVIrp processes
		CORE_2_AVIrp_4_start = new sc_csp_channel< bool > (13,CORE_id,AVIrp_id);
		AVIrp_2_CORE_4_end = new sc_csp_channel< pm_state > (14,AVIrp_id,CORE_id);
		CORE_2_AVIrp_4_fired = new sc_csp_channel< bool > (15,CORE_id,AVIrp_id);

		//// Connections between CORE and AVIr processes
		CORE_2_AVIr_4_start = new sc_csp_channel< sc_uint<8> > (16,CORE_id,AVIr_id);
		AVIr_2_CORE_4_end = new sc_csp_channel< pm_state > (17,AVIr_id,CORE_id);
		
		//// Connections among NV_DISPATCHER, the core and the processes that need NV
		CORE_2_NV_DISPATCHER_4_NV = new sc_csp_channel< pm_state > (18,CORE_id,NV_DISPATCHER_id);
		CORE_2_NA_DISPATCHER_4_NA = new sc_csp_channel< pm_state > (19,CORE_id,NA_DISPATCHER_id);
		NV_DISPATCHER_2_PVARP_4_NV = new sc_csp_channel< bool > (20,NV_DISPATCHER_id,PVARP_id);
		NV_DISPATCHER_2_AEIr_4_NV = new sc_csp_channel< bool > (21,NV_DISPATCHER_id,AEIr_id);
		NV_DISPATCHER_2_CSW_4_NV = new sc_csp_channel< bool > (22,NV_DISPATCHER_id,CSW_id);
		NV_DISPATCHER_2_AVIr_4_NV = new sc_csp_channel< bool > (23,NV_DISPATCHER_id,AVIr_id);

		//// Connections among NV_DISPATCHER, the core and the processes that need NV
		NA_DISPATCHER_2_AEIr_4_NA = new sc_csp_channel< bool > (24,NA_DISPATCHER_id,AEIr_id);

		// Connections among the collector, the display and the processes that generate SV
		AVIrp_2_SV_COLLECTOR_4_SV = new sc_csp_channel< bool > (25, AVIrp_id, SV_COLLECTOR_id);
		AVIr_2_SV_COLLECTOR_4_SV = new sc_csp_channel< bool > (26, AVIr_id, SV_COLLECTOR_id);

		// Connections between CORE process and CORE timer
		CORE_2_CORE_timer_mng_4_start = new sc_csp_channel< timer_parameters >(27,CORE_id,CORE_timer_mng_id);
		CORE_2_CORE_counter_4_stop = new sc_csp_channel< bool >(28,CORE_id,CORE_counter_id);
		CORE_timer_mng_2_CORE_4_fired = new sc_csp_channel< bool > (29,CORE_timer_mng_id,CORE_id);

		//// Connections between CORE timer and CORE counter
		CORE_timer_mng_2_CORE_counter_4_start = new sc_csp_channel< timer_parameters > (30,CORE_timer_mng_id,CORE_counter_id);
		CORE_counter_2_CORE_timer_mng_4_end = new sc_csp_channel< bool > (31,CORE_counter_id,CORE_timer_mng_id);

		// Connections between PVARP process and PVARP timer
		PVARP_2_PVARP_timer_mng_4_start = new sc_csp_channel< timer_parameters >(32,PVARP_id,PVARP_timer_mng_id);
		PVARP_2_PVARP_counter_4_stop = new sc_csp_channel< bool >(33,PVARP_id,PVARP_counter_id);
		PVARP_timer_mng_2_PVARP_4_fired = new sc_csp_channel< bool > (34,PVARP_timer_mng_id,PVARP_id);

		//// Connections between PVARP timer and PVARP counter
		PVARP_timer_mng_2_PVARP_counter_4_start = new sc_csp_channel< timer_parameters > (35,PVARP_timer_mng_id,PVARP_counter_id);
		PVARP_counter_2_PVARP_timer_mng_4_end = new sc_csp_channel< bool > (36,PVARP_counter_id,PVARP_timer_mng_id);

		// Connections between AEIr process and AEIr timer
		AEIr_2_AEIr_timer_mng_4_start = new sc_csp_channel< timer_parameters >(37,AEIr_id,AEIr_timer_mng_id);
		AEIr_2_AEIr_counter_4_stop = new sc_csp_channel< bool >(38,AEIr_id,AEIr_counter_id);
		AEIr_timer_mng_2_AEIr_4_fired = new sc_csp_channel< bool > (39,AEIr_timer_mng_id,AEIr_id);

		//// Connections between AEIr timer and AEIr counter
		AEIr_timer_mng_2_AEIr_counter_4_start = new sc_csp_channel< timer_parameters > (40,AEIr_timer_mng_id,AEIr_counter_id);
		AEIr_counter_2_AEIr_timer_mng_4_end = new sc_csp_channel< bool > (41,AEIr_counter_id,AEIr_timer_mng_id);

		// Connections between BP process and BP timer
		BP_2_BP_timer_mng_4_start = new sc_csp_channel< timer_parameters >(42,BP_id,BP_timer_mng_id);
		BP_2_BP_counter_4_stop = new sc_csp_channel< bool >(43,BP_id,BP_counter_id);
		BP_timer_mng_2_BP_4_fired = new sc_csp_channel< bool > (44,BP_timer_mng_id,BP_id);

		//// Connections between BP timer and BP counter
		BP_timer_mng_2_BP_counter_4_start = new sc_csp_channel< timer_parameters > (45,BP_timer_mng_id,BP_counter_id);
		BP_counter_2_BP_timer_mng_4_end = new sc_csp_channel< bool > (46,BP_counter_id,BP_timer_mng_id);

		// Connections between CSW process and CSW timer
		CSW_2_CSW_timer_mng_4_start = new sc_csp_channel< timer_parameters >(47,CSW_id,CSW_timer_mng_id);
		CSW_2_CSW_counter_4_stop = new sc_csp_channel< bool >(48,CSW_id,CSW_counter_id);
		CSW_timer_mng_2_CSW_4_fired = new sc_csp_channel< bool > (49,CSW_timer_mng_id,CSW_id);

		//// Connections between CSW timer and CSW counter
		CSW_timer_mng_2_CSW_counter_4_start = new sc_csp_channel< timer_parameters > (50,CSW_timer_mng_id,CSW_counter_id);
		CSW_counter_2_CSW_timer_mng_4_end = new sc_csp_channel< bool > (51,CSW_counter_id,CSW_timer_mng_id);

		// Connections between AVIr process and AVIr timer
		AVIr_2_AVIr_timer_mng_4_start = new sc_csp_channel< timer_parameters >(52,AVIr_id,AVIr_timer_mng_id);
		AVIr_2_AVIr_counter_4_stop = new sc_csp_channel< bool >(53,AVIr_id,AVIr_counter_id);
		AVIr_timer_mng_2_AVIr_4_fired = new sc_csp_channel< bool > (54,AVIr_timer_mng_id,AVIr_id);

		//// Connections between AVIr timer and AVIr counter
		AVIr_timer_mng_2_AVIr_counter_4_fired = new sc_csp_channel< timer_parameters > (55,AVIr_timer_mng_id,AVIr_counter_id);
		AVIr_counter_2_AVIr_timer_mng_4_end = new sc_csp_channel< bool > (56,AVIr_counter_id,AVIr_timer_mng_id);

		//// DFM 

		// Connections between CORE and DFM_UTF
		CORE_2_DFM_UTF_4_UTF = new sc_csp_channel< bool > (58,CORE_id,DFM_UTF_id);

		// Connections between NV_DISPATCHER and DFM_UNE
		NV_DISPATCHER_2_DFM_UNE_4_UNE = new sc_csp_channel< UNE_info > (60,NV_DISPATCHER_id,DFM_UNE_id);

		// Connections between NA_DISPATCHER and DFM_UNE
		NA_DISPATCHER_2_DFM_UNE_4_UNE = new sc_csp_channel< UNE_info > (61,NA_DISPATCHER_id,DFM_UNE_id);

		// Connections between CORE and DFM_USS
		CORE_2_DFM_USS_4_USS = new sc_csp_channel< pm_state > (63,CORE_id,DFM_USS_id);

		// Connections between AEIr and DFM_UNE
		AEIr_2_DFM_UNE_4_UNE = new sc_csp_channel< UNE_info > (64,AEIr_id,DFM_UNE_id);

		// Processes registration
		SC_THREAD(CORE);
		SC_THREAD(CORE_timer_mng);
		SC_THREAD(CORE_counter);
		SC_THREAD(NV_DISPATCHER);
		SC_THREAD(NA_DISPATCHER);
		SC_THREAD(SV_COLLECTOR);
		SC_THREAD(PVARP);
		SC_THREAD(PVARP_timer_mng);
		SC_THREAD(PVARP_counter);
		SC_THREAD(AEIr);
		SC_THREAD(AEIr_timer_mng);
		SC_THREAD(AEIr_counter);
		SC_THREAD(BP);
		SC_THREAD(BP_timer_mng);
		SC_THREAD(BP_counter);
		SC_THREAD(CSW);
		SC_THREAD(CSW_timer_mng);
		SC_THREAD(CSW_counter);
		SC_THREAD(AVIrp);
		SC_THREAD(AVIr);
		SC_THREAD(AVIr_timer_mng);
		SC_THREAD(AVIr_counter);
		SC_THREAD(DFM_UTF);
		SC_THREAD(DFM_UNE);
		SC_THREAD(DFM_USS);
	}
};

#endif