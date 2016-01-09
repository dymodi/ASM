%% An implementation of WGS method to solve convex QP problems
% Please refer to the article: A WEIGHTED GRAM-SCHMIDT METHOD FOR CONVEX QUADRATIC PROGRAMMING
% This m-function solves the following convex QP prroblem:
% minimize c^T*x + 1/2*x^T*H*x
% subject to lx <= x, x <= ux, AAx >= lg
% The frame of the active-set method comes from Chapter 16 of the book:
% NUMERICAL OPTIMIZATION, 2006
% 
% August 20th, 2015

%% Matrix dimension 
% H:  ndec*ndec;    % ndec = nv + nf;    
% Hv: nv*nv;
% Hf: nf*nf;
% R:  ndec*ndec;
% Rv: nv*nv;
% Rf: nf*nf;
% A:  ml*ndec;
% Av: ml*nv;
% Af: ml*nf;
% Lv: ml*ml;
% Yv: nv*ml;
% gx: ndec*1;
% gv: nv*1;
% gf: nf*1;
% uv: nv*1;
% wv: nv*1;
% vl: ml*1;

%clc;clear;
% 
% %% Test data
% %Data1  
% H = [ 4.5267, -3.9095,  0.6937, -7.1302,  1.2138, -0.9079;
%      -3.9095, 42.3583, -7.1494, 11.0149, -1.0405,  0.7782;
%       0.6937, -7.1494,  3.3094, -2.8661,  0.3464, -0.2591;
%      -7.1302, 11.0149, -2.8661, 41.4638, -6.8516,  5.1248;
%       1.2138, -1.0405,  0.3464, -6.8516,  3.2103, -0.9053;
%      -0.9079,  0.7782, -0.2591,  5.1248, -0.9053,  2.6771];
% c = [16.8930; -53.6424; 9.4920; -47.2980; 7.3800; -5.5200];
% lx= [-2;-2;-2;-2;-2;-2];
% ux= [2;2;2;2;2;2];
% lg = [-3;-3;-3;-3;-3;-3];
% nbc = length(lx);
% AA = [%-0.2460,  0.1840,  0,       0,       0,       0;
%     -1,  1,  0,       0,       0,       0;
%     -0.0704,  1.3926, -0.2460,  0.1840,  0,       0;
%     -0.2467,  0.2115, -0.0704,  1.3926, -0.2460,  0.1840;
%     %0.2460, -0.1840,  0,       0,       0,       0;
%     1, -1,  0,       0,       0,       0;
%     0.0704, -1.3926,  0.2460, -0.1840,  0,       0;
%     0.2467, -0.2115,  0.0704, -1.3926,  0.2460, -0.1840];
% wf = [7];
% wl = [1];
% nf = 1;
% ml = 1;
% %x = [0;0;0;0;2;2];
% x = [2;-1;0;0;0;0];

% %Data2
% H = [ 7,    8.2,  8.7, 7;
%       8.2,  9.8, 10.2, 8;
%       8.7, 10.2, 11.7, 9;
%       7,    8,    9,  10];
% c = [1;1;2;3];
% lx= [-4;-4;-4;-4];
% ux = [4;4;4;4];
% lg = [2;-3];
% nbc = length(lx);
% AA = [1,1,0,0;0,1,0,1];
% wf = [3];
% wl = [1,2];
% nf = 1;
% ml = 2;
% x = [2;0;-4;-3];
% 
% %Data3
% H = [ 7,    8.2,  8.7, 7;
%       8.2,  9.8, 10.2, 8;
%       8.7, 10.2, 11.7, 9;
%       7,    8,    9,  10];
% c = [1;1;2;3];
% lx = [-4;-4;-4;-4;];
% ux = [4;4;4;4];
% lg = [2;1];
% nbc = length(lx);
% AA = [1,1,0,0;1,0,1,0];
% wf = [4];
% wl = [];
% nf = 1;
% ml = 0;
% x = [3;0;0;-4]; % 正确的测试初始值
% % x = [3;0;0;-3]; % 测试Error用的错误初值

% %Data 4~5
% load failedData1
% %load failedData2
% %load failedData3
% %load failedData4
% %load failedData5
% H = H_ori;
% c = c_ori;
% x = x_ori;
% wf = [];
% wl = [];
% nf = 0;
% ml = 0;

