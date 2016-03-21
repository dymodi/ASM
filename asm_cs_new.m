% A Practical Primal Active Set Method with new constraints selection 
% strategy
% Algorithm based on book Numerical Optimization
% The new constraints selection can be found in ResearchNote 20160303
% z = 1/2x'Gx + c'x, s.t. Ax>b
% 2016.3.3
% Yi DING
% Input:
% x: Primal feasible starting point
% w£ºInitial working set
% preActSet: The opimal active set of previous sampling time
% Output:
% xStar: Optimal variable
% zStar: Optimal objective function value
% iterStar: Iteration count

function [xStar, zStar, iterStar, finalAS, failFlag] = asm_cs_new(G,invG,c,A,b,x,w,maxIter,preActSet)

[mc,ndec] = size(A);
iterStar = 0;
failFlag = 0;

% Give Warrings if the initial point is infeasible!
if min(A*x-b) < -1e-6
    error('Infeasible initial point!');
    %display('Infeasible initial point!');
    %return;
end

for i = 1:maxIter
    if i == maxIter
        failFlag = 1;
        disp('maxIter reached!');
        xStar = zeros(ndec,1);
        finalAS = [];
        %error('maxIter reached!');
    end
    
    iterStar = iterStar + 1;
    g = G*x+c;
    
    % Compute active constraints matrix accoring to w
    setSize = length(w);
    Aw = zeros(setSize,ndec);
    bw = zeros(setSize,1);
    for j = 1:setSize
        Aw(j,:)  = A(w(j),:);
    end
    
    % Solve equality constrained problem
    if setSize == ndec
        p = zeros(ndec,1);
    else
        [p, ~, ~] = eqp(G,invG,g,Aw,bw,zeros(ndec,1),setSize);
    end
    
    
    if (isZero(p,1e-4) == 1)
        %% p=0. Optimal reached or delete a constraint
        % lambda = (G*x+c)./Aw();
        lambda = linsolve(Aw',g);
        if max(isnan(lambda)) == 1
            error('Equation solve fails,try resolve.');
%             % Some modification to help compute lambda
%             disp('Equation solve fails,try modification.');                        
%             [rAw,cAw] = size(Aw);
%             lambda = linsolve((Aw+0.001*eye(rAw,cAw))',g);
%             if max(isnan(lambda)) == 1
%                 error('Modification fails.');
%             end
        end
        if (setSize == 0 || min(lambda) >= 0)
            xStar = x;
            finalAS = w;
            break;
        else
            % [~,index] = min(lambda);
            % w(index) = [];
            lambdaTmp = lambda;
            wTmp = w;
            while(~isempty(wTmp))
                if min(lambdaTmp) >= 0
                    % All negative lambda are preActSet
                    % We have to delete a cons in preActSet
                    [~,index] = min(lambda);
                    w(index) = [];
                    break;
                end
                [~,index] = min(lambdaTmp);
                if any(preActSet == wTmp(index))    
                    % The cons to be deleted are in preActSet
                    % Remove the cons and find the next negative lamda
                    wTmp(index) = [];
                    lambdaTmp(index) = [];                    
                else
                    % The cons to be deleted are not in preActSet
                    % Successfully delete the cons from working set
                    w(find(w==wTmp(index))) = [];
                    break;
                end
                if isempty(wTmp)
                    % Special case from example in book NO
                    [~,index] = min(lambda);
                    w(index) = [];
                end
            end
            
        end
    else
        notW = w2notW(w,mc);
        Anotw = zeros(mc-setSize,ndec);
        bnotw = zeros(mc-setSize,1);
        for j = 1:mc-setSize
            Anotw(j,:)  = A(notW(j),:);
            bnotw(j) = b(notW(j));
        end
        
        %% Compute Step length alpha
        %numAlpha = 0;
        hasFirst = 0;
        %minAlpha = 1;
        for j = 1:mc-setSize
            ap = Anotw(j,:)*p;
            if (ap < 0)
                if (hasFirst == 0)
                    minAlpha = (bnotw(j)-Anotw(j,:)*x)/ap;
                    indexMin = j;
                    hasFirst = 1;
                else
                    tmpAlpha = (bnotw(j)-Anotw(j,:)*x)/ap;                    
                    if (tmpAlpha < minAlpha)
                        minAlpha = tmpAlpha;
                        indexMin = j;
                    end
                end
            end
        end
        alpha = min([1,minAlpha]);
        x = x + alpha * p;
        if (alpha < 1)
            %% Add blocking constraint to working set
            tmpW = w;
            w = zeros(setSize+1,1);
            w(1:setSize) = tmpW;
            w(setSize+1) = notW(indexMin);
        end
    end
end

zStar = 1/2*xStar'*G*xStar + c'*xStar;
end