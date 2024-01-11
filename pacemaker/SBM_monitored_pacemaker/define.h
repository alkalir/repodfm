#ifndef __DEFINE__
#define __DEFINE__

//////////////////////////////
// DEFINES
//////////////////////////////

//// For debug

//// For debug

//#define DEBUG_OUT
//#define PAUSE
//
//#define DEBUG_VAL
//
//#define DEBUG_CORE
//#define DEBUG_DISPATCHER
//#define DEBUG_PVARP
//#define DEBUG_AEIR
//#define DEBUG_BP
//#define DEBUG_CSW
//#define DEBUG_AVIrp
//#define DEBUG_AVIr
//#define DEBUG_COLLECTOR

//// Related to the pacemaker

// Possible pacemaker states
enum pm_state {ND, PVARP_state, AEIr_state, BP_state, CSW_state, AVIr_state, AVIrp_state};
enum chk_state {NONE, ERROR, STATE0, STATE1, STATE2, STATE3, STATE4};

// Operational frequencies (pulse per minute)
#define NORMAL_FREQ 60
#define MAX_FREQ 180
#define MIN_FREQ 40

//// Related to the CSP model

// Processes ID
enum ps_id {STIMULUS_id, DISPLAY_id, CORE_id, PVARP_id, AEIr_id, BP_id, CSW_id, AVIr_id, AVIrp_id,
			  NV_DISPATCHER_id, NA_DISPATCHER_id, SV_COLLECTOR_id,
			  CORE_timer_mng_id, CORE_counter_id,
			  PVARP_timer_mng_id, PVARP_counter_id,
			  AEIr_timer_mng_id,AEIr_counter_id,
			  BP_timer_mng_id, BP_counter_id,
			  CSW_timer_mng_id, CSW_counter_id,
			  AVIr_timer_mng_id,AVIr_counter_id,
			  DFM_UTF_id, DFM_UNE_id, DFM_USS_id};


// Timer granularity
#define DEFAULT_GRANULARITY sc_time(1, SC_MS)

//// Macro to resue the same code also for timing simulation
#define HEPSY_S(X)
#define HEPSY_P(X)
#define PRE_WAIT(X)
#define POST_WAIT(X)
#define HEPSY_S_TIMER(X,Y) wait(Y);

#endif
