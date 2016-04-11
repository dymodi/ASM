%% Generate and simulate MPC problems based on given parameters
% 2015.12.30


function output = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R,solverSwitch)

global LP1Failtimes LP1NotFailtimes xDelta serialPort
maxIter = 200;

hasTransed = 0;

%% Generate Random Model
csys = rss(nx,ny,nu);
disPlant = c2d(csys,Ts);
Ad = disPlant(1,1).a;
Bd = zeros(nx,nu);
for i = 1:nu
    Bd(:,i) = disPlant(1,i).b;
end
Cd = zeros(ny,nx);
for i = 1:ny
    Cd(i,:) = disPlant(i,:).c;
end
Dd = zeros(ny,nu);
% Transform the model based on u to the model based on delta_u
[A_e,B_e,C_e] = augment(Ad,Bd,Cd,Dd);

%% Control parameters
L1 = zeros(nx,ny);
L2 = eye(ny,ny);
L=[L1;L2];
% F and Phi are used to predict x and y based on delta_u
[F,Phi] = fphi_v2(A_e,B_e,C_e,P,M);

%% Constraints settings
II = eye(nu*M,nu*M);
B = eye(nu*M,nu*M);
for i = 1:nu*M
    for j = 1:nu*M
        for k = 1:M
            if(i==(j+(k-1)*nu))
                B(i,j)=1;
            end
        end
    end
end
% Constraints with delta_u, u and y
%　OMEGA_L = [II;-II;B;-B;Phi;-Phi];
% Constraints with delta_u, and u
% OMEGA_L = [II;-II;B;-B];
% Constraints with u and y
OMEGA_L = [B;-B;Phi;-Phi];
% Constraints specifications
Umax = 0.4;
Umin = -0.4;
delta_U_p_ = 0.5*ones(nu,1);
delta_U_n_ = -0.5*ones(nu,1);
U_p_ = Umax*ones(nu,1);
U_n_ = Umin*ones(nu,1);
info = stepinfo(csys);
Yinfo = zeros(ny,nu);
for i = 1: ny
    for j = 1:nu
        Yinfo(i,j) = 0.5*(info(i,j).SettlingMin+info(i,j).SettlingMax);
    end
end
if max(max(isnan(Yinfo))) == 1      % The process is unstabel
    Ymax = 3;
    Ymin = -3;
else
    Ymax = max(max(Yinfo));
    Ymin = min(min(Yinfo));
end
yCoef = 0.2;
if Ymax > 0
    Y_p_ = Ymax*yCoef*ones(ny,1);
else
    Y_p_ = Ymax/yCoef*ones(ny,1);
end
if Ymin < 0
    Y_n_ = Ymin*yCoef*ones(ny,1);
else
    Y_n_ = Ymin/yCoef*ones(ny,1);
end
% % The followings are sample constraints for flight control
% delta_U_p_ = [1;1];delta_U_n_ = [-1;-1];
% U_p_ = [25;25]; U_n_ = [-25;-25];
% Y_p_ = [0.5;100]; Y_n_ = [-0.5;-100]

% Constraints augment
delta_U_p=[];delta_U_n=[];U_p=[];U_n=[];Y_p=[];Y_n=[];
for k = 1:M
    delta_U_p = [delta_U_p;delta_U_p_];
    delta_U_n = [delta_U_n;delta_U_n_];
    U_p = [U_p;U_p_];
    U_n = [U_n;U_n_];
end
for k = 1:P
    Y_p = [Y_p;Y_p_];
    Y_n = [Y_n;Y_n_];
end

%% Output reference
% The following is sample reference for flight control
% Yr = [zeros(1,Nsim);zeros(1,Nsim/4),10*ones(1,Nsim/4*3)];
% rr = [];
% for i = 1:P
%     rr = [rr;Yr];
% end

