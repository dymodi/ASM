% A Practical Dual Active Set Method
% Dual algorithm based on Ferreau's thesis: An Online Active Set Strategy
% for Fast Solution of Parametric Quadratic Programs with Applications to
% Predictive Engine Control
% Together with Goldfarb's paper:  A Numerically Stable Dual Method for 
% Solving Strictly Convex Quadratic Programs
% z = 1/2x'Hx + g'x, s.t. Gx>b
% 2016.1.4  % Pass random QP test on 2016/1/7
% Yi DING
% Input:
% x: Primal variables
% y: Dual variables
% Output:
% xStar: Optimal primal variable
% iterStar: Iteration count

function [xStar, iterStar, finalAS, failFlag] = asm_dual(H,invH,g,G,b,x,y,maxIter,ny,nu,M,P)

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
consInfo = zeros(max([M,P]),nu*2+ny*2);
for i = 1:nu
    for j = 1:M
        consInfo()
    end
end

consInfoNum = zeros(1,nu*2+ny*2);

hpW = [];       % High priority working set
lpW = [];       % Low priority working set

% Iterations
for k = 1:maxIter
    if k == maxIter
        failFlag = 1;
        error('Maximum iteration reached.');
    end
    
    %% Step 1 Choose a violated (primal) constraint
    if toStep1 == 1 && toStep2 == 0
        optFlag = 1;
%         % The original constraint picking strategy
%         for j = 1:length(notA)
%             i = notA(j);
%             if G(i,:)*x < b(i);    % Here we find a violated constraint
%                 optFlag = 0;
%                 q = i;             % Note, q is the id of the cons
%                 qIndNotA = j;
%                 break;
%             end
%         end
        
        

        
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
    if isZero(delta_x,1e-6)
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
    if isZero(delta_x,1e-6)
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
            toStep1 = 1;
            toStep2 = 0;
        elseif tau == tauDual           % Partial Step
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