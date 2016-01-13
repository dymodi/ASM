% A Practical Dual Active Set Method
% Dual algorithm based on Ferreau's thesis: An Online Active Set Strategy
% for Fast Solution of Parametric Quadratic Programs with Applications to
% Predictive Engine Control
% Together with Goldfarb's paper:  A Numerically Stable Dual Method for 
% Solving Strictly Convex Quadratic Programs
% z = 1/2x'Hx + g'x, s.t. Gx>b
% 2016/1/10
% Yi DING
% Input:
% x: Primal variables
% y: Dual variables
% Output:
% xStar: Optimal primal variable
% iterStar: Iteration count

function [xStar, iterStar, finalAS, failFlag] = asm_dual_cs(H,invH,g,G,b,x,y,maxIter,ny,nu,M,P)

%% Step 0 Initial primal and dual variable, intial active set
[mc,ndec] = size(G);
A = [];             % Current active set
notA = (1:mc)';     % Current not active set
if isempty(x) || isempty(y)
    x = -invH*g;
    y = [];
end
failFlag = 0;
toStep1 = 1;
toStep2 = 0;

% In case we only consider constraitns on u and y
% Note that in dual ASM, consInfo has a different meaning
% In primal ASM, consInfo stores cons in w, while in dual ASM, consInfo
% stores cons in notW
% Here the we only consider cons on u and y but omit delta_u
consInfo = zeros(max([M,P]),nu*2+ny*2);
for i = 1:nu
    for j = 1:M
        consInfo(j,i) = (j-1)*nu+i;
        consInfo(j,i+nu) = (j-1)*nu+i+nu*M;
    end
end
for i = 1:ny
    for j = 1:P
        consInfo(j,i+2*nu) = (j-1)*ny+i+2*nu*M;
        consInfo(j,i+2*nu+ny) = (j-1)*ny+i+2*nu*M+ny*P;
    end
end
consInfoNum = zeros(1,nu*2+ny*2);
consHaveAct = zeros(1,nu*2+ny*2);

for j = 1:2*nu
    consInfoNum(j) = M;
end
for j = 2*nu+1:2*nu+2*ny
    consInfoNum(j) = P;
end
hpW = [];       % High priority working set
lpW = [];       % Low priority working set
for j = 1:length(consInfoNum)
    hpW = [hpW;consInfo(1,j)];
end
hpWInd = 1;
for j = 1:2*nu*M+2*ny*P
    if hpWInd <= length(consInfoNum) && j == hpW(hpWInd)
        hpWInd = hpWInd+1;
    else
        lpW = [lpW;j];
    end
end

% Iterations
for k = 1:maxIter
    if k == maxIter
        failFlag = 1;
        xStar = x;
        iterStar = k;
        finalAS = A; 
        disp('Maximum iteration reached. Dual ASM with CS fails');
        %error('Maximum iteration reached.');
    end
    
    %% Step 1 Choose a violated (primal) constraint
    if toStep1 == 1 && toStep2 == 0
        optFlag = 1;