%% Simulation Initialization
[n,~] = size(B_e);           % Dimenson of states
xm = zeros(nx,1);               % xm is based on x
x_k = zeros(n,1);               % x_k is based on delta_x
u_k = zeros(nu,1);              % input
y_k = zeros(ny,1);              % output
delta_u = 0*ones(nu,1);
u_k_1 = zeros(nu,1);            % u(k-1)
u_k_2 = zeros(nu,1);            % u(k-2)
delta_u2 = zeros(nu,1);
delta_u_ini = 0*ones(nu*M,1);
delta_u_M_out = zeros(nu*M,1);
delta_u_M_out_asm = zeros(nu*M,1);

% G is the Hessian in the QP：min 0.5*x'*G*x + c'*x   subject to:  A*x <= b
G = Phi'*(Q*eye(ny*P,ny*P))*Phi + R*eye(nu*M,nu*M);

% Records for drawing
delta_u_draw = zeros(Nsim,nu);
y_draw = zeros(Nsim,ny);    x_draw = zeros(n,Nsim);
u_draw = zeros(Nsim,nu);
invG = inv(G);
diff_ASM_QUAD = [];         diff_ASMDUAL_QUAD = [];
diff_ASMDUAL_QUAD_CS = [];  diff_WGS_QUAD = [];
diff_ASM_C_QUAD = [];
diff_DSPASM_QUAD = [];      diff_DSPWGS_QUAD = [];
iter_ASM = [];              iter_ASM_cs = [];
iter_ASM_cs_new = [];       iter_ASM_ws = [];
iter_ASM_ws_cs_new = [];    iter_ASM_dual = [];
iter_ASM_dual_cs = [];      iter_WGS = [];
iter_DSPASM = [];           iter_DSPWGS = [];
time_QUAD = [];             time_WGS = [];
iter_ASM_C = [];            time_ASM_C = [];
time_DSPASM = [];           time_DSPWGS = [];
data_max_delta_u = [];
finalAS = [];
lpW = [];
ucTimes = 0;        % Record the cases that optimum is unconstrained
tightTimes = 0;     % Record the cases that no feasible solution existed
failTimesPrimASM = 0;           failTimesPrimASM_CS = 0;
failTimesPrimASM_WS = 0;        failTimesPrimASM_CS_New = 0;
failTimesPrimASM_WS_CS_New = 0; failTimesDualASM = 0;
failTimesDualASM_CS = 0;        failTimesWGS = 0;
failTimesASM_C = 0;

% % Here we set a fixed reference
% rrEle = (Ymax-Ymin)*rand(ny,1)+Ymin*ones(ny,1);

% % Here we try to do some EMPC approximation
% C_empc = eye(nx,nx);
% D_empc = eye(nu,nu);
% [H_empc, F_empc, G_empc, W_empc, E_empc] = QPformRT(P, R*eye(nu,nu),...
%     Q*eye(ny,ny), Ad, Bd, C_empc,D_empc, Ymax, Ymin, Umax, Umin,Cd);

% Simulation
for kk = 1:Nsim;
    % r_k = rr(:,kk);        %对k时刻的参考轨迹进行更新
    
