%% Aircraft with Unstable Poles with Smart Selection ASM
% This example shows how to control an unstable aircraft with saturating
% actuators primal using active set method with smart selction

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
Ts = 0.05;          % Sampling time
disPlant = c2d(plant,Ts);
Ad = disPlant(1,1).a;
Bd = [disPlant(1,1).b,disPlant(1,2).b];
Cd = [disPlant(1,1).c;disPlant(2,1).c];
Dd = D;

x0 = zeros(4,1);
nx = 4; nu = 2; ny = 2;

% Transform the model based on u to the model based on delta_u
[A_e,B_e,C_e] = augment(Ad,Bd,Cd,Dd);

%% Control parameters
% Create an MPC controller with plant model, sample time and horizons.
Nsim = 100;
P = 10;             % Prediction horizon
M = 2;              % Control horizon
Q = 10;
R = 0.1;
L1 = zeros(nx,ny);
L2 = eye(ny,ny);
L=[L1;L2];

% F and Phi are used to predict x and y based on delta_u
[F,Phi] = fphi_v2(A_e,B_e,C_e,P,M);

%% Output reference
Yr = [zeros(1,Nsim);zeros(1,Nsim/4),10*ones(1,Nsim/4*3)];
rr = [];
for i = 1:P
    rr = [rr;Yr];
end

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
% OMEGA_L = [II;-II;B;-B;Phi;-Phi];
% Constraints with delta_u, and u
% OMEGA_L = [II;-II;B;-B];
% Constraints with u and y
OMEGA_L = [B;-B;Phi;-Phi];
delta_U_p_ = [1;1];delta_U_n_ = [-1;-1];
U_p_ = [25;25]; U_n_ = [-25;-25];
Y_p_ = [0.5;100]; Y_n_ = [-0.5;-100];
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

%% Simulation Initialization
[n,n_in] = size(B_e);           % Dimenson of states
xm = zeros(nx,1);               % xm is based on x
x_k = zeros(n,1);               % x_k is based on delta_x
u_k = zeros(nu,1);              % input
y_k = zeros(ny,1);              % output
delta_u = 0*ones(nu,1);         %
u_k_1 = zeros(nu,1);            % u(k-1)
u_k_2 = zeros(nu,1);            % u(k-2)
delta_u2 = zeros(nu,1);
delta_u_M_in = zeros(nu*M,1);
delta_u_ini = 0*ones(nu*M,1);
y_ini = 0*ones(4*nu*M,1);

% G is the Hessian in the QP£ºmin 0.5*x'*G*x + c'*x   subject to:  A*x <= b
G = Phi'*(Q*eye(ny*P,ny*P))*Phi + R*eye(nu*M,nu*M);

% Records for drawing
delta_u_draw = zeros(Nsim,nu);
delta_u_uc_draw = zeros(Nsim,nu);
y_draw = zeros(Nsim,ny);
x_draw = zeros(n,Nsim);
u_draw = zeros(Nsim,nu);
Iter_rec= [];
invG = inv(G);
diff_ASM_QUAD = [];
diff_ASM_QUAD_dual = [];
delta_u_M_out = zeros(nu*M,1);
iter_ASM = [];
iter_ASM_cs = [];
iter_ASM_dual = [];
iter_ASM_ws = [];
finalAS = [];

