%% Simulation of MPC on Masses Problems with different QP solvers
% Masses model comes from paper "An Accelerated Dual Gradient-Projection 
% Algorithm for Embedded Linear Model Predictive Control"
% August 17, 2015

% Note: 注意，引入Gurobi求解器后用原来记录ASM的位置来记录Gurobi的时间

clc;clear;

%% Precision option
precisionFlag = 3;  % 1: single precision, 2: double precision,3 double & single
% if precisionFlag == 1
%     mex -g wgsQPMEX.c
% elseif precisionFlag ==2
%     mex -g wgsQPMEX_double.c
% elseif precisionFlag ==3
%     mex wgsQPMEX.c
%     mex wgsQPMEX_double.c
% else
%     error('Wrong precisionFlag!');
% end

global nu nx
global noc nic

%% Add the father path into the working directroy
currentDepth = 1; % get the supper path of the current path
currPath = fileparts(mfilename('fullpath')); % get current path
pos_v = strfind(currPath,filesep);
father_p = currPath(1:pos_v(length(pos_v)-currentDepth+1)-1);
% -1: delete the last character '/' or '\'
addpath(father_p);
addpath('C:\gurobi605\win64\matlab');

%% Simulation parameter
SimLength = 100;        % Simultion length
NumberOfHorzion = 5;    % Different horizon times
%NumberOfMasses = 5;

%% Recording variables
time_Record = zeros(SimLength,NumberOfHorzion,5);
maxTime_Record = zeros(NumberOfHorzion,5);
diff_wgsC_single_QUADPROG = []; diff_wgsC_double_QUADPROG = [];
diff_wgs_QUADPROG = [];     
diff_gbBarrier_QUADPROG = [];   diff_gbSimplex_QUADPROG = [];
diff_wgsC_wgs = [];         diff_asm_wgs = [];
diff_asm_QUADPROG = [];     diff_QUADPROG_QUADPROG = [];
iter_asm = [];  iter_asm_cs = [];    iter_wgs = [];      
iter_gbBarrier = [];   iter_gbSimplex = []; iter_QUADPROG = []; 
iter_wgsC_single = [];  iter_wgsC_double = [];

%% Simluation
for ii = 5:NumberOfHorzion
    
    %% Problem parameters
    N = 10*ii;  % Horizon length
    M = 5;  % Number of Masses
    k = 1;  % Spring Constant
    c = 0;  % Damping Coefficient
    m = 1;  % Masses
    
    nx = 2*M;   % Number of states
    nu = M-1;   % Number of inputs
        
    %% Constraints
    % c_floor <= C*x <= c_ceil
    % d_floor <= D*u <= d_ceil
    noc = nx; nic = nu;
    C = eye(nx,nx);
    c_ceil = 4;
    c_floor = -4;
    D = eye(nu,nu);
    d_ceil = 1;
    d_floor = -1;
    
    %% Model formulation
    [A,B] = formMDS(M,k,c,m);
    SYSD = c2d(ss(A,B,zeros(1,nx),zeros(1,nu)),0.5);
    Ad = SYSD(1,1).a;
    Bd = zeros(nx,nu);
    for i = 1:nu
        Bd(:,i) = SYSD(1,i).b;
    end
    
    %% Control Parameters
    Q = 1*eye(nx,nx);
    R = 1*eye(nu,nu);
    %[P,~,~] = dare(Ad,Bd,Q,R);
    P = Q;
    [H, F, G, W, E] = QPform(N, R, P, Q, Ad, Bd, C, D, c_ceil, c_floor,...
        d_ceil, d_floor);
    [~, ~, Gs, Ws, Es] = QPform(N, R, P, Q, Ad, Bd, C, [], c_ceil, ...
        c_floor, [], []);
    lx = d_floor*ones(nu*N,1);
    ux = d_ceil*ones(nu*N,1);
    [~,ndec] = size(G);
    [ngc,~] = size(Gs);
    
    %% Initialization
    x_k = rand(nx,1)*2-1;
    %u_k = rand(nu,1)*2-1;
    u_k = 0*rand(nu,1);
    u_k_1_N = [];
    for i = 1:N
        u_k_1_N = [u_k_1_N;u_k];
    end
    
    u_Record = zeros(SimLength,nu);
    x_Record = zeros(SimLength,nx);
      
    %% MPC Iterations
    for kk = 1:SimLength
        
        u_Record(kk,:) = u_k';
        x_Record(kk,:) = x_k';                
        
       %% Solve QP with WGS-ASM Method       
        %Phase I
        % Use the solution of last MPC iteration as a guess of the 
        % initial value
        u_ini = u_k_1_N;    
        if min(G*u_ini-W-E*x_k) < -1e-8
            u_ini = linprog(zeros(ndec,1),-G,-W-E*x_k);
        end
        if min(G*u_ini-W-E*x_k) < -1e-8
            error('Correction failed!')
        end

