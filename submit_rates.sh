#!/bin/bash
# run with $ bsub -q 8nh "sh submit_batch.sh <options>"
# $ bsub -q 8nh "sh submit_rates.sh"
cd /afs/cern.ch/user/t/taylor/CMSSW_8_0_9/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/t/taylor/L1TriggerStudies/

root -q -b -l rates.cxx