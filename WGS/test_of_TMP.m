%% Test the WGS solver on aircraft model
% 2015/10/20, Yi
% Aircraft model is from MATLAB mpctoolbox demo, mpcaircraft
% MPC strategy is from Gionata Cimini

clc;clear
Nsim = 20;
r = zeros(6,Nsim);
for i = 1:Nsim
    r(1,i) = 0; r(2,i) = 0.4; r(3,i) = 0; r(4,i) = 8.5; r(5,i) = 0.3; r(6,i) = 6;
end

feasRes_QUAD = []; feasRes_Single = []; feasRes_Double = [];
diff_Single_QUAD = []; diff_Double_QUAD = [];
time_QUAD = []; time_Single = []; time_Double = [];
iter_QUAD = []; iter_Single = []; iter_Double = [];
u_Record = []; x_Record = []; y_Record = [];

load .\modelData\tmpModel

options.Algorithm='interior-point-convex';
options.MaxIter=1000;
options.TolCon=1.0000e-12; % default: 1e-8
options.TolFun=1.0000e-12; % default: 1e-8
options.TolX=1.0000e-12;   % default: 1e-8
options.Display='none';

%% Define Aircraft Model
% The linear open-loop dynamic model is as follows:
A = st.specs.model.A;
B = st.specs.model.B;
C = st.specs.model.C;
D = zeros(6,5);

%% Ini
x = zeros(7,1);
xkk = zeros(7,1);
u = [30;0.8;170;0.8;120];
y = [0;0.3;0;8;0.3;7];
y = y + [0.0260;0.1016;0.5676;0.5;0.1017;-0.3];

%% get info
[~,nu]=size(st.specs.model.B);
ny=size(st.specs.model.C,1);

for i = 1:Nsim
    
    y_Record = [y_Record,y];
    u_Record = [u_Record,u];
    x_Record = [x_Record,x];
    
    %% get info
    f = [u - st.specs.offset.u; y - st.specs.offset.y; r(:,i) - st.specs.offset.y];
    u0=f(1:nu);
    xkk1 = xkk;
    
    xkk = xkk1 + st.specs.kalman.M*(y - st.specs.offset.y - st.specs.model.C*xkk1);  % kalman
    
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
    
    u = zopt_QUAD(1:nu)+ u0 + st.specs.offset.u;
    
    xkk = st.specs.model.A * xkk1 + st.specs.model.B * (u-st.specs.offset.u) + st.specs.kalman.L*(y - st.specs.offset.y - st.specs.model.C*xkk1); % kalman
    
    x = A * x + B * u;
    y = C * x + D * u;
        
    
    disp(i);
end

figure;
subplot(2,1,1);plot(u_Record');title('TMP model,u');
subplot(2,1,2);plot(y_Record');title('TMP model,y');
figure; 
plot(diff_Single_QUAD,'-o');hold on;title('Difference between WGS and QUADPROG');
plot(diff_Double_QUAD,'-x');hold on;
legend('diff Single QUAD','diff Double QUAD');
figure; 
semilogy(time_Single,'-o');hold on;title('Runtime of WGS and QUADPROG');
semilogy(time_Double,'-x');hold on;
semilogy(time_QUAD);hold on;
legend('time Single','time Double','time QUAD');
figure; 
plot(iter_Single,'-o');hold on;title('Iterations of WGS and QUADPROG');
plot(iter_Double,'-x'); hold on;
plot(iter_QUAD);hold on;    
legend('iter Single','iter Double','iter QUAD');



