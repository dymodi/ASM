% code used to debug asm.m
% 2016/1/2

clc;clear;

%% Add the father path into the working directroy
currentDepth = 1; % get the supper path of the current path
currPath = fileparts(mfilename('fullpath')); % get current path
pos_v = strfind(currPath,filesep); 
father_p = currPath(1:pos_v(length(pos_v)-currentDepth+1)-1); 
% -1: delete the last character '/' or '\' 
addpath(father_p);

% %load asmFail6
% load dualFail1
% %load newFail1
% A = -OMEGA_L;
% b = -omega_r;
% maxIter = 300;
% ndec = length(c);

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

% % Test dual ASM solvers
% % G = [4,-2;-2,4];
% % c = [6;0];
% % A = [1,0;0,1;1,1];
% % b = [0;0;2];
% G = [2,0;0,2];
% c = [-2;-5];
% A = [1,0;0,1;1,-2;-1,-2;-1,2];
% b = [0;0;-2;-6;-2];
% [xStar_Prim, ~, iterStar_Prim, finalAS_Prim, ~] = asm(G,...
%     inv(G),c,A,b,[2;0],[2,5],100);
% [xStar_QUAD] = quadprog(G,c,-A,-b);
% [xStar_cs_new, zStar, iterStar_cs_new, finalAS, failFlag] = asm_cs_new(G,...
%     inv(G),c,A,b,[2;0],[2,5],100,[5]);
% % [xStar_Dual, iterStar, finalAS, failFlag] = asm_dual(G,inv(G),c,A,b,[],[],100);

% load ..\testData\dualcsFail1.mat
% [xStar, iterStar, finalAS, failFlag] = asm_dual_cs(H,invH,g,G,b,[],[],maxIter,ny,nu,M,P);

load D:\Users\Work\Documents\MATLAB\ASM\deleteConsFail1.mat
[w,consInfo,consInfoNum,hpW,lpW] = deleteCons(lambda,w,consInfo,consInfoNum,hpW,lpW);