%     % Update x_k in normal simulation
%     x_k_old = x_k;
%     x_k = A_e * x_k + B_e * (u_k_1 - u_k_2);    % Prediction
%     x_k = x_k + L * (y_k - C_e * x_k);          % Correction
%     % xDelta = [xDelta;norm(x_k_old - x_k)];
%     u_k_2 = u_k_1;
%     u_k_1 = u_k;
    
    oldFinalAS = finalAS;
    oldDelta_u_M_out = delta_u_M_out_asm;
    oldLpW = lpW;
    
    % Generate random x_k and u_k_1
    x_k_old = x_k;
    x_k = 0.5*rand(n,1)-0.2*ones(n,1);
    xDelta = [xDelta;norm(x_k_old - x_k)];
    % u_k_1 = 0.7*((Umax-Umin)*rand(nu,1)+Umin*ones(nu,1));
    u_k_1 = zeros(nu,1);
    
    % The following generate a random reference
    rrEle = (Ymax-Ymin)*rand(ny,1)+Ymin*ones(ny,1);
    rrEle = 1.8*rand(ny,1)-0.9*ones(ny,1);
    
    r_k = [];
    for i = 1:P
        r_k = [r_k;rrEle];
    end
    
    aug_u_k_1 = [];
    for k = 1:M
        aug_u_k_1 = [aug_u_k_1;u_k_1];
    end
    
    %     % Constraints with delta_u, u and y
    %     omega_r = [delta_U_p;-delta_U_n;U_p-aug_u_k_1;-U_n+aug_u_k_1;...
    %        Y_p-F*x_k;-Y_n+F*x_k];
    % Constraints with u and y
    omega_r = [U_p-aug_u_k_1;-U_n+aug_u_k_1;Y_p-F*x_k;-Y_n+F*x_k];
    % Constraints with delta_u, and u
    % omega_r = [delta_U_p;-delta_U_n;U_p-aug_u_k_1;-U_n+aug_u_k_1];
    
    c = (F*x_k-r_k)'*Q*eye(ny*P,ny*P)*Phi;
    c = c';
    
    if solverSwitch.QUAD == 1
        tic
        delta_u_M_out = quadprog(G,c,OMEGA_L,omega_r);
        time = toc;
        time_QUAD = [time_QUAD;time];
    end
    
    % Here we check wether the problem is too tight
    if isempty(delta_u_M_out)
        tightTimes = tightTimes + 1;
        zoomPara = 1.3;
        if Y_p_ > 0
            Y_p_ = Y_p_*zoomPara;
        else
            Y_p_ = Y_p_/zoomPara;
        end
        if Y_n_ < 0
            Y_n_ = Y_n_*zoomPara;
        else
            Y_n_ = Y_n_/zoomPara;
        end
        U_p_ = zoomPara*U_p_;
        U_n_ = zoomPara*U_n_;
        continue;
    end
    
    % Here we check wether it's a unconstrained problem
    if min(abs(OMEGA_L*delta_u_M_out-omega_r)) > 1e-5
        ucTimes = ucTimes + 1;
        zoomPara = 0.7;
        if Y_p_ > 0
            Y_p_ = Y_p_*zoomPara;
        else
            Y_p_ = Y_p_/zoomPara;
        end
        if Y_n_ < 0
            Y_n_ = Y_n_*zoomPara;
        else
            Y_n_ = Y_n_/zoomPara;
        end
        continue;
    end
    
    %Phase I (Generate feasible starting point)
    x_ini = zeros(nu*M,1);
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        tightTimes = tightTimes + 1;
        continue;
        %error('Correction failed!')
    end
    
    % We have to use a uniformed starting point for comparison
    if isempty(oldDelta_u_M_out)
        disp('empty initial?');
        pause;
    end
    [x_ini,~,~] = wsPhaseI(OMEGA_L,omega_r,oldFinalAS,oldDelta_u_M_out,2);
    
    if solverSwitch.ASM == 1
        % Solve the problem with original primal ASM
        [delta_u_M_out_asm,~,iterASM,finalAS,failFlag] = asm(G,...
            invG,c,-OMEGA_L,-omega_r,x_ini,[],maxIter);
        iter_ASM = [iter_ASM;iterASM];
        diff = norm(delta_u_M_out_asm-delta_u_M_out);
        diff_ASM_QUAD = [diff_ASM_QUAD;diff];
        if failFlag == 1 || diff > 1e-3
            failTimesPrimASM = failTimesPrimASM + 1;
            disp('ASM failes!');
        end
    end
    
    if solverSwitch.ASM_CS == 1
        % Solve with Primal ASM with Gionata's Constraints Selection
        [delta_u_M_out_asm_cs,~,iter,lpW,failFlag] = asm_cs(G,...
            invG,c,-OMEGA_L,-omega_r,x_ini,[],maxIter,ny,nu,M,P);
        iter_ASM_cs = [iter_ASM_cs;iter];
        diff = norm(delta_u_M_out_asm_cs-delta_u_M_out);
        if failFlag == 1 || diff > 1e-3
            failTimesPrimASM_CS = failTimesPrimASM_CS + 1;
            disp('ASM_cs fails.');
        end
    end
    
    if solverSwitch.ASM_CS_NEW == 1
        % Solve the problem with Xu's Constraints Selection
        [delta_u_M_out_asm_cs_new,~,iter,~,failFlag] = asm_cs_new(G,...
            invG,c,-OMEGA_L,-omega_r,x_ini,[],maxIter,oldFinalAS);
        iter_ASM_cs_new = [iter_ASM_cs_new;iter];
        diff = norm(delta_u_M_out_asm_cs_new-delta_u_M_out);
        if failFlag == 1 || diff > 1e-3
            failTimesPrimASM_CS_New = failTimesPrimASM_CS_New + 1;
            disp('ASM_cs_new fails.');
        end
    end
    
    if solverSwitch.ASM_DUAL == 1
        % Solve with Dual ASM
        [delta_u_M_out_asm_dual,iter_dual,~,failFlag] = asm_dual(G,...
            invG,c,-OMEGA_L,-omega_r,[],[],maxIter);
        iter_ASM_dual = [iter_ASM_dual;iter_dual];
        diff = norm(delta_u_M_out_asm_dual-delta_u_M_out);
        if failFlag == 1 || diff > 1e-3
            failTimesDualASM = failTimesDualASM + 1;
            disp('ASM_dual fails.');
        end
        diff_ASMDUAL_QUAD = [diff_ASMDUAL_QUAD;diff];
    end
    
    if solverSwitch.ASM_DUAL_CS == 1
        % Solve the problem with Dual ASM with constraints selection
        [delta_u_M_out_asm_dual,iter_dual_cs,~,failFlag] = asm_dual_cs(G,...
            invG,c,-OMEGA_L,-omega_r,[],[],300,ny,nu,M,P);
        iter_ASM_dual_cs = [iter_ASM_dual_cs;iter_dual_cs];
        diff = norm(delta_u_M_out_asm_dual-delta_u_M_out);
        if failFlag == 1 || diff > 1e-3
            failTimesDualASM_CS = failTimesDualASM_CS + 1;
            disp('ASM_dual_cs fails.');
        end
        diff_ASMDUAL_QUAD_CS = [diff_ASMDUAL_QUAD_CS;diff];
    end
    
    %     % Initial point based on previous optimal active set
    %     % My old wrong method, for comparison
    %     % Phase I
    %     x_ini_oldws = delta_u_M_out;
    %     %if max(OMEGA_L*x_ini-omega_r) > 1e-8
    %     if isempty(oldFinalAS)
    %         x_ini_oldws = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    %     else
    %         Aeq = [];
    %         beq = [];
    %         finalASuseToformAeq = oldFinalAS;
    %         for j=1:length(oldFinalAS)
    %             Aeq = [Aeq;OMEGA_L(oldFinalAS(j),:)];
    %             beq = [beq;omega_r(oldFinalAS(j),:)];
    %         end
    %         x_ini_oldws = linprog(zeros(nu*M,1),OMEGA_L,omega_r,Aeq,beq);
    %         oldWSFail = 0;
    %     end
    %     %end
    %     if (isempty(x_ini_oldws)) || (max(OMEGA_L*x_ini_oldws-omega_r) > 1e-8)
    %         x_ini_oldws = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    %         oldWSFail = 1;
    %         finalAS = [];
    %         if max(OMEGA_L*x_ini_oldws-omega_r) > 1e-8
    %             error('Correction failed!')
    %         end
    %     end
    
    %     [Kax, Lax, cx, clambda] = calPara(G_empc, W_empc, E_empc, H_empc, F_empc, finalAS, -1);
    %     residual1 = Lax*x_k+clambda;
    
    
    if solverSwitch.ASM_WS == 1 || solverSwitch.ASM_WS_CS == 1
        % Decide whether use warm start according to u change
        max_delta_u = max(abs(oldDelta_u_M_out(1:nu)));
        data_max_delta_u = [data_max_delta_u;max_delta_u];
        if  max_delta_u > 0.05*(Umax-Umin)
            [x_ws,LP1Fail,iniW] = wsPhaseI(OMEGA_L,omega_r,oldLpW,oldDelta_u_M_out,2);
        else
            [x_ws,LP1Fail,iniW] = wsPhaseI(OMEGA_L,omega_r,oldLpW,oldDelta_u_M_out,1);
        end
        if LP1Fail == 1
            LP1Failtimes = LP1Failtimes + 1;
        else
            LP1NotFailtimes = LP1NotFailtimes + 1;
        end
    end
    

    
    if solverSwitch.ASM_WS == 1
        % Solve with Warm Start
        [delta_u_M_out_asm_ws,~,iter,finalASws,failFlag] = asm(G,...
            invG,c,-OMEGA_L,-omega_r,x_ws,iniW,maxIter);
        iter_ASM_ws = [iter_ASM_ws;iter];
        diff = norm(delta_u_M_out_asm_ws-delta_u_M_out);
        if failFlag == 1 || diff > 1e-3
            failTimesPrimASM_WS = failTimesPrimASM_WS + 1;
            disp('ASM_ws fails.');
        end
        if iter > iterASM
            disp('Worse than Priaml ASM');
            pause;
        end
    end    
    
    if solverSwitch.ASM_WS_CS == 1
        % Solve with Xu's Constraints Selection and new Warm Start
        [delta_u_M_out_asm_ws_cs_new,~,iter,~,failFlag] = asm_cs_new(G,...
            invG,c,-OMEGA_L,-omega_r,x_ws,iniW,maxIter,finalAS);
        iter_ASM_ws_cs_new = [iter_ASM_ws_cs_new;iter];
        diff = norm(delta_u_M_out_asm_ws_cs_new-delta_u_M_out);
        if diff > 1e-3 || failFlag == 1
            failTimesPrimASM_WS_CS_New = failTimesPrimASM_WS_CS_New + 1;
        end
        if iter > iterASM
            disp('Worse than Priaml ASM');
        end
    end
    
    if solverSwitch.WGS == 1
        % Solve with WGS
        [delta_u_M_out_wgs, time, iter] = wgsSolver(G, c, -OMEGA_L,...
            -omega_r, [], [], x_ini, [], [], 2);
        time_WGS = [time_WGS;time];
        iter_WGS = [iter_WGS;iter];
        diff = norm(delta_u_M_out_wgs-delta_u_M_out);
        diff_WGS_QUAD = [diff_WGS_QUAD;diff];
        if diff > 1e-3
            failTimesWGS = failTimesWGS + 1;
            disp('WGS fails.');
        end
    end        
    
    if solverSwitch.ASM_C == 1
        [delta_u_M_out_asm_c, time, iter] = asmSolver(G, c, -OMEGA_L,...
            -omega_r, x_ini, [], 2);
        time_ASM_C = [time_ASM_C;time];
        iter_ASM_C = [iter_ASM_C;iter];
        diff = norm(delta_u_M_out_asm_c-delta_u_M_out);
        diff_ASM_C_QUAD = [diff_ASM_C_QUAD;diff];
        if diff > 1e-3
            failTimesASM_C = failTimesASM_C + 1;
            disp('ASM_C fails.');
        end
    end
    
    if solverSwitch.DSPASM == 1
        if hasTransed == 0
            [delta_u_M_out_dsp_asm,time,iter] = dspSolver(G,c,-OMEGA_L,-omega_r,x_ini,[],1,1,serialPort);
        hasTransed = 1;
        else
            [delta_u_M_out_dsp_asm,time,iter] = dspSolver(G,c,-OMEGA_L,-omega_r,x_ini,[],1,0,serialPort);
        end
        time_DSPASM = [time_DSPASM;time];
        iter_DSPASM = [iter_DSPASM;iter];
        diff = norm(delta_u_M_out_dsp_asm-delta_u_M_out);
        diff_DSPASM_QUAD = [diff_DSPASM_QUAD;diff];
        if diff > 1e-3
            disp('DSP ASM fails.');
        end
    end
    
    if solverSwitch.DSPWGS == 1
        if hasTransed == 0
            [delta_u_M_out_dsp_wgs,time,iter] = dspSolver(G,c,-OMEGA_L,-omega_r,x_ini,[],2,1,serialPort);
            hasTransed = 1;
        else
            [delta_u_M_out_dsp_wgs,time,iter] = dspSolver(G,c,-OMEGA_L,-omega_r,x_ini,[],2,0,serialPort);
        end
        time_DSPWGS = [time_DSPWGS;time];
        iter_DSPWGS = [iter_DSPWGS;iter];
        diff = norm(delta_u_M_out_dsp_wgs-delta_u_M_out);
        diff_DSPWGS_QUAD = [diff_DSPWGS_QUAD;diff];
        if diff > 1e-3
            disp('DSP WGS fails.');
        end
    end
    
    % The followings are used to do simulations
    delta_u = delta_u_M_out(1:nu,1);
    u_k = u_k + delta_u;
    xm = Ad*xm + Bd*u_k;    % States updating
    y_k = Cd*xm;            % Output updating
    
