#include <systemc.h>
#include "sc_csp_channel.h"
#include "define.h"
#include "stim_gen.h"
#include "mainsystem.h"
#include "display.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////

int sc_main(int a, char* b[])
{

	// Channels for the connection between the test bench and the main system

	sc_csp_channel< sc_uint<8> >   stim1_channel(12,stimulus_id,fir8m_id);
    	sc_csp_channel< sc_uint<8> >   stim2_channel(13,stimulus_id,fir16m_id);
	sc_csp_channel< sc_uint<8> >   result_channel(14,gcdm_id,display_id);

	// Instantiation and connection of testbench and system

	stim_gen mystimgen("mystimgen");
	mystimgen.stim1_channel_port(stim1_channel);
	mystimgen.stim2_channel_port(stim2_channel);

	mainsystem mysystem("mysystem");
	mysystem.stim1_channel_port(stim1_channel);
	mysystem.stim2_channel_port(stim2_channel);
	mysystem.result_channel_port(result_channel);

	display mydisplay("mydisplay");
	mydisplay.result_channel_port(result_channel);

	// Start simulation
	sc_start();

	// Simulation end
	cout << "Simulation finished at simulated time: " << sc_time_stamp() << endl;

	#if _WIN32
	    system("pause");
	#endif

	return 0;
}
