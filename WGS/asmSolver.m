%% An implementation of ASM to solve convex QP problems in C code
% ASM algorithm according to the MATLAB version, which refers to the book
% NUMERICAL OPTIMIZATION
% This m-function solves the following convex QP prroblem:
% minimize 0.5*x'*H*x + c'*x   subject to: Ax >= b

function [z, time, iter] = asmSolver(H, c, A, b, x0, w, precisionFlag)

maxIter = int32(100);
[mc,ndec] = size(A);
invH = inv(H);
wSize = length(w);
x = zeros(ndec,1);
for i = 1:ndec
    x(i) = x0(i);
end

% At current stage, we require that a feasible starting point x0
if isempty(x)
    error('Empty starting point. Feasible starting point require.');
end
if min(A*x-b) < 0
    error('Infeasible starting point. Feasible starting point require.');
end

% Check initial working set
if ~isempty(w)
    for i = 1: wSize
        if max(abs(A(w(i),:)*x-b(w(i)))) > 0.0001
            error('Wrong initial working set.');
        end
    end
end

% At current stage, we only have double precision version
if precisionFlag ~= 2
    error('Wrong precision!');
end

%% Memoray allocation for C code
largeSize = max([ndec,mc])+1;
H_ori = zeros(ndec,ndec);
invH_ori = zeros(ndec,ndec);
c_ori = zeros(ndec,1);
Aw = zeros(ndec+1,ndec+1);
bw = zeros(ndec+1,1);
lambda = zeros(ndec,1);
p = zeros(ndec,1);
gx = zeros(ndec,1);
tmpVec1 = zeros(largeSize,1);
tmpVec2 = zeros(largeSize,1);
tmpMat1 = zeros(ndec+1,ndec+1);
tmpMat2 = zeros(ndec,ndec);
tmpMat3 = zeros(ndec,ndec);
tmpMat4 = zeros(ndec,ndec);
iter = int32(zeros(1,1));
w_c = int32(zeros(ndec,1));
for i = 1:wSize
    w_c(i) = w(i);
end

tic
if precisionFlag == 2
    [z,iter] = asmMEX_double(H,invH,c,A',b,x,w_c,wSize,Aw,bw,H_ori,invH_ori,c_ori,...
                      p,gx,lambda,tmpVec1,tmpVec2,tmpMat1,tmpMat2,tmpMat3,...
                      tmpMat4,iter,maxIter);
end
time = toc;

end