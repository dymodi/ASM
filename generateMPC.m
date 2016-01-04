%% Generate and simulate MPC problems based on given parameters


function [maxIterASM,avgIterASM,maxIterNew,avgIterNew,ucTimes,tightTimes,...
    failTimesASM,failTimesNew] = generateMPC(nu,ny,nx,Ts,Nsim,P,M,Q,R)

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
% OMEGA_L = [II;-II;B;-B;Phi;-Phi];   
% Constraints with delta_u, and u
% OMEGA_L = [II;-II;B;-B];
% Constraints with u and y
OMEGA_L = [B;-B;Phi;-Phi];
% Constraints specifications
Umax = 1;
Umin = -1;
delta_U_p_ = 1.5*ones(nu,1);
delta_U_n_ = -1.5*ones(nu,1);
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
    Ymax = 100;
    Ymin = -100;
else
    Ymax = max(max(Yinfo));
    Ymin = min(min(Yinfo));
end
yCoef = 5;
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

% The following generate a random reference
% rrEle = (Ymax-Ymin)*rand(ny,1)+Ymin*ones(ny,1);
rrEle = rand(ny,1)-0.5*ones(ny,1);
r_k = [];
for i = 1:P
    r_k = [r_k;rrEle];
end


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
invG = inv(G);
diff_ASM_QUAD = [];
iter_ASM = [];
iter_ASM_cs = [];
iter_ASM_ws = [];
finalAS = [];
ucTimes = 0;        % Record the cases that optimum is unconstrained
tightTimes = 0;     % Record the cases that no feasible solution existed
failTimesASM = 0;
failTimesNew = 0;

% Simulation
for kk = 1:Nsim;
    %r_k = rr(:,kk);        %对k时刻的参考轨迹进行更新   
    
%     % Update x_k in normal simulation
%     x_k = A_e * x_k + B_e * (u_k_1 - u_k_2);    % Prediction
%     x_k = x_k + L * (y_k - C_e * x_k);          % Correction
    
    % Generate random x_k and u_k_1
    x_k = 0.4*rand(n,1)-0.2*ones(n,1);
    %u_k_1 = 0.7*((Umax-Umin)*rand(nu,1)+Umin*ones(nu,1));
    u_k_1 = zeros(nu,1);
    
    aug_u_k_1 = [];
    for k = 1:M
        aug_u_k_1 = [aug_u_k_1;u_k_1];
    end
    
    % Constraints with delta_u, u and y
    % omega_r = [delta_U_p;-delta_U_n;U_p-aug_u_k_1;-U_n+aug_u_k_1;...
    %    Y_p-F*x_k;-Y_n+F*x_k];
    % Constraints with u and y
    omega_r = [U_p-aug_u_k_1;-U_n+aug_u_k_1;Y_p-F*x_k;-Y_n+F*x_k];
    % Constraints with delta_u, and u
    % omega_r = [delta_U_p;-delta_U_n;U_p-aug_u_k_1;-U_n+aug_u_k_1];
        
    c = (F*x_k-r_k)'*Q*eye(ny*P,ny*P)*Phi;
    c = c';
            
    delta_u_M_out = quadprog(G,c,OMEGA_L,omega_r);
    % Here we check wether the problem is too tight
    if isempty(delta_u_M_out)
        tightTimes = tightTimes + 1;
        continue;  
    end
    
    % Here we check wether it's a unconstrained problem
    if min(abs(OMEGA_L*delta_u_M_out-omega_r)) > 1e-5 
        ucTimes = ucTimes + 1;
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
    % Solve the problem with original primal ASM
    [delta_u_M_out_asm,~,iter,finalAS_right,failFlag] = asm(G,...
        invG,c,-OMEGA_L,-omega_r,x_ini,[],200);       
    iter_ASM = [iter_ASM;iter];
    
   if failFlag == 1 || norm(delta_u_M_out_asm-delta_u_M_out) > 1e-3
        failTimesASM = failTimesASM + 1;
        disp('ASM failes!');
        %error('ASM failes!');
    end
    
    %Phase I (Generate feasible starting point)
    x_ini = zeros(nu*M,1);
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        x_ini = linprog(zeros(nu*M,1),OMEGA_L,omega_r);
    end
    if max(OMEGA_L*x_ini-omega_r) > 1e-8
        error('Correction failed!')
    end
    % Solve the problem with ASM based on constraints selection
    [delta_u_M_out_asm_cs,~,iter,~,failFlag] = asm_cs_flight(G,...
        invG,c,-OMEGA_L,-omega_r,x_ini,[],200,ny,nu,M,P);
    iter_ASM_cs = [iter_ASM_cs;iter];
        
    diff = norm(delta_u_M_out_asm_cs-delta_u_M_out);
    if failFlag == 1 || diff > 1e-3
        failTimesNew = failTimesNew + 1;
        disp('ASM_cs fails.');
        %error('ASM_cs fails.');
    end
    diff_ASM_QUAD = [diff_ASM_QUAD;diff];
    
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
        
%     % The followings are used to do simulations
%     delta_u = delta_u_M_out(1:nu,1);
%     u_k = u_k + delta_u;
%     xm = Ad*xm + Bd*u_k;    % States updating
%     y_k = Cd*xm;            % Output updating
%     u_k_2 = u_k_1;
%     u_k_1 = u_k;
    
    % Records for drawing
    delta_u_draw(kk,:) = delta_u';
    u_draw(kk,:) = u_k';
    y_draw(kk,:) = y_k';          
    x_draw(1,kk) = x_k(1,1);x_draw(2,kk) = x_k(2,1);x_draw(3,kk) = x_k(3,1);x_draw(4,kk) = x_k(4,1);x_draw(5,kk) = x_k(5,1); 

end

maxIterASM = max(iter_ASM);
maxIterNew = max(iter_ASM_cs);
avgIterASM = mean(iter_ASM);
avgIterNew = mean(iter_ASM_cs);


% % Drawing
% figure;
% subplot(2,1,1); plot(y_draw(:,1),'LineWidth',2); title('y(k)');
% hold on; plot(y_draw(:,2),'LineWidth',2); 
% subplot(2,1,2); stairs(u_draw(:,1),'LineWidth',2);title('u(k)');
% hold on; stairs(u_draw(:,2),'LineWidth',2);
% figure; title('Iteration count')
% plot(iter_ASM); hold on; plot(iter_ASM_cs);
% legend('Original ASM','ASM with Constraints Selection');
% figure; title('Iteration count')
% plot(iter_ASM); hold on; plot(iter_ASM_ws);
% legend('Original ASM','ASM with Warm Start');

end
