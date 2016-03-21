%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

clc;clear;

global LP1Failtimes LP1NotFailtimes xDelta;
LP1Failtimes = 0;
LP1NotFailtimes = 0;
xDelta = [];

%% Add the father path into the working directroy
currentDepth = 1; % get the supper path of the current path
currPath = fileparts(mfilename('fullpath')); % get current path
pos_v = strfind(currPath,filesep);
father_p = currPath(1:pos_v(length(pos_v)-currentDepth+1)-1);
% -1: delete the last character '/' or '\'
addpath(father_p);

Ts = 0.5;         % Sampling time
Nsim = 30;         % Simulation length

Q = 10;
R = 1;
testSizeIO = 5;
testSizeMP = 5;

dataMaxIterPrimASM = zeros(testSizeIO,testSizeMP);  % Max Iter of origin ASM
dataMaxIterPrimASM_CS = zeros(testSizeIO,testSizeMP);  % Max Iter of ASM with constraints seletion
dataMaxIterPrimASM_CS_New = zeros(testSizeIO,testSizeMP);
dataMaxIterPrimASM_WS = zeros(testSizeIO,testSizeMP);
dataMaxIterPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);
dataAvgIterPrimASM = zeros(testSizeIO,testSizeMP);  % Average Iter of origin ASM
dataAvgIterPrimASM_CS = zeros(testSizeIO,testSizeMP);  % Average Iter of ASM with constraints seletion
dataAvgIterPrimASM_CS_New = zeros(testSizeIO,testSizeMP);  
dataAvgIterPrimASM_WS = zeros(testSizeIO,testSizeMP);
dataAvgIterPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);
dataMaxIterDualASM = zeros(testSizeIO,testSizeMP);  % Max Iter of origin ASM
dataMaxIterDualASM_CS = zeros(testSizeIO,testSizeMP);  % Max Iter of ASM with constraints seletion
dataAvgIterDualASM = zeros(testSizeIO,testSizeMP);  % Average Iter of origin ASM
dataAvgIterDualASM_CS = zeros(testSizeIO,testSizeMP);  % Average Iter of ASM with constraints seletion
dataUcTimes = zeros(testSizeIO,testSizeMP);     % Unconstrained problems
dataTightTimes = zeros(testSizeIO,testSizeMP);  % Unsolvable problems
dataSolveTimes = zeros(testSizeIO,testSizeMP);  % Actual solve times
dataFailTimesPrimASM = zeros(testSizeIO,testSizeMP);% Fails of origin ASM
dataFailTimesPrimASM_CS = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection
dataFailTimesPrimASM_CS_New = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection
dataFailTimesPrimASM_WS = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection
dataFailTimesPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection
dataFailTimesDualASM = zeros(testSizeIO,testSizeMP);% Fails of origin ASM
dataFailTimesDualASM_CS = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection

for i = 1:testSizeIO
    nu = i+1;     % Number of inputs variables
    ny = i+1;     % Number of outputs variables
    nx = nu*2;    % Number of states varaibles    
    for j = 1:testSizeMP
        P = j*10;
        M = j+5;
        P = M;
        output = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R);               
        dataUcTimes(i,j) = output.ucTimes;
        dataTightTimes(i,j) = output.tightTimes;
        dataSolveTimes(i,j) = Nsim - output.ucTimes - output.tightTimes;
        if dataSolveTimes(i,j) == 0
            continue;
        end
        dataMaxIterPrimASM(i,j) = output.maxIterPrimASM;
        % dataMaxIterPrimASM_CS(i,j) = output.maxIterPrimASM_CS;
        dataMaxIterPrimASM_CS_New(i,j) = output.maxIterPrimASM_CS_New;
        dataMaxIterPrimASM_WS(i,j) = output.maxIterPrimASM_WS;
        dataMaxIterPrimASM_WS_CS_New(i,j) = output.maxIterPrimASM_WS_CS_New;
        dataAvgIterPrimASM(i,j) = output.avgIterPrimASM;
        % dataAvgIterPrimASM_CS(i,j) = output.avgIterPrimASM_CS;
        dataAvgIterPrimASM_WS(i,j) = output.avgIterPrimASM_WS;
        dataAvgIterPrimASM_CS_New(i,j) = output.avgIterPrimASM_CS_New;        
        dataAvgIterPrimASM_WS_CS_New(i,j) = output.avgIterPrimASM_WS_CS_New;
        % dataMaxIterDualASM(i,j) = output.maxIterDualASM;
        % dataMaxIterDualASM_CS(i,j) = output.maxIterDualASM_CS;
        % dataAvgIterDualASM(i,j) = output.avgIterDualASM;
        % dataAvgIterDualASM_CS(i,j) = output.avgIterDualASM_CS;
        dataFailTimesPrimASM(i,j) = output.failTimesPrimASM;
        dataFailTimesPrimASM_CS(i,j) = output.failTimesPrimASM_CS;
        dataFailTimesPrimASM_CS_New(i,j) = output.failTimesPrimASM_CS_New;
        dataFailTimesPrimASM_WS(i,j) = output.failTimesPrimASM_WS;
        dataFailTimesPrimASM_WS_CS_New(i,j) = output.failTimesPrimASM_WS_CS_New;
        % dataFailTimesDualASM(i,j) = output.failTimesDualASM;
        % dataFailTimesDualASM_CS(i,j) = output.failTimesDualASM_CS;
    end
end