% Simulation
for kk = 1:Nsim;
    r_k = rr(:,kk);
    x_k = A_e * x_k + B_e * (u_k_1 - u_k_2);    % Prediction
    x_k = x_k + L * (y_k - C_e * x_k);          % Correction
    aug_u_k_1 = [];
    for k = 1:M
        aug_u_k_1 = [aug_u_k_1;u_k_1];
    end
    
    % Constraints with u and y
    omega_r = [U_p-aug_u_k_1;-U_n+aug_u_k_1;Y_p-F*x_k;-Y_n+F*x_k];
    c = (F*x_k-r_k)'*Q*eye(ny*P,ny*P)*Phi;
    c = c';
        
    delta_u_M_out = quadprog(G,c,OMEGA_L,omega_r);    
    % Phase I (Generate feasible starting point)
    % x_ini = delta_u_M_out;
    x_ini = zeros(nu*M,1);
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        error('Correction failed!')
    end
    [delta_u_M_out_asm,~,iter,finalAS_right] = asm(G,invG,c,-OMEGA_L,-omega_r,x_ini,[],200);
    iter_ASM = [iter_ASM;iter];
    
    % Phase I (Generate feasible starting point)
    % x_ini = delta_u_M_out;
    x_ini = zeros(nu*M,1);
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        error('Correction failed!')
    end
    [delta_u_M_out_asm_cs,~,iter,~] = asm_cs(G,invG,c,-OMEGA_L,-omega_r,x_ini,[],200,ny,nu,M,P);
    iter_ASM_cs = [iter_ASM_cs;iter];    
    diff = norm(delta_u_M_out_asm_cs-delta_u_M_out);
    if diff > 1e-5
        disp('ASM_cs fails.');
    end
    diff_ASM_QUAD = [diff_ASM_QUAD;diff];
       
    [delta_u_M_out_asm_dual, iter, ~, failFlag] = asm_dual(G,inv(G),c,-OMEGA_L,-omega_r,[],[],200);
    iter_ASM_dual = [iter_ASM_dual;iter];
    diff = norm(delta_u_M_out_asm_dual-delta_u_M_out);
    if diff > 1e-5
        error('ASM_dual fails.');
    end
    diff_ASM_QUAD_dual = [diff_ASM_QUAD_dual;diff];
        
    %     % Initial point based on previous optimal active set
    %     % Phase I
    %     x_ini = delta_u_M_out;    % Use the solution of last MPC iteration as a guess of the initial value
    %     %if max(OMEGA_L*x_ini-omega_r) > 1e-8
    %         if isempty(finalAS)
    %             x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    %         else
    %             Aeq = [];
    %             beq = [];
    %             finalASuseToformAeq = finalAS;
    %             for j=1:length(finalAS)
    %                 Aeq = [Aeq;OMEGA_L(finalAS(j),:)];
    %                 beq = [beq;omega_r(finalAS(j),:)];
    %             end
    %             x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r,Aeq,beq);
    %         end
    %     %end
    %     if (isempty(x_ini)) || (max(OMEGA_L*x_ini-omega_r) > 1e-8)
    %         x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    %         finalAS = [];
    %         if max(OMEGA_L*x_ini-omega_r) > 1e-8
    %             error('Correction failed!')
    %         end
    %     end
    %     oldfinalAS = finalAS;
    %     %[delta_u_M_out_asm_ws,~,iter,finalAS] = asm(G,invG,c,-OMEGA_L,-omega_r,x_ini,finalAS,200);
    %     [delta_u_M_out_asm_ws,~,iter,finalAS] = asm_cs_flight(G,invG,c,-OMEGA_L,-omega_r,x_ini,finalAS,200,ny,nu,M,P);
    %     iter_ASM_ws = [iter_ASM_ws;iter];

    delta_u = delta_u_M_out(1:nu,1);
    u_k = u_k + delta_u;
    xm = Ad*xm + Bd*u_k;    % States updating
    y_k = Cd*xm;            % Output updating
    u_k_2 = u_k_1;
    u_k_1 = u_k;
    
    % Records for drawing
    delta_u_draw(kk,:) = delta_u';
    u_draw(kk,:) = u_k';
    y_draw(kk,:) = y_k';
    x_draw(1,kk) = x_k(1,1);x_draw(2,kk) = x_k(2,1);x_draw(3,kk) = x_k(3,1);x_draw(4,kk) = x_k(4,1);x_draw(5,kk) = x_k(5,1);
end

OriMax = max(iter_ASM);
CsMax = max(iter_ASM_cs);
OriAvg = mean(iter_ASM);
CsAvg = mean(iter_ASM_cs);

% Drawing
figure;
subplot(2,1,1); plot(y_draw(:,1),'LineWidth',2); title('y(k)');
hold on; plot(y_draw(:,2),'LineWidth',2);
subplot(2,1,2); stairs(u_draw(:,1),'LineWidth',2);title('u(k)');
hold on; stairs(u_draw(:,2),'LineWidth',2);
figure; title('Iteration count')
plot(iter_ASM); hold on; plot(iter_ASM_cs);
legend('Original ASM','ASM with Constraints Selection');
% figure; title('Iteration count')
% plot(iter_ASM); hold on; plot(iter_ASM_ws);
% legend('Original ASM','ASM with Warm Start');
