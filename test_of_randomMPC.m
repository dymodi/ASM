%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

Ts = 0.05;         % Sampling time
Nsim = 30;         % Simulation length

Q = 10;
R = 0.1;
testSizeIO = 5;
testSizeMP = 5;

dataMaxIterASM = zeros(testSizeIO,testSizeMP);  % Max Iter of origin ASM
dataMaxIterNew = zeros(testSizeIO,testSizeMP);  % Max Iter of ASM with constraints seletion
dataAvgIterASM = zeros(testSizeIO,testSizeMP);  % Average Iter of origin ASM
dataAvgIterNew = zeros(testSizeIO,testSizeMP);  % Average Iter of ASM with constraints seletion
dataUcTimes = zeros(testSizeIO,testSizeMP);     % Unconstrained problems
dataTightTimes = zeros(testSizeIO,testSizeMP);  % Unsolvable problems
dataSolveTimes = zeros(testSizeIO,testSizeMP);  % Actual solve times
dataFailTimesASM = zeros(testSizeIO,testSizeMP);% Fails of origin ASM
dataFailTimesNew = zeros(testSizeIO,testSizeMP);% Fails of ASM with constraints selection

for i = 1:testSizeIO
    nu = i+1;     % Number of inputs variables
    ny = i+1;     % Number of outputs variables
    nx = nu*2;    % Number of states varaibles    
    for j = 1:testSizeMP
        P = j*10+10;
        M = j+3;        
        [maxIterASM,avgIterASM,maxIterNew,avgIterNew,ucTimes,tightTimes,...
          failTimesASM,failTimesNew] = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R);                
        dataUcTimes(i,j) = ucTimes;
        dataTightTimes(i,j) = tightTimes;
        dataSolveTimes(i,j) = Nsim - ucTimes - tightTimes;
        if dataSolveTimes(i,j) == 0
            continue;
        end
        dataMaxIterASM(i,j) = maxIterASM;
        dataMaxIterNew(i,j) = maxIterNew;
        dataAvgIterASM(i,j) = avgIterASM;
        dataAvgIterNew(i,j) = avgIterNew;                
        dataFailTimesASM(i,j) = failTimesASM;
        dataFailTimesNew(i,j) = failTimesNew;                
    end        
end