%         MPCstart = tic;
%         [u_k_N_wgs, iter] = wgsQP(H,F'*x_k,Gs,lx,ux,Ws+Es*x_k,[],[],0,0,u_ini);                           
%         time_Record(kk,ii,2) = toc(MPCstart);
%         if time_Record(kk,2) > maxTime_Record(ii,2);
%             maxTime_Record(ii,2) = time_Record(kk);
%         end                
%         iter_wgs = [iter_wgs;iter];
        
       %% Solve QP with Active-Set Method      
        MPCstart = tic;       
        %[u_k_N_asm_cs, ~, iter_cs, ~] = asm_cs(H,inv(H),F'*x_k,G,W+E*x_k,u_ini,[],400,nx,nu,N);
        [u_k_N_asm, ~, iter, ~] = asm(H,inv(H),F'*x_k,G,W+E*x_k,u_ini,[],400);
        time_Record(kk,ii,1) = toc(MPCstart);
        if time_Record(kk,1) > maxTime_Record(ii,1);
            maxTime_Record(ii,1) = time_Record(kk);
        end
%         diff = max([abs(u_k_N_asm - u_k_N_wgs)]); 
%         diff_asm_wgs  = [diff_asm_wgs;diff];
        iter_asm = [iter_asm;iter];
%         iter_asm_cs = [iter_asm_cs;iter_cs];
        
       %% Solve QP with Matlab built-in QUADPROG
        MPCstart = tic;     
        opts = optimoptions('quadprog','Algorithm','active-set');
        [u_k_N,~,~,output] = quadprog(H,F'*x_k,-Gs,-Ws-Es*x_k,[],[],lx,ux,[],opts);
        iter = output.iterations;
        time_Record(kk,ii,3) = toc(MPCstart);
        if time_Record(kk,3) > maxTime_Record(ii,3);
            maxTime_Record(ii,3) = time_Record(kk);
        end         
        
        diff = max([abs(u_k_N - u_k_N_asm)]); 
        diff_asm_QUADPROG = [diff_asm_QUADPROG;diff];    
        iter_QUADPROG = [iter_QUADPROG;iter];
        
        if (diff > 0.000001)
            %error('wgs gives wrong answer!');
            disp('asm gives wrong answer!');
            pause;
        end

%         % Solve with Gurobi Barrier
%         % clear model para results;
%         model.Q = sparse(0.5 * H);
%         model.obj = F'*x_k;
%         model.A = sparse(Gs);
%         model.rhs = Ws+Es*x_k;
%         model.lb = lx;
%         model.ub = ux;
%         model.sense = '>';
%         para.OutputFlag = 0;
%         para.Method = 2;
%         results = gurobi(model,para);
%         diff = max([abs(u_k_N - results.x)]); 
%         diff_gbBarrier_QUADPROG = [diff_gbBarrier_QUADPROG;diff];  
%         iter_gbBarrier = [iter_gbBarrier;results.baritercount];
%         time_Record(kk,ii,1) = results.runtime;
%         if time_Record(kk,1) > maxTime_Record(ii,1);
%             maxTime_Record(ii,1) = time_Record(kk);
%         end
%         
%         % Solve with Gurobi Simplex
%         % clear model para results;
%         model.Q = sparse(0.5 * H);
%         model.obj = F'*x_k;
%         model.A = sparse(Gs);
%         model.rhs = Ws+Es*x_k;
%         model.lb = lx;
%         model.ub = ux;
%         model.sense = '>';
%         para.OutputFlag = 0;
%         para.Method = 0;
%         results = gurobi(model,para);
%         diff = max([abs(u_k_N - results.x)]); 
%         diff_gbSimplex_QUADPROG = [diff_gbSimplex_QUADPROG;diff];  
%         iter_gbSimplex = [iter_gbSimplex;results.itercount];
%         time_Record(kk,ii,2) = results.runtime;
%         if time_Record(kk,2) > maxTime_Record(ii,2);
%             maxTime_Record(ii,2) = time_Record(kk);
%         end
                        
       %% Solve QP with WGS-ASM Method in C code            
        % Phase I        
        u_ini = u_k_1_N;    % Use the solution of last MPC iteration as a guess of the initial value
        if min(G*u_ini-W-E*x_k) < -1e-8
            u_ini = linprog(zeros(ndec,1),-G,-W-E*x_k);
        end
        if min(G*u_ini-W-E*x_k) < -1e-8
            error('Correction failed!')
        end        
        H_c = H;
        c_c = F'*x_k;
        lg_c = Ws+Es*x_k;
        u_ini_c = zeros(ndec,1);
        for i = 1:ndec
            u_ini_c(i) = u_ini(i);
        end
        
        [u_k_N_wgs_C_single, time1, iter_c_single] = wgsSolver(H_c, c_c, Gs, lg_c, lx, ux, u_ini, [], [],1);
        [u_k_N_wgs_C_double, time2, iter_c_double] = wgsSolver(H_c, c_c, Gs, lg_c, lx, ux, u_ini, [], [],2);        
        
        time_Record(kk,ii,4) = time1;
        if time_Record(kk,4) > maxTime_Record(ii,4);
            maxTime_Record(ii,4) = time_Record(kk);
        end
        
        time_Record(kk,ii,5) = time2;
        if time_Record(kk,5) > maxTime_Record(ii,5);
            maxTime_Record(ii,5) = time_Record(kk);
        end        
        
        diff = max([abs(u_k_N - u_k_N_wgs_C_single)]);
        diff_wgsC_single_QUADPROG = [diff_wgsC_single_QUADPROG;diff];
        if (diff > 0.001)
            pause;
            disp('Single C code gives wrong answers!');
        end        
        iter_wgsC_single = [iter_wgsC_single;iter_c_single];    
        
        diff = max([abs(u_k_N - u_k_N_wgs_C_double)]);
        diff_wgsC_double_QUADPROG = [diff_wgsC_double_QUADPROG;diff];
        if (diff > 0.00001)
            error('Double C code gives wrong answers!');
        end              
        iter_wgsC_double = [iter_wgsC_double;iter_c_double];                                       
        
        u_k = u_k_N(1:nu);        
               
        % No process disturbance
        x_k = Ad * x_k + Bd * u_k;
        % With process distrubance
        % x_k = x_k + max(x_k)*noiseAmp*rand(nx,1);
        
        % Updates
        u_k_1_N = u_k_N;       
        
        disp('Horizon: '); disp(ii*10); 
        disp('Iteration: '); disp(kk); 
    end
    
    %plot(x_Record);hold on;
    
end

% figure;plot(diff_wgsC_single_QUADPROG);title('Error between wgs C code(single) and QUADPROG');
% figure;plot(diff_wgsC_double_QUADPROG);title('Error between wgs C code(double) and QUADPROG');
% figure;plot(diff_gbBarrier_QUADPROG);title('Error between Gurobi(Barrier) and QUADPROG');
% figure;plot(diff_gbSimplex_QUADPROG);title('Error between Gurobi(Simplex) and QUADPROG');
% figure;plot(iter_QUADPROG);title('Iteration count of QUADPROG');
% figure;plot(iter_gbBarrier);title('Iteration count of Gurobi(Barrier)');
% figure;plot(iter_gbSimplex);title('Iteration count of Gurobi(Simplex)');
% figure;plot(iter_wgsC_single);title('Iteration count of wgs C code(single)');
% figure;plot(iter_wgsC_double);title('Iteration count of wgs C code(double)');

figure;
semilogy(diff_wgsC_single_QUADPROG); hold on;
semilogy(diff_wgsC_double_QUADPROG); hold on;
semilogy(diff_gbBarrier_QUADPROG); hold on;
semilogy(diff_gbSimplex_QUADPROG); title('Error between solvers and QUADPROG(active-set solver)');
legend('diff wgsC(single) QUADPROG','diff wgsC(double) QUADPROG','diff Gurobi(Barrier) QUADPROG','diff Gurobi(Simplex) QUADPROG');
figure;
semilogy(iter_wgsC_single); hold on;
semilogy(iter_wgsC_double); hold on;
semilogy(iter_gbBarrier); hold on;
semilogy(iter_gbSimplex); hold on;
semilogy(iter_QUADPROG); title('Iteration counts of solvers');
legend('iter wgsC(single)','iter wgsC(double)','iter Gurobi(Barrier)','iter Gurobi(Simplex)', 'iter QUADPROG');
