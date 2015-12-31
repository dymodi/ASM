%% Generate and simulate MPC problems based on given nu,ny,A,B,C,D


function [maxIterASM,avgIterASM,maxIterNew,avgIterNew] = generateMPC(nu,ny,nx,A,B,C,D,Ts,Nsim,P,M,Q,R)


%% Define Aircraft Model

plant = ss(A,B,C,D);
disPlant = c2d(plant,Ts);
Ad = disPlant(1,1).a;
Bd = zeros(nx,nu);
for i = 1:nu
    Bd(:,i) = disPlant(1,i).b;
end   
Cd = zeros(ny,nx);
for i = 1:ny
    Cd(i,:) = disPlant(i,:).c;
end
Dd = D;

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

%% Output reference
Yr = [zeros(1,Nsim);zeros(1,Nsim/4),10*ones(1,Nsim/4*3)];
rr = [];
for i = 1:P
    rr = [rr;Yr];
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

% G is the Hessian in the QP：min 0.5*x'*G*x + c'*x   subject to:  A*x <= b
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
delta_u_M_out = zeros(nu*M,1);
iter_ASM = [];
iter_ASM_cs = [];
iter_ASM_ws = [];
finalAS = [];

% Simulation
for kk = 1:Nsim;
    r_k = rr(:,kk);        %对k时刻的参考轨迹进行更新
    %% 修改这个地方，把MPC_v3里的计算过程显式地写在下面，这样也可以不用什么全局变量了
    %[delta_u,delta_u_M_in,u_k,y_k,x_k,delta_u_ini,y_ini,lambda_ini] = mpc_v3(delta_u,delta_u_ini,u_k,y_k,x_k,r_k,delta_u_ini,y_ini,lambda_ini);%调用MPC在线算法进行计算
    %预测
    x_k = A_e * x_k + B_e * (u_k_1 - u_k_2);
    %矫正
    x_k = x_k + L * (y_k - C_e * x_k);
    aug_u_k_1 = [];
    for k = 1:M
        aug_u_k_1 = [aug_u_k_1;u_k_1];
    end
    %带被控变量不带控制增量的约束
    omega_r = [U_p-aug_u_k_1;-U_n+aug_u_k_1;Y_p-F*x_k;-Y_n+F*x_k];
    c = (F*x_k-r_k)'*Q*eye(ny*P,ny*P)*Phi;
    c = c';
        
    
    %Phase I
    x_ini = delta_u_M_out;    % Use the solution of last MPC iteration as a guess of the initial value
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        error('Correction failed!')
    end
    [delta_u_M_out_asm,~,iter,finalAS_right] = asm(G,invG,c,-OMEGA_L,-omega_r,x_ini,[],200);
    iter_ASM = [iter_ASM;iter];
    
    %Phase I
    x_ini = delta_u_M_out;    % Use the solution of last MPC iteration as a guess of the initial value
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        error('Correction failed!')
    end
    [delta_u_M_out_asm_cs,~,iter,~] = asm_cs_flight(G,invG,c,-OMEGA_L,-omega_r,x_ini,[],200,ny,nu,M,P);
    iter_ASM_cs = [iter_ASM_cs;iter];
    
    % Initial point based on previous optimal active set
    % Phase I
    x_ini = delta_u_M_out;    % Use the solution of last MPC iteration as a guess of the initial value
    %if max(OMEGA_L*x_ini-omega_r) > 1e-8
        if isempty(finalAS)
            x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
        else
            Aeq = [];
            beq = [];
            finalASuseToformAeq = finalAS;
            for j=1:length(finalAS)
                Aeq = [Aeq;OMEGA_L(finalAS(j),:)];
                beq = [beq;omega_r(finalAS(j),:)];
            end
            x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r,Aeq,beq);
        end
    %end
    if (isempty(x_ini)) || (max(OMEGA_L*x_ini-omega_r) > 1e-8)
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
        finalAS = [];
        if max(OMEGA_L*x_ini-omega_r) > 1e-8
            error('Correction failed!')
        end
    end
    oldfinalAS = finalAS;
    %[delta_u_M_out_asm_ws,~,iter,finalAS] = asm(G,invG,c,-OMEGA_L,-omega_r,x_ini,finalAS,200);
    [delta_u_M_out_asm_ws,~,iter,finalAS] = asm_cs_flight(G,invG,c,-OMEGA_L,-omega_r,x_ini,finalAS,200,ny,nu,M,P);   
    iter_ASM_ws = [iter_ASM_ws;iter];
    
    delta_u_M_out = quadprog(G,c,OMEGA_L,omega_r);
    
    diff = norm(delta_u_M_out_asm_cs-delta_u_M_out);
    if diff > 1e-5
        disp('ASM_cs fails.');
    end
    diff_ASM_QUAD = [diff_ASM_QUAD;diff];
    
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

% Drawing
figure;
subplot(2,1,1); plot(y_draw(:,1),'LineWidth',2); title('y(k)');
hold on; plot(y_draw(:,2),'LineWidth',2); 
subplot(2,1,2); stairs(u_draw(:,1),'LineWidth',2);title('u(k)');
hold on; stairs(u_draw(:,2),'LineWidth',2);
figure; title('Iteration count')
plot(iter_ASM); hold on; plot(iter_ASM_cs);
legend('Original ASM','ASM with Constraints Selection');
figure; title('Iteration count')
plot(iter_ASM); hold on; plot(iter_ASM_ws);
legend('Original ASM','ASM with Warm Start');

end
