This folder contains the SystemC code related to the System Behavioral Model (SBM) as requested by HEPSYCODE (ESL HW/SW Co-Design methodology).

In particular:
- SBM_nominal_FFG: contains the code of the NON monitored Fir-Fir-GCD
- SBM_monitored_FFG: contains the code of the monitored Fir-Fir-GCD
- SBM_nominal_pacemaker: contains the code of the NON monitored pacemaker
- SBM_monitored_pacemaker: contains the code of the monitored pacemaker

The code can be directly used to perform FUNCTIONAL simulations (i.e., the simulations don't take into account the time needed to perform computations and communications) by compiling it in a C++ environment with SystemC library installed).

stim_gen.cpp file can be modified to provide different Reference Inputs.

To perform HW/SW timing co-simulations there is the need to integrate the SBM in HEPSIM, i.e., the HW/SW co-simulation environment associated to HEPSYCODE.
                                   
