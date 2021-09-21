/*****************************************************************************

  sc_csp_channel.h -- The sc_csp_channel<T> primitive channel class.

 *****************************************************************************/

#ifndef __SC_CSP_CHANNEL_H__
#define __SC_CSP_CHANNEL_H__

#include "sysc/communication/sc_communication_ids.h"
#include "sysc/communication/sc_prim_channel.h"
#include "sysc/kernel/sc_event.h"
#include "sysc/communication/sc_communication_ids.h"
#include "sysc/kernel/sc_simcontext.h"
#include "sysc/tracing/sc_trace.h"
#include <typeinfo>

#include "sc_csp_channel_ifs.h"

using namespace sc_core;

// ----------------------------------------------------------------------------
//  CLASS : sc_csp_channel<T>
//
//  The sc_csp_channel<T> channel class.
// ----------------------------------------------------------------------------

template <class T>
class sc_csp_channel
: public sc_csp_channel_in_if<T>,
  public sc_csp_channel_out_if<T>,
  public sc_prim_channel
{
	public:

		// constructor

		explicit sc_csp_channel(
				unsigned int channel_id=0, // ID of the channel
				unsigned int writer_id=0, // ID of the writer process
				unsigned int reader_id=0, // ID of the reader process
				unsigned int w=0 // Number of bits composing the messages used by the channel
				):sc_prim_channel( sc_gen_unique_name( "csp_channel" ) ),
			ready_to_read_event(sc_gen_unique_name( "read_event" )),
			ready_to_write_event(sc_gen_unique_name("write_event" )),
			ready_alt_event(sc_gen_unique_name("alt_event"))
		{
			id=channel_id;
			w_id=writer_id;
			r_id=reader_id;
			width=w;
			init();
		}

		// interface methods
	    virtual void register_port( sc_port_base&, const char* );

		// blocking read
		virtual void read( T& );
		virtual T read();

		// blocking write
		virtual void write( const T& );

		// ALT management
		virtual bool read_test();
		virtual bool write_test();
		virtual void register_alt();
		virtual const sc_event & get_alt_event();

		// other methods

		operator T ()
		{ return read(); }

		sc_csp_channel<T>& operator = ( const T& a )
		{ write( a ); return *this; }

		void trace( sc_trace_file* tf ) const;

		virtual const char* kind() const
		{ return "sc_csp_channel"; }

	protected:

		void init();

		// Events for handshake
		sc_event ready_to_read_event;
		sc_event ready_to_write_event;

		// Event for ALT-support
		sc_event ready_alt_event;

		// Flags for handshake
		bool ready_to_read;
		bool ready_to_write;

		// Flag used by processes to activate ALT-support
		bool enable_alt_events;

		T  csp_buf; // temporary store

	public:

		unsigned int id; // ID of the channel
		unsigned int w_id; // ID of the writer process
		unsigned int r_id; // ID of the reader process
		unsigned int width; // // Number of bits composing the messages used by the channel

	protected:
		sc_port_base* m_reader;	// used for static design rule checking
		sc_port_base* m_writer;	// used for static design rule checking

};

//################ METHODS #############

// register port (used by the SystemC library for static design rule checking)

template <class T>
inline
void
sc_csp_channel<T>::register_port( sc_port_base& port_,
			    const char* if_typename_ )
{
    std::string nm( if_typename_ );
    if( nm == typeid( sc_csp_channel_in_if<T> ).name())
	{
		// only one reader can be connected
		if( m_reader != 0 ) {
			SC_REPORT_ERROR("sc_csp_channel<T> cannot have more than one reader", 0 );
	}
	m_reader = &port_;
    } else if( nm == typeid( sc_csp_channel_out_if<T> ).name()) {
		// only one writer can be connected
		if( m_writer != 0 ) {
			SC_REPORT_ERROR("sc_csp_channel<T> cannot have more than one writer", 0 );
		}
	m_writer = &port_;
    }
    else
    {
        SC_REPORT_ERROR( SC_ID_BIND_IF_TO_PORT_, 
	                 "sc_csp_channel<T> port not recognized" );
    }
}

// blocking read

template <class T>
inline
void
sc_csp_channel<T>::read( T& val_ )
{

	// If the writer is already ready
	if(ready_to_write==true)
	{
		ready_to_read=true;
		ready_to_read_event.notify(SC_ZERO_TIME);
		wait(ready_to_write_event);

		val_=csp_buf;

		ready_to_read=false;
		ready_to_read_event.notify(SC_ZERO_TIME);
	}
	else // If not
	{
		ready_to_read=true;
		if (enable_alt_events) ready_alt_event.notify(SC_ZERO_TIME); // ALT-support
		wait(ready_to_write_event);

		val_=csp_buf;

		ready_to_read=false;
		ready_to_read_event.notify(SC_ZERO_TIME);
		wait(ready_to_write_event);
	}

}

template <class T>
inline
T
sc_csp_channel<T>::read()
{
    T tmp;
    read( tmp );
    return tmp;
}

// blocking write

template <class T>
inline
void
sc_csp_channel<T>::write( const T& val_ )
{

	// If the reader is already ready
	if( ready_to_read==true)
	{
		csp_buf=val_;

		ready_to_write=true;
		ready_to_write_event.notify(SC_ZERO_TIME);
		wait(ready_to_read_event);

		ready_to_write=false;
		ready_to_write_event.notify(SC_ZERO_TIME);
	}
	else // If not
	{
		ready_to_write=true;
		if (enable_alt_events) ready_alt_event.notify(SC_ZERO_TIME); // ALT-support
		wait(ready_to_read_event);

		csp_buf=val_;

		ready_to_write=false;
		ready_to_write_event.notify(SC_ZERO_TIME);
		wait(ready_to_read_event);
	}										

}

template <class T>
inline
void
sc_csp_channel<T>::trace( sc_trace_file* tf ) const
{
	// WIP
}


template <class T>
inline
void
sc_csp_channel<T>::init()
{
    m_reader = 0;
    m_writer = 0;

	ready_to_read=false;
	ready_to_write=false;
	enable_alt_events = false;
}

//// ALT-support MANAGEMENT 

// read_test
template <class T>
inline
bool
sc_csp_channel<T>::read_test()
{
	return ready_to_write;
}

// write_test
template <class T>
inline
bool
sc_csp_channel<T>::write_test()
{
	return ready_to_read;
}

// enable ALT
template <class T>
inline
void
sc_csp_channel<T>::register_alt()
{
	enable_alt_events = true;
}

// get ALT event
template <class T>
inline
const sc_event &
sc_csp_channel<T>::get_alt_event()
{
	return ready_alt_event;
}

#endif
