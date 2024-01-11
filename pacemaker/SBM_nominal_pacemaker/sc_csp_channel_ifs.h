/*****************************************************************************

  sc_csp_ifs.h -- The sc_csp_channel<T> interface classes.

 *****************************************************************************/

#ifndef __SC_CSPCHANNEL_IFS_H__
#define __SC_CSPCHANNEL_IFS_H__

#include "sysc/communication/sc_interface.h"

namespace sc_core
{

 // ----------------------------------------------------------------------------
 //  CLASS : sc_csp_channel_in_if<T>
 //
 //  The sc_csp_channel<T> input interface class.
 // ----------------------------------------------------------------------------

 template <class T> 
 class sc_csp_channel_in_if 
 :virtual public sc_interface 
 { 
	public: 

		// blocking read 
		virtual void read( T& ) = 0; 
		virtual T read() = 0; 

		// ALT-support management
		virtual bool read_test() = 0;
		virtual void register_alt() = 0;
		virtual const sc_event & get_alt_event() = 0;

 protected: 

		// constructor 
		sc_csp_channel_in_if() {} 

}; 

 // ----------------------------------------------------------------------------
 //  CLASS : sc_csp_channel_out_if<T>
 //
 //  The sc_csp_channel<T> output interface class.
 // ----------------------------------------------------------------------------

 template <class T> 
 class sc_csp_channel_out_if 
 :virtual public sc_interface 
 { 
	public: 

	    // blocking write 
		virtual void write( const T& ) = 0; 

		// ALT-support management
		virtual bool write_test() = 0;
		virtual void register_alt() = 0;
		virtual const sc_event & get_alt_event() = 0;

	protected: 

	    // constructor 
		sc_csp_channel_out_if(){} 

}; 

} //end of namespace

#endif
