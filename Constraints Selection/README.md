# Constraints Selection

History

2016/1/1 
Constraints Selection (CS) strategy are also included according to Gionata Cimini's idea

2016/1/4 
CS performance unsatisfactory. Dual ASM under construction.

2016/1/7
Dual ASM completed! Dual ASM with CS strategy under construction.

2016/1/10
Dual ASM with CS strategy completed! But the performance is unsatisfactory.

---------------------------------------------------------------------------

Current API

test_of_randomMPC.m   
% Main function entrance

generateMPC.m              
% Generate random MPC and solve QPs

---------------------------------------------------------------------------

asm.m    
% A generic Primal ASM function

asm_cs.m    
% A generic Primal ASM function with constraint selection strategy

addToConsInfo.m    
% Add a constraint to consInfo according to which input/output it belongs and at what time instant

updatePW.m    
% Update high prioritys set and low priority sets according to consInfo (Note that you can choose whether to consider no-successive as higher priority in this function.)

deleteCons.m
% Delete a constraint from high prioritys set or low priority sets and consInfo.

---------------------------------------------------------------------------

asm_dual.m     
% A dual ASM function

asm_dual_cs.m     
% A dual ASM function with constraint selection strategy

updatePW_add_dual.m     
% Update high prioritys set and low priority sets when adding a constraint to working set.

updatePW_del_dual.m     
% Update high prioritys set and low priority sets when deleting a constraint to working set.

