%% Thermo-Mechanical Pulping Process with Multiple Control Objectives
% This example shows how to control a thermo-mechanical pulping (TMP) plant
% with a model predictive controller.

% Copyright 2004-2014 The MathWorks, Inc.

%% Plant Description
% The following diagram shows a typical process arrangement for a two 
% stage TMP operation. Two pressured refiners operate in sequence to
% produce a mechanical pulp suitable for making newsprint.
%
% A primary objective of controlling the TMP plant is to regulate the
% energy applied to the pulp by the electric motors which drive each
% refiner to derive pulp with good physical properties without incurring 
% excess energy costs. 
%
% A secondary control objective is to regulate the ratio of dry mass flow
% rate to overall mass flow rate (known as consistency) measured at the
% outlet of each refiner. 
% 
% In practice these objectives amount to regulating the primary and
% secondary refiner motor loads and the primary and secondary refiner
% constancies subject to the following output constraints: 
%
% (1) Power on each refiner must be less than maximum rated values rated. 
%
% (2) Maintain the vibration level on the two refiners below a critical
% level defined to prevent refiner plate clash.
%
% (3) Limits on measured consistency to prevent blow line plugging and
% fiber damage. 
%
% Manipulated variables comprise:
%
% * set points to the two gap controllers regulating the distance between the refiner plates 
% * the dilution flow rates to the two refiners
% * the rpm of the screw feeder
%
% Physical limits are also imposed on each of these inputs.
%
% <<tmpplant.jpg>>
%
clc;clear;
load mpc_tmpdemodata;
mpctmpinit

%% Modeling of the TMP Plant in Simulink(R)
% To run this example, Simulink(R) is required.
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink(R) is required to run this example.')
    return
end

%%
% The following Simulink(R) model represents a TMP plant and an MPC Controller
% designed for the control objectives described above. The model can be
% opened with:
%open_system('mpc_tmpdemo')

%%
% The MPC controller is represented by an MPC object in the workspace. It 
% can be viewed at the command line as follows:
load mpc_tmpdemodata;
mpcobj


load problem.mat