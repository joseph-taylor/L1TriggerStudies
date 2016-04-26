# L1TriggerStudies

Main scripts:

jets.cxx
creates l1 vs ref comparison plots and turnOn efficiency curves for jets
can select whether to use l1==hw/emu and ref==pf/gen

eSums.cxx
creates l1 vs ref comparison plots and turnOn efficiency curves for eSums
can select whether to use l1==hw/emu

rates.cxx
calculates rates and distributions for l1 objects
can select either l1=hw, l1=emu, or both
(have to ensure you have the normalisation inputs correct)

output format:
The above scripts create histos.root files. Order comes from the directory structuring...
output_jets/*infoAboutDataYourUsing*/histos.root
output_eSums/*infoAboutDataYourUsing*/histos.root
output_rates/*infoAboutDataYourUsing*/histos.root

makePlots.cxx
this can then be used to make nice pdf's from the histos.root files
saving them in the same directory as the file