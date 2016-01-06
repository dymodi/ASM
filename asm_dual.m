% A Practical Dual Active Set Method
% Dual algorithm based on Ferreau's thesis: An Online Active Set Strategy 
% for Fast Solution of Parametric Quadratic Programs with Applications to 
% Predictive Engine Control
% z = 1/2x'Hx + g'x, s.t. Gx>b
% 2016.1.4
% Yi DING
% Input:
% x: Primal variables
% y: Dual variables
% Output:
% xStar: Optimal variable
% iterStar: Iteration count

function [xStar, iterStar, finalAS, failFlag] = asm_dual(H,invH,g,G,b,x,y,maxIter)

%% Step 1 Initial primal and dual variable, intial active set
[mc,ndec] = size(G);
A = [];             % Current active set
notA = (1:mc)';     % Current not active set
actSize = 0;        % The cardinality of the current active set
if isempty(x) || isempty(y)
    x = -invH*g;
    y = zeros(mc,1);
end
failFlag = 0;
toStep3 = 0;

% Iterations
for k = 1:maxIter
    if k == maxIter
        failFlag = 1;
        error('Maximum iteration reached.');
    end
    
    %% Step 2 Choose a violated (primal) constraint
    if toStep3 == 0
        optFlag = 1;
        for j = 1:length(notA)
            i = notA(j);
            if G(i,:)*x < b(i);    % Here we find a violated constraint
                optFlag = 0;
                q = i;             % Note, q is the id of the cons
                qIndNotA = j;      
                break;
            end
        end
        % No primal constraint violated, optimum reached.
        if optFlag == 1
            xStar = x;
            iterStar = k;
            finalAS = A;
            return;
        end
    end

    %% Step 3 Calculate step directions    
    GA = zeros(length(A),ndec);
    for j = 1:length(A)
        GA(j,:) = G(A(j),:);
    end
    Wk = inv(GA*invH*GA');
    Gq = G(q,:);
    
    delta_x = -(invH*GA'*Wk*GA*invH-invH)*Gq';   % Note here is different 
    % with the substance in the thesis    
    delta_y = -Wk*GA*invH*Gq';  % Note, length(delta_y) = length(A);
    
    %% Step 4 Calculate the step length
    if isZero(delta_x,1e-3)
        tauPrim = +Inf;
    else
        tauPrim = -(Gq*x-b(q))/(Gq*delta_x);     % Note here is different 
    % with the substance in the thesis    
    end
    tauDual = +Inf;
    for j = 1:length(A)
        if delta_y(j) < 0
            tauTmp = -y(A(j))/delta_y(j);
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
    if isZero(delta_x,1e-3)
        if tauDual == Inf
            error('QP infeasible!');
        end
        notA = [notA;A(blockJ)];    % Note that notA is not ordered
        A(blockJ) = [];
        delta_y(blockJ) = [];
        for i = 1:length(A)
            y(A(i)) = y(A(i)) + tau * delta_y(i);
            if y(A(i)) < 0
                error('Dual infeasible!');
            end
        end
        y(q) = y(q) + tau;
        toStep3 = 1;
        continue;
    end
    if tau == tauPrim
        A = [A;q];
        notA(qIndNotA) = [];
        % A = sort(A);          % Do we need A to be ordered?
        % Also note that if we force the order in A, then the new added
        % cons q may not be located in the last position, thus the next
        % for loop is wrong
        x = x + tau * delta_x;  % Note that x keep original order
        for i = 1:length(A)-1
            y(A(i)) = y(A(i)) + tau * delta_y(i);
            if y(A(i)) < 0
                error('Dual infeasible!');
            end
        end
        y(q) = y(q) + tau;
        toStep3 = 0;
    elseif tau == tauDual
        notA = [notA;A(blockJ)];    % Note that notA is not ordered
        A(blockJ) = [];
        delta_y(blockJ) = [];
        x = x + tau * delta_x;  % Note here is different with the thesis
        % x = x + delta_x;  % This is Ferreau's version
        for i = 1:length(A)
            y(A(i)) = y(A(i)) + tau * delta_y(i);
            if y(A(i)) < 0
                error('Dual infeasible!');
            end
        end
        y(q) = y(q) + tau;
        toStep3 = 1;
    else
        error('tau error!');
    end 
    
    % Check the primal variables with active set
    
    % Check the dual variables with active set
    
end


end