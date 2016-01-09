%% Aircraft with Unstable Poles
% This example shows how to control an unstable aircraft with saturating
% actuators.
%
% Reference:
%
% [1] P. Kapasouris, M. Athans and G. Stein, "Design of feedback control 
% systems for unstable plants with saturating actuators", Proc. IFAC Symp. 
% on Nonlinear Control System Design, Pergamon Press, pp.302--307, 1990
%
% [2] A. Bemporad, A. Casavola, and E. Mosca, "Nonlinear control of
% constrained linear systems via predictive reference management", IEEE(R)
% Trans. Automatic Control, vol. AC-42, no. 3, pp. 340-349, 1997.
%
% See also EMPCAIRCRAFT.

% Copyright 1990-2014 The MathWorks, Inc.  
clc;clear;
%% Define Aircraft Model
% The linear open-loop dynamic model is as follows:
A = [-0.0151 -60.5651 0 -32.174;
     -0.0001 -1.3411 0.9929 0;
      0.00018 43.2541 -0.86939 0;
      0      0       1      0];
B = [-2.516 -13.136;
     -0.1689 -0.2514;
     -17.251 -1.5766;
      0        0];
C = [0 1 0 0;
     0 0 0 1];
D = [0 0;
     0 0];
plant = ss(A,B,C,D);
x0 = zeros(4,1);
%%
% The manipulated variables are the elevator and flaperon angles, the
% attack and pitch angles are measured outputs to be regulated. 
%
% The open-loop response of the system is unstable.
%pole(plant)

%% Design MPC Controller
% *MV Constraints* 
%%
% Both manipulated variables are constrained between +/- 25 degrees.  Since
% the plant inputs and outputs are of different orders of magnitude, you
% also use scale factors to faciliate MPC tuning.  Typical choices of scale
% factor are the upper/lower limit or the operating range.
MV = struct('Min',{-25,-25},'Max',{25,25});

%%
% *OV Constraints* 
%%
% Both plant outputs have constraints to limit undershoots at the first
% prediction horizon.  You also specify scale factors for outputs.
OV = struct('Min',{[-0.5;-Inf],[-100;-Inf]},'Max',{[0.5;Inf],[100;Inf]});

%%
% *Weights* 
%%
% The control task is to get zero offset for piecewise-constant references,
% while avoiding instability due to input saturation.  Because both MV and
% OV variables are already scaled in MPC controller, MPC weights are
% dimensionless and applied to the scaled MV and OV values.  In this
% example, you penalize the two outputs equally with the same OV weights.
Weights = struct('MV',[0 0],'MVRate',[0.1 0.1],'OV',[10 10]);

%%
% *Construct MPC controller*
%%
% Create an MPC controller with plant model, sample time and horizons.
Ts = 0.05;          % Sampling time
p = 10;             % Prediction horizon
m = 2;              % Control horizon
mpcobj = mpc(plant,Ts,p,m,Weights,MV,OV);

load problem.mat
