#include "stim_gen.h"

////////////////////////////

// STIMULUS: GENERATES INPUTS FOR THE SYSTEM

////////////////////////////

// Stimulus for stim1
void stim_gen::stimulus1()
{
	sc_uint<8> value1=1;
	sc_uint<8> value2=1;
	unsigned int i=1;
	sc_time expected(0, SC_MS);

	// Wait for setup
	wait(0.5, SC_MS);
	expected += sc_time(0.5, SC_MS);

	while(i<=10)
	{
		// Sends out value1
		wait(1, SC_MS);
		expected += sc_time(1, SC_MS);
		stim1_channel_port->write(value1);
		cout << "Stimulus1-"<<i<<": \t" << value1 << "\t at time \t" << sc_time_stamp() << " (" << expected << ")" << endl;

		// Change next out values
		value1=value1+value2;
		value2=(value2*value1)+1;

		// Counter
		i++;
	}

}

// Stimulus for stim2
void stim_gen::stimulus2()
{
	sc_uint<8> value1=1;
	sc_uint<8> value2=1;
	unsigned int i=1;
	sc_time expected(0, SC_MS);

	// Wait for setup
	wait(0.5, SC_MS);
	expected += sc_time(0.5, SC_MS);

	while(i<=10)
	{
		// Sends out value2
		wait(1, SC_MS);
		expected += sc_time(1, SC_MS);
		stim2_channel_port->write(value2);
		cout << "Stimulus2-"<<i<<": \t" << value1 << "\t at time \t" << sc_time_stamp() << " (" << expected << ")" << endl;

		// Change next out values
		value1=value1+value2;
		value2=(value2*value1)+1;

		// Counter
		i++;
	}

}

// END
