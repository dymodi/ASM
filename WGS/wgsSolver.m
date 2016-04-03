%% An implementation of WGS method to solve convex QP problems in C code
% Please refer to the article:
% A WEIGHTED GRAM-SCHMIDT METHOD FOR CONVEX QUADRATIC PROGRAMMING
% This m-function solves the following convex QP prroblem:
% minimize 0.5*x'*H*x + f'*x   subject to:
% subject to lx <= x <= ux, AAx >= lg
% The frame of the active-set method comes from Chapter 16 of the book:
% NUMERICAL OPTIMIZATION, 2006

% Varaibles declarations:
% ndec: number of decision variables
% ngc: number of general constraints
% nbc: number of bound constraints
% boxIndex: the index of variables for box constraints
% x0: feasible starting point (ndec * 1) (can be empty) 
% wf_out: suitable working set for bound constraints (can be empty) 
% wl_out: suitable working set for general constraints (can be empty)
% Note that items in wf_out should be rang between 1 and 2*nbc
% 1 to nbc stands for lower bound, nbc+1 to 2*nbc stands for upper bound
% precisionFlag == 1 means single precision, precisionFlag == 2 means double

function [z, time, iter] = wgsSolver(H, f, AA, lg, lx_out, ux_out, x0, wf_out, wl_out, precisionFlag)


if isempty(AA)
    ndec = length(f);
    AA = zeros(1,ndec);
    lg = -1;    
end

maxIter = int32(200);
[ngc,ndec] = size(AA);
if length(lx_out)~=length(ux_out)
        error('lx and ux must have the same size.');
end
if ~isempty(lx_out)
    if (ndec~=length(lx_out) || ndec ~=length(ux_out))
        error('Length of lx, ux must be the same as x.');
    end
end

boxIndex = [];
lx = [];
ux = [];
for i = 1:length(lx_out)
    if lx_out(i) ~= -Inf || ux_out(i) ~= Inf
        lx = [lx;lx_out(i)];
        ux = [ux;ux_out(i)];
        boxIndex = [boxIndex;i];
    end
end

nbc = length(boxIndex);

% Here we reorder the parameters so that the first nbc elements has bound constraints
outOrd = 1:ndec;
for i=1:nbc
    index = boxIndex(i);
    tmpH = H(i,:);  H(i,:) = H(index,:);    H(index,:) = tmpH;
    tmpH = H(:,i);  H(:,i) = H(:,index);    H(:,index) = tmpH;
    tmpf = f(i);    f(i) = f(index);        f(index) = tmpf;
    tmpA = AA(:,i); AA(:,i) = AA(:,index);  AA(:,index) = tmpA;
    tmp = outOrd(i);outOrd(i) = outOrd(index);outOrd(index) = tmp;
end
if ~isempty(x0)
    for i=1:nbc
        tmpx = x0(i);   x0(i) = x0(index);      x0(index) = tmpx;
    end
end

% Here we check whether the intial x is feasible with given constraints
x0FsbFlg = 1;
if (~isempty(x0))
    if min(AA*x0-lg) < -1e-8
        x0FsbFlg = 0;
    end
    for i = 1:nbc
        if x0(i) < lx(i)-0.0000001 || x0(i) > ux(i)+0.0000001
            x0FsbFlg = 0;
        end
    end
end

if (isempty(x0) || x0FsbFlg == 0)
    %disp('x0 not given or is infeasible, try to do correction');
    opt.Display='off';
    %opt.Algorithm='active-set';
    x0 = linprog(zeros(ndec,1),-AA,-lg,[],[],[lx;-inf*ones(ndec-nbc,1)],[ux;inf*ones(ndec-nbc,1)],[],opt);
%     fprintf('x0\n'); disp(x0);
%     fprintf('AA\n'); disp(AA);
%     fprintf('lg\n'); disp(lg);
    if min(AA*x0-lg) < -1e-8
        error('Correction failed, Please offer a feasible starting point!');
    end
    for i = 1:nbc
        if x0(i) < lx(i)-0.0000001 || x0(i) > ux(i)+0.0000001
            error('Correction failed, Please offer a feasible starting point!');
        end
    end    
end

% Working set is set to be empty if the given starting point is infeasible
if (x0FsbFlg == 0)
    wf_out = [];
    wl_out = [];
end

% Here we check whether the initial x accords with the initial working set
wsFsbFlg = 1;
for i = 1:length(wf_out)
    consIndex = wf_out(i);
    if consIndex <= nbc
        if abs(x0(consIndex) - lx(consIndex)) > 0.0000001
            wsFsbFlg = 0;
        end
    elseif consIndex <= 2*nbc
        if abs(x0(consIndex-nbc) - ux(consIndex-nbc)) > 0.0000001
            wsFsbFlg = 0;
        end
    else
        error('Wrong constraint number in working set!');
    end        
