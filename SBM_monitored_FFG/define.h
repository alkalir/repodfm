#ifndef __DEFINE__
#define __DEFINE__

//////////////////////////////
// DEFINES
//////////////////////////////

//// Related to the CSP model

// Processes ID
enum p_id {stimulus_id, display_id, fir8m_id, fir8e_id, fir8s_id, fir16m_id, fir16e_id, fir16s_id, gcdm_id, gcde_id, s_fir8m_fir8e_id, s_fir16m_fir16e_id, s_fir8m_fir8s_id, s_fir16m_fir16s_id, s_gcdm_gcde_id, s_fir8m_fir16m_id};

// FirFirGCD: costants
#define TAP8 8
#define TAP16 16

//// Macro to reuse the same code also for timing simulation
#define HEPSY_S(X)
#define HEPSY_P(X)
#define PRE_WAIT(X)
#define POST_WAIT(X)
#define HEPSY_S_TIMER(X,Y) wait(Y);

#endif