%     % Records for drawing
%     delta_u_draw(kk,:) = delta_u';
%     u_draw(kk,:) = u_k';
%     y_draw(kk,:) = y_k';
%     x_draw(1,kk) = x_k(1,1);x_draw(2,kk) = x_k(2,1);x_draw(3,kk) = x_k(3,1);
%     x_draw(4,kk) = x_k(4,1);x_draw(5,kk) = x_k(5,1);
    
end

%semilogy(diff_ASMDUAL_QUAD);
output.maxIterPrimASM = max(iter_ASM(2:length(iter_ASM)));
output.maxIterPrimASM_CS = max(iter_ASM_cs(2:length(iter_ASM_cs)));
output.maxIterPrimASM_CS_New = max(iter_ASM_cs_new(2:length(iter_ASM_cs_new)));
output.maxIterDualASM = max(iter_ASM_dual);
output.maxIterDualASM_CS = max(iter_ASM_dual_cs);
output.maxIterPrimASM_WS = max(iter_ASM_ws(2:length(iter_ASM_ws)));
output.maxIterPrimASM_WS_CS_New = max(iter_ASM_ws_cs_new(2:length(iter_ASM_ws_cs_new)));
output.maxIterWGS = max(iter_WGS(2:length(iter_WGS)));
output.maxIterASM_C = max(iter_ASM_C(2:length(iter_ASM_C)));
output.maxIterDSPASM = max(iter_DSPASM(2:length(iter_DSPASM)));
output.maxIterDSPWGS = max(iter_DSPWGS(2:length(iter_DSPWGS)));

