%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

clc;clear;

global LP1Failtimes LP1NotFailtimes xDelta;
LP1Failtimes = 0;
LP1NotFailtimes = 0;
xDelta = [];

%% Choose the solver
solverSwitch.QUAD = 1;
solverSwitch.ASM = 1;
solverSwitch.ASM_CS = 0;
solverSwitch.ASM_CS_NEW = 0;
solverSwitch.ASM_WS = 0;
solverSwitch.ASM_WS_CS = 0;
solverSwitch.ASM_DUAL = 0;
solverSwitch.ASM_DUAL_CS = 0;
solverSwitch.WGS = 1;

%% Add the father path into the working directroy
currentDepth = 1; % get the supper path of the current path
currPath = fileparts(mfilename('fullpath')); % get current path
pos_v = strfind(currPath,filesep);
father_p = currPath(1:pos_v(length(pos_v)-currentDepth+1)-1);
% -1: delete the last character '/' or '\'
addpath(father_p);
addpath([father_p,'\wgs']);

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
        output = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R,solverSwitch);               
        dataUcTimes(i,j) = output.ucTimes;
        dataTightTimes(i,j) = output.tightTimes;
        dataSolveTimes(i,j) = Nsim - output.ucTimes - output.tightTimes;
        if dataSolveTimes(i,j) == 0
            continue;
        end
        if solverSwitch.ASM == 1
            dataMaxIterPrimASM(i,j) = output.maxIterPrimASM;
            dataAvgIterPrimASM(i,j) = output.avgIterPrimASM;
            dataFailTimesPrimASM(i,j) = output.failTimesPrimASM;
        end
        if solverSwitch.ASM_CS == 1
            dataMaxIterPrimASM_CS(i,j) = output.maxIterPrimASM_CS;
            dataAvgIterPrimASM_CS(i,j) = output.avgIterPrimASM_CS;
            dataFailTimesPrimASM_CS(i,j) = output.failTimesPrimASM_CS;
        end
        if solverSwitch.ASM_CS_NEW == 1
            dataMaxIterPrimASM_CS_New(i,j) = output.maxIterPrimASM_CS_New;
            dataAvgIterPrimASM_CS_New(i,j) = output.avgIterPrimASM_CS_New;   
            dataFailTimesPrimASM_CS_New(i,j) = output.failTimesPrimASM_CS_New;
        end
        if solverSwitch.ASM_DUAL == 1
            dataMaxIterDualASM(i,j) = output.maxIterDualASM;
            dataAvgIterDualASM(i,j) = output.avgIterDualASM;
            dataFailTimesDualASM(i,j) = output.failTimesDualASM;
        end
        if solverSwitch.ASM_DUAL_CS == 1
            dataMaxIterDualASM_CS(i,j) = output.maxIterDualASM_CS;
            dataAvgIterDualASM_CS(i,j) = output.avgIterDualASM_CS;
            dataFailTimesDualASM_CS(i,j) = output.failTimesDualASM_CS;
        end
        if solverSwitch.ASM_WS == 1
            dataMaxIterPrimASM_WS(i,j) = output.maxIterPrimASM_WS;
            dataAvgIterPrimASM_WS(i,j) = output.avgIterPrimASM_WS;
            dataFailTimesPrimASM_WS(i,j) = output.failTimesPrimASM_WS;
        end
        if solverSwitch.ASM_WS_CS == 1
            dataMaxIterPrimASM_WS_CS_New(i,j) = output.maxIterPrimASM_WS_CS_New;
            dataAvgIterPrimASM_WS_CS_New(i,j) = output.avgIterPrimASM_WS_CS_New;
            dataFailTimesPrimASM_WS_CS_New(i,j) = output.failTimesPrimASM_WS_CS_New;
        end        
    end
end

