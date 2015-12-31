%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

nu = 2;     % Number of inputs variables
ny = 2;     % Number of outputs variables
nx = 4;     % Number of states varaibles

Ts = 0.05;          % Sampling time
Nsim = 100;         % Simulation length
P = 30;             % Prediction horizon
M = 10;             % Control horizon
Q = 10;
R = 0.1;


