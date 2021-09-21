#include <systemc.h>
#include "sc_csp_channel.h"
#include "define.h"
#include "stim_gen.h"
#include "mainsystem.h"
#include "display.h"

using namespace std;

// Data used to provide debug info
#ifdef DEBUG_OUT
	sc_time prev_V, prev_A, prev_S, LRL[100], I1[100], I2[100], I3[100], I4[100], I5[100], I6[100];
	unsigned int ilrl, i1, i2, i3, i4, i5, i6;
#endif

/////////////////////////////////////////////////////////////////////////////////////////

int sc_main(int a, char* b[])
{

#ifdef DEBUG_OUT
	prev_V=prev_A=prev_S=sc_time(0, SC_MS);
	ilrl=i1=i2=i3=i4=i5=i6=0;
#endif

	// Channels for the connection between the test bench and the main system

	//// Natural atrial
	sc_csp_channel< bool >   STIMULUS_2_NA_DISPATCHER_4_NA(0,STIMULUS_id,NA_DISPATCHER_id);
	//// Natural ventricular
	sc_csp_channel< bool >   STIMULUS_2_NV_DISPATCHER_4_NV(1,STIMULUS_id,NV_DISPATCHER_id);
	//// Required ppm
	sc_csp_channel< sc_uint<8> >   STIMULUS_2_CORE_4_ref_freq(2,STIMULUS_id,CORE_id);

	//// Stimulated atrial
	sc_csp_channel< bool >   AEIr_2_DISPLAY_4_SA(3,AEIr_id,DISPLAY_id);
	//// Stimulated ventricular
	sc_csp_channel< bool >   SV_COLLECTOR_2_DISPLAY_4_SV(4,SV_COLLECTOR_id,DISPLAY_id);

	// DFM
	sc_csp_channel< bool >   DFM_UTF_2_DISPLAY_4_UTF(57,DFM_UTF_id,DISPLAY_id);
	sc_csp_channel< UNE_info >   DFM_UNE_2_DISPLAY_4_UNE(59,DFM_UNE_id,DISPLAY_id);
	sc_csp_channel< bool >   DFM_USS_2_DISPLAY_4_USS(62,DFM_USS_id,DISPLAY_id);

	// Instantiation and connection of testbench and system

	stim_gen mystimgen("mystimgen");
	mystimgen.NA(STIMULUS_2_NA_DISPATCHER_4_NA); 
	mystimgen.NV(STIMULUS_2_NV_DISPATCHER_4_NV); 
	mystimgen.f(STIMULUS_2_CORE_4_ref_freq); 

	mainsystem mysystem("mysystem");
	mysystem.NA(STIMULUS_2_NA_DISPATCHER_4_NA);
	mysystem.NV(STIMULUS_2_NV_DISPATCHER_4_NV);
	mysystem.f(STIMULUS_2_CORE_4_ref_freq);
	mysystem.SA(AEIr_2_DISPLAY_4_SA);
	mysystem.SV(SV_COLLECTOR_2_DISPLAY_4_SV);
	mysystem.UTF(DFM_UTF_2_DISPLAY_4_UTF);
	mysystem.UNE(DFM_UNE_2_DISPLAY_4_UNE);
	mysystem.USS(DFM_USS_2_DISPLAY_4_USS);

	display mydisplay("mydisplay");
	mydisplay.SA(AEIr_2_DISPLAY_4_SA); 
	mydisplay.SV(SV_COLLECTOR_2_DISPLAY_4_SV); 
	mydisplay.UTF(DFM_UTF_2_DISPLAY_4_UTF);
	mydisplay.UNE(DFM_UNE_2_DISPLAY_4_UNE);
	mydisplay.USS(DFM_USS_2_DISPLAY_4_USS);

	// Start simulation
	//sc_start();
	sc_start( sc_time(1000*20+19, SC_MS) );

	// Simulation end
	cout << "Simulation finished at simulated time: " << sc_time_stamp() << endl;

	#if _WIN32
	    system("pause");
	#endif
	
#ifdef DEBUG_OUT

	sc_time tot_val;
		
	// DeltaV
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<ilrl; index++) tot_val+=LRL[index];
	if (ilrl!=0) cout << endl << "DeltaV: " << tot_val/ilrl << " (" << 60*1000/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "DeltaV: N/A" << endl;

	// PVARP
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i1; index++) tot_val+=I1[index];
	if (i1!=0) cout << endl << "PVARP: " << tot_val/i1 << " (" << 60*400/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "PVARP: N/A" << endl;

	// AEIr
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i2; index++) tot_val+=I2[index];
	if (i2!=0) cout << endl << "AEIr: " << tot_val/i2 << " (" << 60*400/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "AEIr: N/A" << endl;

	// BP
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i3; index++) tot_val+=I3[index];
	if (i3!=0) cout << endl << "BP: " << tot_val/i3 << " (" << 60*25/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "BP: N/A" << endl;

	// CSW
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i4; index++) tot_val+=I4[index];
	if (i4!=0) cout << endl << "CSW: " << tot_val/i4 << " (" << 60*75/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "CSW: N/A" << endl;
	
	// AVIr
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i5; index++) tot_val+=I5[index];
	if (i5!=0) cout << endl << "AVIr: " << tot_val/i5 << " (" << 60*100/mystimgen.ref_bpm << ")" << endl;
	else cout << endl << "AVIr: N/A" << endl;

	// AVIrp
	tot_val=sc_time(0, SC_MS);
	for (unsigned int index=0; index<i6; index++) tot_val+=I6[index];
	if (i6!=0) cout << endl << "AVIrp: " << tot_val/i6 << " (N/A)" << endl;
	else cout << endl << "AVIrp: N/A (N/A)" << endl;

	#if _WIN32
	    system("pause");
	#endif

#endif

	return 0;
}
