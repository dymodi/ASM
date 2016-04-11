%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

clc;clear;

global LP1Failtimes LP1NotFailtimes xDelta serialPort;
LP1Failtimes = 0;
LP1NotFailtimes = 0;
xDelta = [];

%串口设置：
serialPort=serial('COM4');           %创建串口对象s，串口端号COM
set(serialPort,'BaudRate',115200);   %设定串口s的波特率
set(serialPort,'Timeout',10);        %设定串口s失效时间
fopen(serialPort);                   %打开串口s

%% Choose the solver
solverSwitch.QUAD = 1;
solverSwitch.ASM = 0;
solverSwitch.ASM_CS = 0;
solverSwitch.ASM_CS_NEW = 0;
solverSwitch.ASM_WS = 0;
solverSwitch.ASM_WS_CS = 0;
solverSwitch.ASM_DUAL = 0;
solverSwitch.ASM_DUAL_CS = 0;
solverSwitch.WGS = 0;
solverSwitch.ASM_C = 0;
solverSwitch.DSPASM = 1;
solverSwitch.DSPWGS = 1;


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
testSizeIO = 1;
testSizeMP = 10;
IOlabel = zeros(testSizeIO,1);
MPlabel = zeros(testSizeMP,1);

if solverSwitch.QUAD == 1
    dataMaxTimeQUAD = zeros(testSizeIO,testSizeMP);
    dataAvgTimeQUAD = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM == 1
    dataMaxIterPrimASM = zeros(testSizeIO,testSizeMP);
    dataAvgIterPrimASM = zeros(testSizeIO,testSizeMP);
    dataFailTimesPrimASM = zeros(testSizeIO,testSizeMP);
    dataMaxDiffPrimASM = zeros(testSizeIO,testSizeMP);
    dataAvgDiffPrimASM = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_CS == 1
    dataMaxIterPrimASM_CS = zeros(testSizeIO,testSizeMP);
    dataAvgIterPrimASM_CS = zeros(testSizeIO,testSizeMP);
    dataFailTimesPrimASM_CS = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_CS_NEW == 1
    dataMaxIterPrimASM_CS_New = zeros(testSizeIO,testSizeMP);
    dataAvgIterPrimASM_CS_New = zeros(testSizeIO,testSizeMP);
    dataFailTimesPrimASM_CS_New = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_DUAL == 1
    dataMaxIterDualASM = zeros(testSizeIO,testSizeMP);
    dataAvgIterDualASM = zeros(testSizeIO,testSizeMP);
    dataFailTimesDualASM = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_DUAL_CS == 1
    dataMaxIterDualASM_CS = zeros(testSizeIO,testSizeMP);
    dataAvgIterDualASM_CS = zeros(testSizeIO,testSizeMP);
    dataFailTimesDualASM_CS = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_WS == 1
    dataMaxIterPrimASM_WS = zeros(testSizeIO,testSizeMP);
    dataAvgIterPrimASM_WS = zeros(testSizeIO,testSizeMP);
    dataFailTimesPrimASM_WS = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_WS_CS == 1
    dataMaxIterPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);
    dataAvgIterPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);
    dataFailTimesPrimASM_WS_CS_New = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.WGS == 1
    dataMaxIterWGS = zeros(testSizeIO,testSizeMP);
    dataAvgIterWGS = zeros(testSizeIO,testSizeMP);
    dataMaxTimeWGS = zeros(testSizeIO,testSizeMP);
    dataAvgTimeWGS = zeros(testSizeIO,testSizeMP);
    dataMaxDiffWGS = zeros(testSizeIO,testSizeMP);
    dataAvgDiffWGS = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.ASM_C == 1
    dataMaxIterASM_C = zeros(testSizeIO,testSizeMP);
    dataAvgIterASM_C = zeros(testSizeIO,testSizeMP);
    dataMaxTimeASM_C = zeros(testSizeIO,testSizeMP);
    dataAvgTimeASM_C = zeros(testSizeIO,testSizeMP);
    dataMaxDiffASM_C = zeros(testSizeIO,testSizeMP);
    dataAvgDiffASM_C = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.DSPASM == 1
    dataMaxIterDSPASM = zeros(testSizeIO,testSizeMP);
    dataAvgIterDSPASM = zeros(testSizeIO,testSizeMP);
    dataMaxTimeDSPASM = zeros(testSizeIO,testSizeMP);
    dataAvgTimeDSPASM = zeros(testSizeIO,testSizeMP);
    dataMaxDiffDSPASM = zeros(testSizeIO,testSizeMP);
    dataAvgDiffDSPASM = zeros(testSizeIO,testSizeMP);
end
if solverSwitch.DSPWGS == 1
    dataMaxIterDSPWGS = zeros(testSizeIO,testSizeMP);
    dataAvgIterDSPWGS = zeros(testSizeIO,testSizeMP);
    dataMaxTimeDSPWGS = zeros(testSizeIO,testSizeMP);
    dataAvgTimeDSPWGS = zeros(testSizeIO,testSizeMP);
    dataMaxDiffDSPWGS = zeros(testSizeIO,testSizeMP);
    dataAvgDiffDSPWGS = zeros(testSizeIO,testSizeMP);
