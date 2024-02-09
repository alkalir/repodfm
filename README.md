The repository contains the code associated to the experimental results of the paper (TITLE).

Requirements: Matlab v...

Repository structure:
- FFG contains the experiment related to monitored synthetic application
 - SBM_nominal_FFG: contains the code of the NON monitored Fir-Fir-GCD
 - SBM_monitored_FFG: contains the code of the monitored Fir-Fir-GCD

- Pacemaker contains the experiment related to monitored Pacemaker
 - SBM_nominal_pacemaker: contains the code of the NON monitored pacemaker
 - SBM_monitored_pacemaker: contains the code of the monitored pacemaker

Steps to recreate experiments of FFG:
- download HEPSYCODE from https://www.hepsycode.com/
- open FFG folder
- import the SystemC files contained in the folder SBM_monitored_FFG, representing the FR with the IBMREQ
- run the tool
- the DSE1step results will be obtained (they are also contained in the folder DSE1stStep_output)
- QUI LA PARTE LUIGI...
- open Matlab
- execute the script...

Steps to recreate experiments of Pacemaker:
- download HEPSYCODE from https://www.hepsycode.com/
- open FFG folder
- import the SystemC files contained in the folder SBM_monitored_FFG, representing the FR with the IBMREQ
- run the tool
- the DSE1step results will be obtained (they are also contained in the folder DSE1stStep_output)
- QUI LA PARTE LUIGI...
- open Matlab
- execute the script ...