output.avgIterPrimASM = mean(iter_ASM(2:length(iter_ASM)));
output.avgIterPrimASM_CS = mean(iter_ASM_cs(2:length(iter_ASM_cs)));
output.avgIterPrimASM_CS_New = mean(iter_ASM_cs_new(2:length(iter_ASM_cs_new)));
output.avgIterDualASM = mean(iter_ASM_dual);
output.avgIterDualASM_CS = mean(iter_ASM_dual_cs);
output.avgIterPrimASM_WS = mean(iter_ASM_ws(2:length(iter_ASM_ws)));
output.avgIterPrimASM_WS_CS_New = mean(iter_ASM_ws_cs_new(2:length(iter_ASM_ws_cs_new)));
output.avgIterWGS = mean(iter_WGS(2:length(iter_WGS)));
output.avgIterASM_C = mean(iter_ASM_C(2:length(iter_ASM_C)));
output.avgIterDSPASM = mean(iter_DSPASM(2:length(iter_DSPASM)));
output.avgIterDSPWGS = mean(iter_DSPWGS(2:length(iter_DSPWGS)));

output.ucTimes = ucTimes;
output.tightTimes = tightTimes;
output.failTimesPrimASM = failTimesPrimASM;
output.failTimesPrimASM_CS = failTimesPrimASM_CS;
output.failTimesPrimASM_CS_New = failTimesPrimASM_CS_New;
output.failTimesPrimASM_WS = failTimesPrimASM_WS;
output.failTimesPrimASM_WS_CS_New = failTimesPrimASM_WS_CS_New;
output.failTimesDualASM = failTimesDualASM;
output.failTimesDualASM_CS = failTimesDualASM_CS;

