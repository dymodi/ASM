% code used to debug asm.m
% 2016/1/2

clc;clear;

%load asmFail6

load asmFail7
%load newFail1

A = -OMEGA_L;
b = -omega_r;

maxIter = 300;
ndec = length(c);

% Phase I
x_ini = zeros(ndec,1);    % Use the solution of last MPC iteration as a guess of the initial value
if max(b-A*x_ini) > 1e-8
    x_ini = linprog(zeros(ndec,1),-A,-b);
end
if isempty(x_ini) || max(b-A*x_ini) > 1e-8   
    error('Correction failed!')   % Incase we do complete simulation
    %disp('Correction failed!');
end

[xStar, zStar, iterStar, finalAS] = asm(G,invG,c,A,b,x_ini,[],maxIter);
%[xStar, zStar, iterStar, finalAS] = asm_cs_flight(G,invG,c,A,b,x_ini,[],maxIter,nu,ny,M,P);
xQuad = quadprog(G,c,-A,-b);
diff = norm(xStar - xQuad);