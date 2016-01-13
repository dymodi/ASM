%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

clc;clear;

Ts = 0.05;         % Sampling time
Nsim = 30;         % Simulation length

Q = 10;
R = 0.1;
testSizeIO = 6;
testSizeMP = 6;

dataMaxIterPrimASM = zeros(testSizeIO,testSizeMP);  % Max Iter of origin ASM
dataMaxIterPrimASM_CS = zeros(testSizeIO,testSizeMP);  % Max Iter of ASM with constraints seletion
dataAvgIterPrimASM = zeros(testSizeIO,testSizeMP);  % Average Iter of origin ASM
dataAvgIterPrimASM_CS = zeros(testSizeIO,testSizeMP);  % Average Iter of ASM with constraints seletion
dataMaxIterDualASM = zeros(testSizeIO,testSizeMP);  % Max Iter of origin ASM
dataMaxIterDualASM_CS = zeros(testSizeIO,testSizeMP);  % Max Iter of ASM with constraints seletion
dataAvgIterDualASM = zeros(testSizeIO,testSizeMP);  % Average Iter of origin ASM
dataAvgIterDualASM_CS = zeros(testSizeIO,testSizeMP);  % Average Iter of ASM with constraints seletion
dataUcTimes = zeros(testSizeIO,testSizeMP);     % Unconstrained problems
dataTightTimes = zeros(testSizeIO,testSizeMP);  % Unsolvable problems
dataSolveTimes = zeros(testSizeIO,testSizeMP);  % Actual solve times
dataFailTimesPrimASM = zeros(testSizeIO,testSizeMP);% Fails of origin ASM
dataFailTimesPrimASM_CS = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection
dataFailTimesDualASM = zeros(testSizeIO,testSizeMP);% Fails of origin ASM
dataFailTimesDualASM_CS = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection

for i = 1:testSizeIO
    nu = i+1;     % Number of inputs variables
    ny = i+1;     % Number of outputs variables
    nx = nu*2;    % Number of states varaibles    
    for j = 1:testSizeMP
        P = j*10+10;
        M = j+5;        
        [maxIterPrimASM,avgIterPrimASM,maxIterPrimASM_CS,avgIterPrimASM_CS,...
    maxIterDualASM,avgIterDualASM,maxIterDualASM_CS,avgIterDualASM_CS,...
    ucTimes,tightTimes,failTimesPrimASM,failTimesPrimASM_CS,...
    failTimesDualASM,failTimesDualASM_CS] = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R);               
        dataUcTimes(i,j) = ucTimes;
        dataTightTimes(i,j) = tightTimes;
        dataSolveTimes(i,j) = Nsim - ucTimes - tightTimes;
        if dataSolveTimes(i,j) == 0
            continue;
        end
        dataMaxIterPrimASM(i,j) = maxIterPrimASM;
        dataMaxIterPrimASM_CS(i,j) = maxIterPrimASM_CS;
        dataAvgIterPrimASM(i,j) = avgIterPrimASM;
        dataAvgIterPrimASM_CS(i,j) = avgIterPrimASM_CS;
        dataMaxIterDualASM(i,j) = maxIterDualASM;
        dataMaxIterDualASM_CS(i,j) = maxIterDualASM_CS;
        dataAvgIterDualASM(i,j) = avgIterDualASM;
        dataAvgIterDualASM_CS(i,j) = avgIterDualASM_CS;
        dataFailTimesPrimASM(i,j) = failTimesPrimASM;
        dataFailTimesPrimASM_CS(i,j) = failTimesPrimASM_CS;
        dataFailTimesDualASM(i,j) = failTimesDualASM;
        dataFailTimesDualASM_CS(i,j) = failTimesDualASM_CS;
    end
end