output.maxTimeQUAD = max(time_QUAD(2:length(time_QUAD)));
output.maxTimeWGS = max(time_WGS(2:length(time_WGS)));
output.maxTimeASM_C = max(time_ASM_C(2:length(time_ASM_C)));
output.maxTimeDSPASM = max(time_DSPASM(2:length(time_DSPASM)));
output.maxTimeDSPWGS = max(time_DSPWGS(2:length(time_DSPWGS)));

output.avgTimeQUAD = mean(time_QUAD(2:length(time_QUAD)));
output.avgTimeWGS = mean(time_WGS(2:length(time_WGS)));
output.avgTimeASM_C = mean(time_ASM_C(2:length(time_ASM_C)));
output.avgTimeDSPASM = mean(time_DSPASM(2:length(time_DSPASM)));
output.avgTimeDSPWGS = mean(time_DSPWGS(2:length(time_DSPWGS)));


output.maxDiffPrimASM = max(diff_ASM_QUAD(2:length(diff_ASM_QUAD)));
output.maxDiffWGS = max(diff_WGS_QUAD(2:length(diff_WGS_QUAD)));
output.maxDiffASM_C = max(diff_ASM_C_QUAD(2:length(diff_ASM_C_QUAD)));
output.maxDiffDSPASM = max(diff_DSPASM_QUAD(2:length(diff_DSPASM_QUAD)));
output.maxDiffDSPWGS = max(diff_DSPWGS_QUAD(2:length(diff_DSPWGS_QUAD)));