end

dataUcTimes = zeros(testSizeIO,testSizeMP);     % Unconstrained problems
dataTightTimes = zeros(testSizeIO,testSizeMP);  % Unsolvable problems
dataSolveTimes = zeros(testSizeIO,testSizeMP);  % Actual solve times

for i = 1:testSizeIO
    %for i = 4:4
    nu = 2;     % Number of inputs variables
    ny = 2;     % Number of outputs variables
    %     nu = i+1;     % Number of inputs variables
    %     ny = i+1;     % Number of outputs variables
    nx = nu*2;    % Number of states varaibles
    IOlabel(i) = nu;
    for j = 1:testSizeMP
        % P = 7;
        % M = 3;
        P = 3*j+2;
        M = j+2;
        MPlabel(j) = M;
        fprintf('i:%d, j:%d \n',i,j)
        output = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R,solverSwitch);
        dataUcTimes(i,j) = output.ucTimes;
        dataTightTimes(i,j) = output.tightTimes;
        dataSolveTimes(i,j) = Nsim - output.ucTimes - output.tightTimes;
        if dataSolveTimes(i,j) == 0
            continue;
        end
        if solverSwitch.QUAD == 1
            dataMaxTimeQUAD(i,j) = output.maxTimeQUAD;
            dataAvgTimeQUAD(i,j) = output.avgTimeQUAD;
        end
        if solverSwitch.ASM == 1
            dataMaxIterPrimASM(i,j) = output.maxIterPrimASM;
            dataAvgIterPrimASM(i,j) = output.avgIterPrimASM;
            dataFailTimesPrimASM(i,j) = output.failTimesPrimASM;
            dataMaxDiffPrimASM(i,j) = output.maxDiffPrimASM;
            dataAvgDiffPrimASM(i,j) = output.avgDiffPrimASM;
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
        if solverSwitch.WGS == 1
            dataMaxIterWGS(i,j) = output.maxIterWGS;
            dataAvgIterWGS(i,j) = output.avgIterWGS;
            dataMaxTimeWGS(i,j) = output.maxTimeWGS;
            dataAvgTimeWGS(i,j) = output.avgTimeWGS;
            dataMaxDiffWGS(i,j) = output.maxDiffWGS;
            dataAvgDiffWGS(i,j) = output.avgDiffWGS;
        end
        if solverSwitch.ASM_C == 1
            dataMaxIterASM_C(i,j) = output.maxIterASM_C;
            dataAvgIterASM_C(i,j) = output.avgIterASM_C;
            dataMaxTimeASM_C(i,j) = output.maxTimeASM_C;
            dataAvgTimeASM_C(i,j) = output.avgTimeASM_C;
            dataMaxDiffASM_C(i,j) = output.maxDiffASM_C;
            dataAvgDiffASM_C(i,j) = output.avgDiffASM_C;
        end
        if solverSwitch.DSPASM == 1
            dataMaxIterDSPASM(i,j) = output.maxIterDSPASM;
            dataAvgIterDSPASM(i,j) = output.avgIterDSPASM;
            dataMaxTimeDSPASM(i,j) = output.maxTimeDSPASM;
            dataAvgTimeDSPASM(i,j) = output.avgTimeDSPASM;
            dataMaxDiffDSPASM(i,j) = output.maxDiffDSPASM;
            dataAvgDiffDSPASM(i,j) = output.avgDiffDSPASM;
        end
        if solverSwitch.DSPWGS == 1
            dataMaxIterDSPWGS(i,j) = output.maxIterDSPWGS;
            dataAvgIterDSPWGS(i,j) = output.avgIterDSPWGS;
            dataMaxTimeDSPWGS(i,j) = output.maxTimeDSPWGS;
            dataAvgTimeDSPWGS(i,j) = output.avgTimeDSPWGS;
            dataMaxDiffDSPWGS(i,j) = output.maxDiffDSPWGS;
            dataAvgDiffDSPWGS(i,j) = output.avgDiffDSPWGS;
        end
    end
end

fclose(serialPort);                   %打开串口s

% Drawing affairs
figure;
[row,col] = size(dataMaxTimeDSPASM);
d1 = dataMaxTimeDSPASM(:); d2 = dataMaxTimeDSPWGS(:);
if row == 1
    semilogy(MPlabel,d1);hold on;semilogy(MPlabel,d2,'o-');
    xlabel('Number of horizon');
elseif col == 1
    semilogy(IOlabel,d1);hold on;semilogy(IOlabel,d2,'o-');
    xlabel('Number of inputs/outputs.');
end
legend('MaxTimeASM','MaxTimeWGS');title('Maximum running time');
figure;
d1 = dataAvgTimeDSPASM(:); d2 = dataAvgTimeDSPWGS(:);
if row == 1
    semilogy(MPlabel,d1);hold on;semilogy(MPlabel,d2,'o-');
    xlabel('Number of horizon');
elseif col == 1
    semilogy(IOlabel,d1);hold on;semilogy(IOlabel,d2,'o-');
    xlabel('Number of inputs/outputs.');
end
legend('AvgTimeASM','AvgTimeWGS');title('Average running time');