% %C failed data 1 & 2 and wgs fail data
% load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\CfailedData1.mat');
% % load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\CfailedData2.mat');
% % load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\wgsFailData1.mat');
% % load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\wgsFail1.mat');
% wf = [];
% wl = [];
% nf = 0;
% ml = 0;
% nbc = length(lx);

% % API and wgs failed data 1 and wgs fail data
% load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\apiFail1.mat');
% wf = [];
% wl = [];
% nf = 0;
% ml = 0;
% c = f;

%% API declaration
% It is required that the H is ordered that last nf variables are fixed
% wf is the initial working set for bound constraints
% wl is the initial working set for general constraints
% nf is the number of the bound constraints
% wl is the number of the general constraints

function [xStar,iter] = wgsQP(H,c,AA,lx,ux,lg,wf,wl,nf,ml,x)
alpha = [];
lub = [lx;ux];
nbc = length(lub)/2;
% Parameters setting
maxIter = 1000;

[ngc,ndec] = size(AA);
nv = ndec - nf;

% Here we check whether the intial x is feasible with given constraints
for i = 1:nbc
    if x(i) < lx(i)-0.000001 || x(i) > ux(i)+0.000001
        error('Initial x infeasible with bound constraint!');
    end
end
if min(AA*x - lg) < -0.000001
    error('Initial x infeasible with general constraint!');
end

% Here we check whether the initial x accords with the initial working set
for i = 1:length(wf)
    consIndex = wf(i);
    xIndex = mod(consIndex,ndec);
    if xIndex == 0
        xIndex = ndec;
    end
    if x(xIndex) ~= lub(consIndex)
        error('Initial x does not fit with initial working set! (Bound constraint)');
    end
end
for i = 1:length(wl)
    consIndex = wl(i);
    if AA(consIndex,:)*x ~= lg(consIndex)
        error('Initial x does not fit with initial working set! (General constraint)');
    end
end

% variables
orderPermu = 1:ndec;
orderPermu = orderPermu';             % orderPermu 采用手动调换而不是乘以PiGlobal的方式来进行更新，为后续彻底告别PiGlobal做准备。 ——8月20日 代码优化时注
H_ori = H;                      % H 的备份，用来检验针对 H 的 permute 是否正确进行
c_ori = c;

% 如果给的 bound constraint 对应的 x 不再靠后 nf 个位置上，在这里需要把它们调整到相应的位置上去
% If the last nf items of x is not according with the initial bound constraints
% we should adjust it to meet the requirement of the algorithm
for i = 1:length(wf)
    boundIndex = wf(i);
    fixedIndex = mod(boundIndex,ndec);
    if fixedIndex==0
        fixedIndex = ndec;
    end
    fixedPos = nv+1;
    if fixedIndex <= nv  % means the fixed item of x is in the first nv rows, needs adjustment                
        orderPermu = swapVec(orderPermu,fixedPos,fixedIndex);
        H = swapMat(H,fixedPos,fixedIndex);        
    end
end

gx = permut(c_ori + H_ori*x, orderPermu, ndec, 1);

%------------------Check the rightness of input parameter------------------
if length(wf) ~= nf
    error('Fixed constraints number error!');
end
if length(wl) ~= ml
    error('General constraints number error!');
end
%--------------------------------------------------------------------------

isInWl = zeros(ngc,1);
for i = 1:ml
    isInWl(wl(i)) = 1;
end

nv = ndec - nf;

Hv = H(1:nv,1:nv);
R = chol(H);        % Cholesky factorization
Rv = R(1:nv,1:nv);                       


%% Compute pStar for the first iteration
Yv = [];
Lv = [];
A  = [];
if ml == 0  % ml == 0 means there is no general constraints
    gv = gx(1:nv,:);
    pvStar = linsolve(Hv,-gv);
    
    %test = fowSubL(Rv,-gv,1);            
    p = [pvStar;zeros(nf,1)];    
    p = permutReco(p,orderPermu,ndec,1);  