%         mostVioValu = 0;
%         mostVioCons = 0;
%         for j = 1:length(notA)
%             i = notA(j);
%             if G(i,:)*x < b(i);
%                 % % Here we pick the violated constraint
%                 % optFlag = 0;
%                 % q = i;             % Note, q is the id of the cons
%                 % qIndNotA = j;
%                 % break;
%                 % Here we pick the most violated one from all constraints
%                 if (G(i,:)*x - b(i))/norm(G(i,:)) < mostVioValu
%                     mostVioValu = (G(i,:)*x - b(i))/norm(G(i,:));
%                     mostVioCons = i;
%                     optFlag = 0;
%                     q = mostVioCons;
%                     qIndNotA = j;
%                 end
%             end
%         end
        
        % Constraints selection strategy 
        % First Chek the high priority cons
        mostVioCons = 0;
        mostVioValu = 0;
        for j = 1:length(hpW)
            cons = hpW(j);
            if G(cons,:)*x < b(cons);
                optFlag = 0;
                vioValu = (G(cons,:)*x-b(cons))/norm(G(cons,:));
                if vioValu < mostVioValu
                    mostVioCons = cons;
                    mostVioValu = vioValu;
                end
            end
        end
        % No violated constraint in hpW, check lpW
        if optFlag == 1
            for j = 1:length(lpW)
                cons = lpW(j);
                if G(cons,:)*x < b(cons);
                    optFlag = 0;
                    vioValu = (G(cons,:)*x-b(cons))/norm(G(cons,:));
                    if vioValu < mostVioValu
                        mostVioCons = cons;
                        mostVioValu = vioValu;
                    end
                end
            end            
        end                
        q = mostVioCons;
        qIndNotA = find(notA==q);
        
        % No primal constraint violated, optimum reached.
        if optFlag == 1
            xStar = x;
            iterStar = k;
            finalAS = A;
            return;
        end                                  
        yPlus = [y;0];
    end
    
    %% Step 2 Calculate step directions
    GA = zeros(length(A),ndec);
    for j = 1:length(A)
        GA(j,:) = G(A(j),:);
    end
    Wk = inv(GA*invH*GA');
    Gq = G(q,:);
    
    delta_x = -(invH*GA'*Wk*GA*invH-invH)*Gq';
    delta_y = -Wk*GA*invH*Gq';  % Note, length(delta_y) = length(A);
    
    %% Step 4 Calculate the step length
    if isZero(delta_x,1e-5)
        tauPrim = +Inf;
    else
        tauPrim = -(Gq*x-b(q))/(Gq*delta_x);
    end
    tauDual = +Inf;
    for j = 1:length(A)
        if delta_y(j) < 0
            tauTmp = -yPlus(j)/delta_y(j);
            if tauTmp < tauDual
                tauDual = tauTmp;
                blockJ = j;     % Note here j is the index of cons in A
            end
        end
    end
    tau = min([tauPrim,tauDual]);
    if tau < 0
        tau = 0;
    end
    
    %% Step 5 Active set update
    if isZero(delta_x,1e-5)
        if tauDual == Inf
            error('QP infeasible!');
        end
        if length(yPlus) - length(delta_y) ~= 1
            error('Dimension error.');
        end
        for j = 1:length(delta_y)
            yPlus(j) = yPlus(j) + tau * delta_y(j);
        end
        yPlus(length(yPlus)) = yPlus(length(yPlus)) + tau;
        % Update hpW, lpW and consInfo 
        [hpW,lpW,consInfo,consInfoNum,consHaveAct] = updatePW_del_dual(hpW,lpW,...
            consInfo,consInfoNum,consHaveAct,A(blockJ),ny,nu,M,P);
        notA = [notA;A(blockJ)];    % Note that notA is not ordered                        
        A(blockJ) = [];
        y(blockJ) = [];                            
        yPlus(blockJ) = [];
        toStep1 = 0;
        toStep2 = 1;
    else
        x = x + tau * delta_x;  % Note that x keep original order
        if length(yPlus) - length(delta_y) ~= 1
            error('Dimension error.');
        end
        for j = 1:length(delta_y)
            yPlus(j) = yPlus(j) + tau * delta_y(j);
            if yPlus(j) < -0.000001
                error('Dual infeasible!');
            end
        end
        yPlus(length(yPlus)) = yPlus(length(yPlus)) + tau;
        if tau == tauPrim               % Full Step            
            y = yPlus;
            A = [A;q];
            % A = sort(A);              % Do we need A to be ordered?
            notA(qIndNotA) = [];
            % Update hpW, lpW and consInfo     
            [hpW,lpW,consInfo,consInfoNum,consHaveAct] = updatePW_add_dual(hpW,lpW,...
                consInfo,consInfoNum,consHaveAct,q,ny,nu,M,P);
            toStep1 = 1;
            toStep2 = 0;
        elseif tau == tauDual           % Partial Step
            % Update hpW, lpW and consInfo     
            [hpW,lpW,consInfo,consInfoNum,consHaveAct] = updatePW_del_dual(hpW,lpW,...
                consInfo,consInfoNum,consHaveAct,A(blockJ),ny,nu,M,P);
            notA = [notA;A(blockJ)];    % Note that notA is not ordered
            A(blockJ) = [];
            y(blockJ) = [];                                    
            yPlus(blockJ) = [];
            toStep1 = 0;
            toStep2 = 1;
        else
            error('tau error!');
        end
        
        % Check the primal variables with active set
        % Can be removed in future stable version
        GAt = zeros(length(A),ndec);
        for j = 1:length(A)
            GAt(j,:) = G(A(j),:);
        end
        bAt = zeros(length(A),1);
        for j = 1:length(A)
            bAt(j,:) = b(A(j),:);
        end
        if norm(GAt*x-bAt) > 1e-5
            error('Active Set Error! Priaml Variables!');
        end
    end          
end

end