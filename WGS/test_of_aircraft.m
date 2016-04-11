%% Test the WGS solver on aircraft model
% Oct. 20, Yi
% Aircraft model is from MATLAB mpctoolbox demo, mpcaircraft
% MPC strategy is from Gionata Cimini

clc;clear
Nsim = 200;
r1 = zeros(Nsim,1);
r2 = zeros(Nsim,1);
for i = 81:Nsim
    r1(i) = 0.1;
end
for i = 21:Nsim
    r2(i) = 10;
end

feasRes_QUAD = []; feasRes_Single = []; feasRes_Double = [];
diff_Single_QUAD = []; diff_Double_QUAD = [];
time_QUAD = []; time_Single = []; time_Double = [];
iter_QUAD = []; iter_Single = []; iter_Double = [];
u_Record = []; x_Record = []; y_Record = [];

load .\modelData\aircraftModel

options.Algorithm='interior-point-convex';
options.MaxIter=1000;
options.TolCon=1.0000e-12; % default: 1e-8
options.TolFun=1.0000e-12; % default: 1e-8
options.TolX=1.0000e-12;   % default: 1e-8
options.Display='none';

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
disPlant = c2d(plant,0.05);
A = disPlant(1,1).a;
B(:,1) = disPlant(1,1).b;
B(:,2) = disPlant(1,2).b;

%% Ini
x = zeros(4,1);
xkk = zeros(6,1);
u = zeros(2,1);
y = zeros(2,1);

%% get info
[~,nu]=size(st.specs.model.B);
ny=size(st.specs.model.C,1);

for i = 1:Nsim
    %% get info
    f = [u;y;r1(i);r2(i)];
    u0=f(1:nu);
    xkk = xkk + st.specs.kalman.M*(y-st.specs.model.C*xkk);  % kalman
    
    %% solver
    p = [f(1:nu); xkk; f(ny+nu+1:2*ny+nu)];
    b = st.mat.parametric.S * p + st.mat.parametric.s;
    h = st.mat.parametric.F * p;
    
    tic
    [zopt_QUAD,~,~,outputs]=quadprog(st.mat.H, h, st.mat.G,b,[],[],[],[],[],options); % solve the optimal control problem
    tQUAD = toc;
    [zopt_Single,tSingle,itSingle] = wgsSolver(st.mat.H,h,-st.mat.G,-b,[],[],[],[],[],1);
    [zopt_Double,tDouble,itDouble] = wgsSolver(st.mat.H,h,-st.mat.G,-b,[],[],[],[],[],2);
    
    %%  Record
    diff_Single_QUAD = [diff_Single_QUAD;norm(zopt_QUAD-zopt_Single)];
    diff_Double_QUAD = [diff_Double_QUAD;norm(zopt_QUAD-zopt_Double)];
    time_QUAD = [time_QUAD;tQUAD];
    time_Single = [time_Single;tSingle];
    time_Double = [time_Double;tDouble];
    iter_QUAD = [iter_QUAD;outputs.iterations];
    iter_Single = [iter_Single;itSingle];
    iter_Double = [iter_Double;itDouble];
    feasRes_QUAD = [feasRes_QUAD,st.mat.G*zopt_QUAD - b];
    feasRes_Single = [feasRes_Single,st.mat.G*zopt_Single - b];
    feasRes_Double = [feasRes_Double,st.mat.G*zopt_Double - b];
    
    u = zopt_QUAD(1:nu)+u0;
    
    xkk = st.specs.model.A * xkk + st.specs.model.B * u + st.specs.kalman.L*(y-st.specs.model.C*xkk); % kalman
    
    x = A * x + B * u;
    y = C * x + D * u;
    
    u_Record = [u_Record,u];
    x_Record = [x_Record,x];
    y_Record = [y_Record,y];
    
    disp(i);
end

figure;
subplot(2,1,1);plot(u_Record');title('Aircraft,u');
subplot(2,1,2);plot(y_Record');title('Aircraft,y');
figure; 
plot(diff_Single_QUAD,'-o');hold on;title('Difference between WGS and QUADPROG');
plot(diff_Double_QUAD,'-x');hold on;
legend('diff Single QUAD','diff Double QUAD');
figure; 
semilogy(time_Single,'-o');hold on; title('Runtime of WGS and QUADPROG');
semilogy(time_Double,'-x');hold on;
semilogy(time_QUAD);hold on;
legend('time Single','time Double','time QUAD');
figure; 
plot(iter_Single,'-o');hold on;    title('Iterations of WGS and QUADPROG');
plot(iter_Double,'-x');hold on;
plot(iter_QUAD); hold on;
legend('iter Single','iter Double','iter QUAD');



