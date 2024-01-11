#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <systemc.h>

////////////////////////////

// DATATYPES (i.e., MESSAGES) USED BY THE CHANNELS

////////////////////////////

//FIR16

// From fir16m to fir16e
struct fir16e_parameters
{
	sc_uint<19> acc;
	sc_uint<9> coef[16];
	sc_uint<8> shift[16];
	sc_uint<8> sample_tmp;
};

// From fir16e to fir16m
struct fir16e_results
{
	sc_uint<19> acc;
};

// From fir16m to fir16s
struct fir16s_parameters
{
	sc_uint<8> shift[16];
	sc_uint<8> sample_tmp;
};

// From fir16s to fir16m
struct fir16s_results
{
sc_uint<8> shift[16];
};

////////////////////////////

//FIR8

// From fir8m to fir8e
struct fir8e_parameters
{
	sc_uint<19> acc;
	sc_uint<9> coef[8];
	sc_uint<8> shift[8];
	sc_uint<8> sample_tmp;
};

// From fir8e to fir8m
struct fir8e_results
{
	sc_uint<19> acc;
};

// From fir8m to fir8s
struct fir8s_parameters
{
	sc_uint<8> shift[8];
	sc_uint<8> sample_tmp;
};

// From fir8s to fir8m
struct fir8s_results
{
	sc_uint<8> shift[8];
};

////////////////////////////

//GCD

// From gcdm to gcde
struct gcde_parameters
{
	sc_uint<8> sample1;
	sc_uint<8> sample2;
};

// From gcde to gcdm
struct gcde_results
{
	sc_uint<8> result;
};

//////////////////////////////

#endif