output.avgDiffPrimASM = mean(diff_ASM_QUAD(2:length(diff_ASM_QUAD)));
output.avgDiffWGS = mean(diff_WGS_QUAD(2:length(diff_WGS_QUAD)));
output.avgDiffASM_C = mean(diff_ASM_C_QUAD(2:length(diff_ASM_C_QUAD)));
output.avgDiffDSPASM = mean(diff_DSPASM_QUAD(2:length(diff_DSPASM_QUAD)));
output.avgDiffDSPWGS = mean(diff_DSPWGS_QUAD(2:length(diff_DSPWGS_QUAD)));

% % Drawing
% figure;
% rr_draw = rrEle*ones(1,Nsim);
% subplot(2,1,1); plot(y_draw(:,1),'LineWidth',2); title('y(k)');
% hold on; plot(y_draw(:,2),'LineWidth',2);
% hold on; plot(rr_draw(1,:)); hold on; plot(rr_draw(2,:));
% subplot(2,1,2); stairs(u_draw(:,1),'LineWidth',2);title('u(k)');
% hold on; stairs(u_draw(:,2),'LineWidth',2);
% % figure; title('Iteration count')
% % plot(iter_ASM); hold on; plot(iter_ASM_cs);
% % legend('Original ASM','ASM with Constraints Selection');
% % % figure; title('Iteration count')
% % % plot(iter_ASM); hold on; plot(iter_ASM_ws);
% % % legend('Original ASM','ASM with Warm Start');
% figure;
% plot(iter_ASM,'linewidth',2); hold on; plot(iter_ASM_cs,'linewidth',2);
% hold on;plot(iter_ASM_ws_cs_new,'linewidth',2);hold on;
% plot(iter_ASM_ws,'linewidth',2);title('Iteration count')
% legend('Primal ASM','Primal ASM with CS','Primal ASM with WS','Primal ASM with new CS');
% % figure;
% % plot(iter_ASM_dual,'linewidth',2);hold on;plot(iter_ASM_dual_cs,'linewidth',2);
% % title('Iteration count')
% % legend('Dual ASM','Dual ASM with CS');

end
