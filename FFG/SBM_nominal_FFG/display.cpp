#include "display.h"

////////////////////////////

// DISPLAY: PRINTS TO THE SCREEN DATA FROM THE SYSTEM

////////////////////////////

void display::output()
{

	// Output counter
	int i=1;

	// Temp
	sc_uint<8> tmp1;

	while(1)
	{
		// Read from channel
		tmp1=result_channel_port->read();

		// Write output
		cout << "Display-" << i <<": \t" << tmp1 << " " << "\t at time \t" << sc_time_stamp() << endl;

		// Output counter
		i++;
	}
}
