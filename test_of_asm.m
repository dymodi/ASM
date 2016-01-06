% code used to debug asm.m
% 2016/1/2

clc;clear;

%load asmFail6
load dualFail1
%load newFail1
A = -OMEGA_L;
b = -omega_r;
maxIter = 300;
ndec = length(c);

% % Phase I
% x_ini = zeros(ndec,1);    % Use the solution of last MPC iteration as a guess of the initial value
% if max(b-A*x_ini) > 1e-8
%     x_ini = linprog(zeros(ndec,1),-A,-b);
% end
% if isempty(x_ini) || max(b-A*x_ini) > 1e-8   
%     error('Correction failed!')   % Incase we do complete simulation
%     %disp('Correction failed!');
% end
% 
% [xStar, zStar, iterStar, finalAS] = asm(G,invG,c,A,b,x_ini,[],maxIter);
% %[xStar, zStar, iterStar, finalAS] = asm_cs_flight(G,invG,c,A,b,x_ini,[],maxIter,nu,ny,M,P);
% xQuad = quadprog(G,c,-A,-b);
% diff = norm(xStar - xQuad);

% %% Tese equality constrained QP solvers
% G = [6,2,1;2,5,2;1,2,4];
% c = [-8;-3;-3];
% A = [1,0,1;0,1,1];
% b = [3;0];
% [xStar, zStar, iterStar] = eqp(G,inv(G),c,A,b,zeros(3,1),2);
% [xStar, zStar] = eqp_ns(G,c,A,b,zeros(3,1),[3;1]);

% Test dual ASM solvers
% G = [4,-2;-2,4];
% c = [6;0];
% A = [1,1;0,1;1,0];
% b = [1.5;0;0];
% G = [2,0;0,2];
% c = [-2;-5];
% A = [1,0;0,1;1,-2;-1,-2;-1,2];
% b = [0;0;-2;-6;-2];
[xStar_Prim, zStar_Prim, iterStar_Prim, finalAS_Prim, ~] = asm(G,...
    inv(G),c,A,b,zeros(4,1),[],100);
[xStar_QUAD] = quadprog(G,c,-A,-b);
[xStar, iterStar, finalAS, failFlag] = asm_dual(G,inv(G),c,A,b,[],[],100);