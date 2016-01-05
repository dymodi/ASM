% A Practical Dual Active Set Method
% Primal algorithm based on the book Numerical Optimization
% Dual analysis based on the book Practical Optimization
% z = 1/2x'Gx + c'x, s.t. Ax>b
% 2016.1.4
% Yi DING
% Input:
% x: Dual feasible starting point (Can be empty)
% w£ºInitial working set
% Output:
% xStar: Optimal variable
% zStar: Optimal objective function value
% iterStar: Iteration count
% Note, dual ASM solves the dual problem using primal ASM


function [xStar, zStar, iterStar, finalAS, failFlag] = asm_dual(H,invH,oric,oriA,b,x,w,maxIter)

%% Here we form the dual problem
[mc,~] = size(oriA);
if isempty(x)
    x = -invH*oric;
    x = linsolve(oriA',H*x+oric);
end
G = oriA*invH*oriA';
invG = inv(G);
c = oriA*invH*oric+b;
A = eye(mc,mc);
b = zeros(mc,1);
ndec = mc;

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
        %[p, ~, ~] = eqp(G,invG,g,Aw,bw,zeros(ndec,1),setSize);
        [p, ~] = eqp_ns(G,g,Aw,bw,zeros(ndec,1),w) ;
    end
    
    
    if (isZero(p,1e-4) == 1)
        %% p=0. Optimal reached or delete a constraint
        % lambda = (G*x+c)./Aw();
        lambda = linsolve(Aw',g);
        if max(isnan(lambda)) == 1
            % error('Equation solve fails,try resolve.');
            disp('Equation solve fails,try modification.');            
            % Some modification to help compute lambda
            [rAw,cAw] = size(Aw);
            lambda = linsolve((Aw+0.001*eye(rAw,cAw))',g);
            if max(isnan(lambda)) == 1
                error('Modification fails.');
            end
        end
        if (setSize == 0 || min(lambda) >= 0)
            xStar = x;
            finalAS = w;
            break;
        else
            [~,index] = min(lambda);
            w(index) = [];
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
        minAlpha = 1;
        for j = 1:mc-setSize
            index = notW(j);
            if p(index) < 0     % If p(index) > 0, constraint will meet
                tmpAlpha = -x(index)/p(index);
                if tmpAlpha < minAlpha
                    minAlpha = tmpAlpha;
                end
            end
            
        end
        alpha = max([min([1,minAlpha]),0]);
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

%% Here we transform the dual optimal to primal optimal
xStar = invH(oriA'*xStar-oric);
zStar = 1/2*xStar'*G*xStar + c'*xStar;
end