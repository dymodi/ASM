%% A outer test code to generate radom MPC QP and test with ASM
% 2015.12.28
% Yi

Ts = 0.05;          % Sampling time
Nsim = 30;         % Simulation length

Q = 10;
R = 0.1;
testSizeIO = 5;
testSizeMP = 10;

dataMaxIterASM = zeros(testSizeIO,testSizeMP);
dataMaxIterNew = zeros(testSizeIO,testSizeMP);
dataAvgIterASM = zeros(testSizeIO,testSizeMP);
dataAvgIterNew = zeros(testSizeIO,testSizeMP);
dataUcTimes = zeros(testSizeIO,testSizeMP);
dataTightTimes = zeros(testSizeIO,testSizeMP);
dataFailTimesASM = zeros(testSizeIO,testSizeMP);
dataFailTimesNew = zeros(testSizeIO,testSizeMP);

for i = 1:testSizeIO
    nu = i+1;     % Number of inputs variables
    ny = i+1;     % Number of outputs variables
    nx = nu*2;     % Number of states varaibles    
    for j = 1:testSizeMP
        P = j*10+10;
        M = j+3;        
        [maxIterASM,avgIterASM,maxIterNew,avgIterNew,ucTimes,tightTimes,...
          failTimesASM,failTimesNew] = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R);        
        dataMaxIterASM(i,j) = maxIterASM;
        dataMaxIterNew(i,j) = maxIterNew;
        dataAvgIterASM(i,j) = avgIterASM;
        dataAvgIterNew(i,j) = avgIterNew;
        dataUcTimes(i,j) = ucTimes;
        dataTightTimes(i,j) = tightTimes;
        dataFailTimesASM(i,j) = failTimesASM;
        dataFailTimesNew(i,j) = failTimesNew;                
    end        
end