else
    % A consists of the general constraints in the current working set
    for i = 1:ml        
        a = permut(AA(wl(i),:)', orderPermu, ndec, 1);
        A = [A;a'];        
    end
    
    Av = A(:,1:nv);
    Af = A(:,nv+1:ndec);
    
    % Inverse Rv and QR factorize Av
    invRv = inv(Rv);
    AinvR = Av*invRv;
    %[Qtmp,Rtmp] = qr(AinvR');   % To achieve WGS factorization
    [Qtmp,Rtmp] = gs_m(AinvR');   % To achieve WGS factorization
    Yv = Qtmp(:,1:ml);
    Lv = Rtmp(1:ml,:)';
    
    % Initial value of auxiliary vectors
    gv = gx(1:nv,:);
    uv = linsolve(Rv',gv);
    vl = Yv'*uv;
    wv = Yv*vl-uv;
    pvStar = linsolve(Rv,wv);
    p = [pvStar;zeros(nf,1)];   
    p = permutReco(p,orderPermu,ndec,1);  
end

% 从计算得到p开始每周期的迭代
% Iteration start!
for iter = 1:maxIter
    
    if iter == maxIter
        error('Maximum iteration reached!');
    end
        
    %% Decide the changes in the working set according to pStar
    %if (isZero(p,5e-4) == 1)         % 5e-4 for diffcult problems   % Check whether pStar is zero vector
    if (isZero(p,5e-6) == 1)          % 5e-6 for normal problems  % Check whether pStar is zero vector                
        gf = gx(nv+1:ndec,:);
        if ml == 0            
            lambdaf = zeros(nf,1);
            % 因为自己的命题和论文中的命题形式不同，区别主要在 lub 的构成上
            % 所以这里需要加一部来对 lub 对应的 gf 的后半部分变号
            for i = 1:nf
                if wf(i) <= nbc
                    lambdaf(i) = gf(i);
                else
                    lambdaf(i) = -gf(i);
                end
            end            
            lambdal = [];
            lambda = [lambdaf;lambdal];
        else
            lambdal = linsolve(Lv',vl);           
            K = H(1:nv,nv+1:ndec);            
            lambdaf = gf + K'*pvStar - Af'*lambdal;         % A 的更新是以 Av 和 Af 的分别更新来实现的           
            % 因为自己的命题和论文中的命题形式不同，区别主要在 lub 的构成上
            % 所以这里需要加一部来对 lub 对应的 gf 的后半部分变号
            for i = 1:nf
                if wf(i) > nbc
                   lambdaf(i) = -lambdaf(i);
                end
            end
            lambda = [lambdaf;lambdal];
        end
        if ((isempty(wf) && isempty(wl)) || min(lambda) >= 0)     % Final solution reached
            xStar = x;
            %finalAS = w;
            break;      % Quit iteration from here
        else
            minlambdal = min(lambdal);
            minlambdaf = min(lambdaf);         
            if (isempty(lambdal) || (~isempty(lambdaf) && minlambdaf < minlambdal))
                %% Delete a bound constraint
                [~,index] = min(lambdaf);
                indexJ = mod(wf(index),nbc);
                if indexJ == 0
                    indexJ = nbc;
                end
                indexJ = find(orderPermu==indexJ);
                wf(index) = wf(1);
                wf(1) = [];
                % Other updates can be implemented here ...
                if indexJ <= nv
                    error('Bound constraints must be in last nf rows');
                end
                % 这里要更新H，肯定就是要把被删的 fixed constraint 对应的 x 从后 nf 提到前 nv 中                         
                orderPermu = swapVec(orderPermu,indexJ,nv+1);
                H = swapMat(H,indexJ,nv+1);      
                gx = swapVec(gx,indexJ,nv+1);                
                                
                h = H(nv+1,1:nv)';
                eta = H(nv+1,nv+1);
                r = linsolve(Rv',h);
                rau = (eta-r'*r)^(1/2);
                Rv = [Rv,r;zeros(1,nv),rau];
                Hv = Rv'*Rv;                                  
                
                nv = nv + 1;
                nf = nf - 1;                                
                
                if ml == 0
                    if (~isempty(wl))
                        error('Working set error!');
                    end
                    %----注意这里在更新Av的时候顺便把A也更新一下，用于在后面校验Af----
                    Av = [];Af = [];wl = [];
                    Yv = [];Lv = [];A = [];                 
                    gv = gx(1:nv,:);
                    pvStar = linsolve(Hv,-gv);
                    p = [pvStar;zeros(nf,1)];                    
                    p = permutReco(p,orderPermu,ndec,1);  
                else
                    % Update Lv, Yv, Af, Av;
                    ev1 = zeros(nv,1);
                    ev1(nv,:) = 1;
                    q = linsolve(Rv,ev1);
                    a = Af(:,indexJ-nv+1);
                    Af(:,indexJ-nv+1) = Af(:,1);
                    Af(:,1) = [];
                    Av_bar = [Av,a];
                    v = Av_bar * q;
                    Av = Av_bar;
                    
                    % Updates
                    uv_tilde = uv + alpha*wv;
                    gamma = gx(nv,:);
                    mu = (gamma - r'*uv_tilde)/rau;
                    uv_bar = [uv_tilde;mu];                    
                    vl_barv = [vl;mu];                    
                    LvvP = [Lv,v];
                    YvP = [Yv,zeros(nv-1,1);zeros(1,ml),1];               
                    for i = 1:ml                        
                        G = myplanerot([LvvP(i,i);LvvP(i,ml+1)]);
                        LvvP = colRot(LvvP,G,i,ml+1);
                        YvP  = colRot(YvP,G,i,ml+1);
                        vl_barv = rowRot(vl_barv,G,i,ml+1);
                    end
                    Lv = LvvP(:,1:ml);
                    Yv = YvP(:,1:ml);
                    z_bar = YvP(:,ml+1);
                                        
                    % Test Code 先删除
                    if max(max(abs(Lv*Yv'*Rv-Av))) > 0.0000001
                        error('Update error!');
                    end                                                             

                    vl_bar = vl_barv(1:ml,:);
                    v = vl_barv(ml+1,:);
                    wv_bar = [(1-alpha)*wv;0]-v*z_bar;
                    % Update
                    uv = uv_bar;
                    vl = vl_bar;
                    wv = wv_bar;
                    pvStar = linsolve(Rv,wv);
                    p = [pvStar;zeros(nf,1)];                    
                    p = permutReco(p,orderPermu,ndec,1);  
                end               
                
            else
                %% Delete a general constraint
                [~,index] = min(lambdal);                
                % 这种更新方法认为Av的后续行也会受到影响
                isInWl(wl(index)) = 0;
                wl(index) = [];
                
                ml = ml - 1;
                if ml == 0          % There will be no general constraints in the working set
                    if (~isempty(wl))
                        error('Working set error!');
                    end
                    Av = [];Af = [];wl = [];
                    Yv = [];Lv = [];A = [];
                    gv = gx(1:nv,:);
                    pvStar = linsolve(Hv,-gv);
                    p = [pvStar;zeros(nf,1)];
                    p = permutReco(p,orderPermu,ndec,1);
                else                                       
                    Lv_tilde = Lv;
                    Lv_tilde(ml+1,:) = Lv(index,:);
                    Lv_tilde(index:ml,:) = Lv(index+1:ml+1,:);
                    YP = Yv;
                    for i = 0:ml+1 - index -1
                        G = myplanerot([Lv_tilde(index+i,index+i);Lv_tilde(index+i,index+1+i)]);
                        Lv_tilde = colRot(Lv_tilde,G,index+i,index+1+i);
                        vl = rowRot(vl,G,index+i,index+1+i);
                        YP = colRot(YP,G,index+i,index+1+i);
                    end
                    v = vl(ml+1,:);
                    vl = vl(1:ml,:);
                    Lv =  Lv_tilde(1:ml,1:ml);
                    Yv = YP(:,1:ml);
                    z_bar = YP(:,ml+1);
                    uv = uv + alpha * wv;
                    wv = (1-alpha)*wv - v*z_bar;
                                                           
                    % Update Av and Af
                    Av(index,:) = [];
                    Af(index,:) = [];
                    A(index,:) = [];            %  这个更新不必要，只是用于在后面校验Af；
                    
                    % Test Code 先删除
                    % Check
                    if max(max(abs(Av-Lv*Yv'*Rv))) > 0.0005
                        disp('Av or Lv update fails');
                        disp(max(max(abs(Av-Lv*Yv'*Rv))));
                        %error('Av or Lv update fails');
                    end                    
                    % Compute p for the next iteration
                    pvStar = linsolve(Rv,wv);
                    p = [pvStar;zeros(nf,1)];
                    p = permutReco(p,orderPermu,ndec,1);
                end
                
            end
        end
        
    else
        %% Calculate alpha
        % Note that here I did not keep the active constaint out for convenience
        alpha = 1;
        addBoundConstraint = 0;
        addGeneralConstraint = 0;   % 这里我们没有把在working set里的约束配排除
        for i = 1:nbc       % 在这里通过依次查验的方法确定一个合适的alpha值
            if p(i) < 0
                tmpAlpha = (lub(i)-x(i))/p(i);
                if tmpAlpha < alpha
                    alpha = tmpAlpha;
                    addBoundConstraint = 1;
                    boundIndex = i;
                end
            end
        end
        for i = nbc+1 : nbc*2
            if p(i-nbc) > 0
                tmpAlpha = (lub(i)-x(i-nbc))/p(i-nbc);
                if tmpAlpha < alpha
                    alpha = tmpAlpha;
                    addBoundConstraint = 1;
                    boundIndex = i;
                end
            end
        end
        % 也就是说，这个时候如果 alpha 已经很接近 0 了，那么就考虑去掉一条 
        % bound 约束，不用在后面再判断要不要去掉 general 约束了            
        if alpha > 0.000000001     
            for i = 1:ngc
                if isInWl(i) == 0
                    ap = AA(i,:)*p;
                    if (ap < 0)
                        tmpAlpha = (lg(i)-AA(i,:)*x)/ap;                                                             
                        if (tmpAlpha < alpha+0.0000001)
                            alpha = tmpAlpha;
                            addGeneralConstraint = 1;
                            addBoundConstraint = 0;
                            generalIndex = i;
                        end
                        %fprintf('ap(%d): %f  tmpAlpha: %f  alpha: %f  \n',i,ap,tmpAlpha,alpha);
                        if alpha < 0.000000001      % 如果 alpha 很接近 0 了，就退出
                            break;                          
                        end
                    end
                    
                end
            end            
        end
        
        alpha = max([0,min([1,alpha])]);
        x = x + alpha * p;
        gx = permut(c_ori + H_ori*x, orderPermu, ndec,1);                       
        
        if (alpha < 1)
            if (addBoundConstraint == 1) && (addGeneralConstraint ==0)
               %% Adding a bound constraint
                wf = [boundIndex;wf];   % wf 内约束index的排列需要注意
                % Other updates ...                
                indexJ = mod(boundIndex,nbc);
                if indexJ == 0
                    indexJ = nbc;
                end                
                indexJ = find(orderPermu == indexJ);                
                tmpS = (swapVec((Rv)',indexJ,nv))';
                Q = eye(nv,nv);
                for i = 1:nv-indexJ-1
                    G = myplanerot([tmpS(nv,indexJ);tmpS(nv-i,indexJ)]);   
                    tmpS = rowRot(tmpS,G,nv,nv-i);
                    Q = rowRot(Q,G,nv,nv-i);                                                                                                                                                                               
                end
                for i = 1: nv - indexJ               
                    G = myplanerot([tmpS(i+indexJ-1,i+indexJ-1);tmpS(nv,i+indexJ-1)]);                                     
                    tmpS = rowRot(tmpS,G,i+indexJ-1,nv);
                    Q = rowRot(Q,G,i+indexJ-1,nv);                 
                end
               
                Rv_hat = (swapVec((Q*Rv)',indexJ,nv))';
                orderPermu = swapVec(orderPermu,indexJ,nv);
                H = swapMat(H,indexJ,nv);        
                gx = swapVec(gx,indexJ,nv);
                Rv = Rv_hat(1:nv-1,1:nv-1);  
                Hv = H(1:nv-1,1:nv-1);     % 这里 Hv 好像不用更新，后期可以考虑删掉
                             
%                 % Test Code 先删除，看下跑得时间怎么样
%                 %%----------------------Test Code--------------------------
%                 if (origin'*H_ori*origin-orderPermu'*H*orderPermu) > 0.0000001
%                     error('Permute on Hv failed!')
%                 end
%                 if max(max(abs(Rv-chol(Hv)))) >0.0000001
%                     error('Rv is not the cholesky factorization of Hv?')
%                 end
%                 %%---------------------------------------------------------
                                                           
                nv = nv-1;
                nf = nf+1;
                
                if ml == 0      % Situation that there is no general constraint in the working set.
                    %%----------------------Test Code----------------------
                    if (~isempty(Yv) || ~isempty(Lv))
                        error('Yv and Lv should be empty.');
                    end
                    %%-----------------------------------------------------
                    gv = gx(1:nv,:);
                    if nf == ndec
                       pvStar = zeros(ndec,1);
                    else
                        pvStar = linsolve(Hv,-gv);
                    end                    
                    p = [pvStar;zeros(nf,1)];
                    p = permutReco(p,orderPermu,ndec,1); 
                else
                    QYv = Q*Yv;
                    Y_tilde = QYv(1:nv,:);   % nv has been updated before
                    y_tilde = QYv(nv+1,:)';
                    tau = (1-y_tilde'*y_tilde)^(-1/2);
                    z = [-tau*Y_tilde*y_tilde;1/tau];                    
                    if ml > nv
                        error('Unsolvable.');
                    end
                    QYz = ([QYv,z]);
                    LvTmp = [Lv,zeros(ml,1)];
                    AvTmp = LvTmp*QYz'*Rv_hat;
                    a = AvTmp(:,nv+1);
                    Af = [a,Af];
                    P = eye(ml+1,ml+1);
                    for i = 1:ml
                        % 这里采用一种特殊的 plane rotation 的方法
                        G = myplanerot([QYz(nv+1,ml+1);QYz(nv+1,ml+1-i)]);
                        QYz = colRot(QYz,G,ml+1,ml+1-i);
                        P = colRot(P,G,ml+1,ml+1-i);
                    end                    
                    QYP = [QYv,z]*P;       % !! Here QYP should has the form of (4.4)
                    z = Q'*z;
                    Yv_bar = QYP(1:nv,1:ml);
                    LvP = [Lv,zeros(ml,1)]*P;
                    Lv_bar = LvP(:,1:ml);   % Here we can check the rightness of Av_bar = Lv_bar*Yv_bar'*Rv_bar;
                    % Update
                    Yv = Yv_bar;
                    Lv = Lv_bar;
                    Av = Lv*Yv'*Rv;
                    uv_baromega = Q*(uv+alpha*wv);
                    uv_bar = uv_baromega(1:nv,:);
                    v = (1-alpha)*z'*uv;
                    vl_baromega = P'*[vl;v];
                    vl_bar = vl_baromega(1:ml,:);
                    wv_barzero = Q*((1-alpha)*wv+v*z);
                    wv_bar = wv_barzero(1:nv,:);
                    % Update
                    uv = uv_bar;
                    vl = vl_bar;
                    wv = wv_bar;                
                    % Compute p for the next iteration
                    pvStar = linsolve(Rv,wv);                   
                    p = [pvStar;zeros(nf,1)];                          
                    p = permutReco(p,orderPermu,ndec,1); 
                end                                
            elseif (addBoundConstraint == 0) && (addGeneralConstraint ==1)
                %% Adding a general constraint
                isInWl(generalIndex) = 1;
                wl = [wl;generalIndex];
                ml = ml + 1;
                % Other updates ...         
                a = permut(AA(generalIndex,:)',orderPermu,ndec,1);                                
                if (ml == 1)    % general constraint added to empty A
                    invRv = inv(Rv);
                    A = (a)';
                    Av = A(1,1:nv);
                    Af = A(1,nv+1:ndec);                    
                    AinvR = Av*invRv;
                    %[Qtmp,Rtmp] = qr(AinvR');   % To achieve WGS factorization
                    [Qtmp,Rtmp] = gs_m(AinvR');   % To achieve WGS factorization
                    Yv = Qtmp(:,1:ml);
                    Lv = Rtmp(1:ml,:)';
                    if max(abs(Lv*Yv'-AinvR)) > 0.000001
                        error('Lv and Yv initialization failed!');
                    end
                    
                    gv = gx(1:nv,:);
                    uv = linsolve(Rv',gv);
                    vl = Yv'*uv;
                    wv = Yv*vl-uv;
                else            % general constraint added to nonempty A
                    q = linsolve(Rv',a(1:nv));                    
                    z_unnomalized = (eye(nv,nv)-Yv*Yv')*q;                    
                    tau = (1/(z_unnomalized'*z_unnomalized))^(1/2);    % The choice of tau is of no reference                    
                    z = tau*(eye(nv,nv)-Yv*Yv')*q;
                    Yv_bar = [Yv,z];
                    l = Yv'*q; 
                    gamma = z'*q;
                    Lv_bar = [Lv,zeros(ml-1,1);l',gamma];
                    uv_bar = uv + alpha*wv;
                    v = (1-alpha)*z'*uv;
                    vl_bar = [vl;v];
                    wv_bar = (1-alpha)*wv+v*z;
                    % Update of Av and Af
                    A = [A;a'];
                    Av = [Av;a(1:nv)'];
                    Af = [Af;a(nv+1:ndec)'];                   
                 
                    % Update
                    Yv = Yv_bar;
                    Lv = Lv_bar;
                    uv = uv_bar;
                    vl = vl_bar;
                    wv = wv_bar;
                    
                    % Check update
                    a_up = [l',gamma]*Yv'*Rv;
                    diff_a = max(abs(a(1:nv,:)-a_up'));
                    
                    % Check 对累计的更新误差进行纠正
                    %if max(max(abs(Av-Lv*Yv'*Rv)))>0.0005
                    if diff_a > 0.0005
                        disp('Av or Lv update fails');
                        disp(max(max(Av-Lv*Yv'*Rv)));
                        %error('Av or Lv update fails');
                        if diff_a > 0.0005
                            invRv = inv(Rv);
                            AinvR = Av*invRv;
                            %[Qtmp,Rtmp] = qr(AinvR');   % To achieve WGS factorization
                            [Qtmp,Rtmp] = gs_m(AinvR');   % To achieve WGS factorization
                            Yv = Qtmp(:,1:ml);
                            Lv = Rtmp(1:ml,:)';
                            % Initial value of auxiliary vectors
                            gv = gx(1:nv,:);
                            uv = linsolve(Rv',gv);
                            vl = Yv'*uv;
                            wv = Yv*vl-uv;
                        end
                    end
                end
                
                % Check
                if max(max(abs(Av-Lv*Yv'*Rv))) > 0.0005
                    disp('Av or Lv update fails');
                    disp(max(max(abs(Av-Lv*Yv'*Rv))));
                    %error('Av or Lv update fails');
                end
                
                if ml == ndec
                    pvStar = zeros(ndec,1);
                else
                    pvStar = linsolve(Rv,wv);
                end                
                % Compute p for the next iteration                                
                p = [pvStar;zeros(nf,1)];                
                p = permutReco(p,orderPermu,ndec,1);  
                
            else
                error('Add constraint error!');
            end
        else    % 当 alpha == 1 时，保持 working set 不变再求解一次 p
            gv = gx(1:nv,:);
            if ml == 0
                %%----------------------Test Code----------------------
                if (~isempty(Yv) || ~isempty(Lv))
                    error('Yv and Lv should be empty.');
                end
                %%-----------------------------------------------------
                pvStar = linsolve(Hv,-gv);
                p = [pvStar;zeros(nf,1)];                
                p = permutReco(p,orderPermu,ndec,1);  
            else                
                % 此时虽然 Lv 和 Yv 没变，但gv 发生了变化，因此要更新 u，v 和 w                                
                uv = linsolve(Rv',gv);                
                vl = Yv'*uv;
                wv = Yv*vl-uv;

                
%                 lambdal = linsolve(Lv',vl);
%                 pvStarTest = linsolve(Hv,Av'*lambdal-gv);
                
                pvStar = linsolve(Rv,wv);
                p = [pvStar;zeros(nf,1)];                
                p = permutReco(p,orderPermu,ndec,1);  
            end
        end
    end        
end