end
for i = 1:length(wl_out)
    consIndex = wl_out(i);
    if abs(AA(consIndex,:)*x0 - lg(consIndex)) > 0.0000001
        wsFsbFlg = 0;        
    end
end
if wsFsbFlg == 0
    error('Initial x0 does not fit with initial working set, Please check!');
end

nf = length(wf_out);
ml = length(wl_out);
wf = int32(zeros(ndec,1));
wl = int32(zeros(ndec,1));
for i = 1:nf
    wf(i) = wf_out(i);
end
for i = 1:ml
    wl(i) = wl_out(i);
end

%% -inf and inf processing
Maxmium = 1e10;             % need to be check!
for i = 1:nbc
    if lx(i) == -inf
        lx(i) = -Maxmium;
    end
    if ux(i) == inf
        ux(i) = Maxmium;
    end        
end

if nbc == 0
    lx =  -Maxmium;
    ux = Maxmium;
    nbc = 1;
end


%% Memoray allocation for C code
largeSize = max([ndec,ngc])+1;
orderPermu = int32(zeros(ndec,1));
H_ori = zeros(ndec,ndec);
c_ori = zeros(ndec,1);
AA_c = [];
for i=1:ngc
    AA_c = [AA_c;AA(i,:)'];
end
Af = zeros(ndec,nbc);
Lv = zeros(ndec,ndec);
Yv = zeros(ndec,ndec);
Rv = zeros(ndec,ndec);
pvStar = zeros(ndec,1);
p = zeros(ndec,1);
gx = zeros(ndec,1);
isInWl = int32(zeros(ngc,1));
uv = zeros(ndec,1);
vl = zeros(ndec,1);
wv = zeros(ndec,1);
lambdal = zeros(ndec,1);
lambdaf = zeros(nbc,1);
lambda = zeros(ndec,1);
P_c = zeros(ndec,ndec);
G_c = zeros(2,2);
tmpVec1 = zeros(largeSize,1);
tmpVec2 = zeros(ndec,1);
tmpMat1 = zeros(ndec,ndec);
tmpMat2 = zeros(ndec,ndec);
tmpMat3 = zeros(ndec,ndec);
tmpMat4 = zeros(ndec,ndec);
tmpMat5 = zeros(ndec,ndec);
tmpMat6 = zeros(ndec,ndec);
iter = int32(zeros(1,1));
nf = int32(nf);
ml = int32(ml);
x = zeros(ndec,1);
for i = 1:ndec
    x(i) = x0(i);
end
if precisionFlag == 1
    H_ori = single(H_ori);
    c_ori = single(c_ori);
    Af = single(Af);
    Lv = single(Lv);
    Yv = single(Yv);
    Rv = single(Rv);
    pvStar = single(pvStar);
    p = single(p);
    gx = single(gx);
    uv = single(uv);
    vl = single(vl);
    wv = single(wv);
    lambdal = single(lambdal);
    lambdaf = single(lambdaf);
    lambda = single(lambda);
    P_c = single(P_c);
    G_c = single(G_c);
    tmpVec1 = single(tmpVec1);
    tmpVec2 = single(tmpVec2);
    tmpMat1 = single(tmpMat1);
    tmpMat2 = single(tmpMat2);
    tmpMat3 = single(tmpMat3);
    tmpMat4 = single(tmpMat4);
    tmpMat5 = single(tmpMat5);
    tmpMat6 = single(tmpMat6);
    x = single(x);
end

tic
if precisionFlag == 1
    [xStar,iter] = wgsQPMEX(single(H),single(f),single(AA_c),...
        single(lg),single(lx),single(ux),wf,wl,single(x), ...
        orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv, ...
        pvStar, p, gx, isInWl,uv,vl,wv, ...
        lambdal,lambdaf,lambda, P_c,G_c, ...
        tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6, nf, ml, iter, maxIter);
elseif precisionFlag == 2
    [xStar,iter] = wgsQPMEX_double(H,f,AA_c,lg,lx,ux,wf,wl,x, ...
        orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv, ...
        pvStar, p, gx, isInWl,uv,vl,wv, ...
        lambdal,lambdaf,lambda, P_c,G_c, ...
        tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6, nf, ml, iter, maxIter);
else
    error('Wrong precisionFlag!');
end
time = toc;

z = zeros(ndec,1);
% Recover x
for i=1:ndec
    z(outOrd(i)) = xStar(i);    
end

end







