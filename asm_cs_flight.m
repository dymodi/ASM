% A Practical ASM function
% Solve：z = 1/2x'Gx + c'x, s.t. Ax>b 
% This is a version with constraints seletion, based on Gionata's idea
% 2015.12.21
% Yi

% Input:
% G: QP parameters
% c: QP parameters
% A: QP parameters (Constraints matrix)
% b: QP parameters (Constraints vector)
% x: Iterating point
% w：Working set

% Output:
% xStar: Optimal point
% zStar: Optimal objective function
% iterStar: Iteration count

function [xStar, zStar, iterStar, finalAS] = asm_cs_flight(G,invG,c,A,b,x,w,maxIter,ny,nu,M,P) 

[mc,ndec] = size(A);
iterStar = 0;

% Give Warrings if the initial point is infeasible!
if min(A*x-b) < -1e-6
   error('Infeasible initial point!'); 
end

u1min = [];
u2min = [];
u1max = [];
u2max = [];
y1min = [];
y2min = [];
y1max = [];
y2max = [];
consInfo = zeros(nu*M,nu*2+ny*2);
consInfoNum = zeros(1,nu*2+ny*2);
hpW = [];       % High priority working set
lpW = [];       % Low priority working set

if ~isempty(w)     % Initial hpW and lpW if w is not empty
    for i = 1:length(w)
        indexCons = w(i);
        % Here we check the category of the new added constraint
        if indexCons <= nu*M
            if mod(indexCons,2) == 1
                u1max = [u1max;indexCons];
                u1max = sort(u1max);
            else
                u2max = [u2max;indexCons];
                u2max = sort(u2max);
            end
        elseif indexCons <= 2*nu*M
            if mod(indexCons,2) == 1
                u1min = [u1min;indexCons];
                u1min = sort(u1min);
            else
                u2min = [u2min;indexCons];
                u2min = sort(u2min);
            end
        elseif indexCons <= (2*nu*M+ny*P)
            if mod(indexCons,2) == 1
                y1max = [y1max;indexCons];
                y1max = sort(y1max);
            else
                y2max = [y2max;indexCons];
                y2max = sort(y2max);
            end
        else
            if mod(indexCons,2) == 1
                y1min = [y1min;indexCons];
                y1min = sort(y1min);
            else
                y2min = [y2min;indexCons];
                y2min = sort(y2min);
            end
        end
    end
    
    for i = 1:length(w)
        indexCons = w(i);
        [consInfo,consInfoNum] = addToConsInfo(indexCons,consInfo,consInfoNum,nu,ny,M,P);
    end
    
    [hpW_new,lpW_new] = updatePW(consInfo,consInfoNum);
    
    % Update hpW and lpW (only non-antecedent)
    hpW = []; lpW = [];
    if ~isempty(u1max)
        hpW = [hpW;u1max(1)];
        for j = 2:length(u1max)
            lpW = [lpW;u1max(j)];
        end
    end
    if ~isempty(u2max)
        hpW = [hpW;u2max(1)];
        for j = 2:length(u2max)
            lpW = [lpW;u2max(j)];
        end
    end
    if ~isempty(u1min)
        hpW = [hpW;u1min(1)];
        for j = 2:length(u1min)
            lpW = [lpW;u1min(j)];
        end
    end
    if ~isempty(u2min)
        hpW = [hpW;u2min(1)];
        for j = 2:length(u2min)
            lpW = [lpW;u2min(j)];
        end
    end
    if ~isempty(y1max)
        hpW = [hpW;y1max(1)];
        for j = 2:length(y1max)
            lpW = [lpW;y1max(j)];
        end
    end
    if ~isempty(y2max)
        hpW = [hpW;y2max(1)];
        for j = 2:length(y2max)
            lpW = [lpW;y2max(j)];
        end
    end
    if ~isempty(y1min)
        hpW = [hpW;y1min(1)];
        for j = 2:length(y1min)
            lpW = [lpW;y1min(j)];
        end
    end
    if ~isempty(y2min)
        hpW = [hpW;y2min(1)];
        for j = 2:length(y2min)
            lpW = [lpW;y2min(j)];
        end
    end
    
end

for i = 1:maxIter
    if i == maxIter
        error('maxIter reached!');
    end
        
    iterStar = iterStar + 1;
    g = G*x+c;
    
    % Form Aw and bw based on working set
    setSize = length(w);
    Aw = zeros(setSize,ndec);
    bw = zeros(setSize,1);
   for j = 1:setSize
      Aw(j,:)  = A(w(j),:);
   end
   
   % Solve equality-constrained QP problems
   [p, ~, ~] = eqp(G,invG,g,Aw,bw,zeros(ndec,1),setSize);
   
   if (isZero(p,1e-7) == 1)  % Check whether p_k is zero
       lambda = linsolve(Aw',g);    
       if (setSize == 0 || min(lambda) >= 0)
           xStar = x;
           finalAS = w;
           if ~isempty(w)
               disp('Not empty optimal active set.');
           end
           break;
       else
           % Original method to find most violated constraint and remove
           % the corresponding constraint from the working set           
           % [~,index] = min(lambda);
           % w(index) = []; 
           
           
           [w_new,consInfo,consInfoNum,hpW_new,lpW_new] = deleteCons(lambda,w,consInfo,consInfoNum,hpW_new,lpW_new);
           
           % Constraint seletion method based on Gionata's idea
           if isempty(hpW) % hpW is empty, we only consider lpW
               [~,index] = min(lambda);
               lpW(index) = [];
               [u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min] = deleteConstraint(u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min,w(index),nu,M,ny,P);
               w(index) = [];               
           elseif isempty(lpW) % lpW is empty, we only consider hpW
               [~,index] = min(lambda);
               hpW(index) = [];               
               [u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min] = deleteConstraint(u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min,w(index),nu,M,ny,P);
               w(index) = [];
           else
               minLambdaHp = 100000000;               
               minLambdaLp = 100000000; % Here thought 100000000 is large enough
               minIndexHp = 1;
               minIndexLp = 1;
               indexHpW = 1;
               indexLpW = 1;
               for j = 1:length(lambda)
                   if indexHpW <= length(hpW) && hpW(indexHpW) == w(j) 
                       % Current constraint is a higher priority constraint
                       if lambda(j) < minLambdaHp
                           minLambdaHp = lambda(j);
                           minIndexHp = indexHpW;
                           indexWforHpW = j;
                       end
                       indexHpW = indexHpW + 1;
                   else
                       % Current constraint is a lower priority constraint
                       if lambda(j) < minLambdaLp
                           minLambdaLp = lambda(j);
                           minIndexLp = indexLpW;
                           indexWforLpW = j;
                       end
                       indexLpW = indexLpW + 1;
                   end
               end
               if minLambdaHp < -0.000001
                   [u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min] = deleteConstraint(u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min,w(indexWforHpW),nu,M,ny,P);
                   hpW(minIndexHp) = [];
                   w(indexWforHpW) = [];
               else                   
                   [u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min] = deleteConstraint(u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min,w(indexWforLpW),nu,M,ny,P);
                   lpW(minIndexLp) = [];
                   w(indexWforLpW) = [];
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

       % Compute the step length alpha
       hasFirst = 0;
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
           tmpW = w;
           w = zeros(setSize+1,1);
           w(1:setSize) = tmpW;
           w(setSize+1) = notW(indexMin);
           w = sort(w);
           indexCons = notW(indexMin);
           
           % Here we check the category of the new added constraint
           if indexCons <= nu*M
               if mod(indexCons,2) == 1
                   u1max = [u1max;indexCons];
                   u1max = sort(u1max);
               else
                   u2max = [u2max;indexCons];
                   u2max = sort(u2max);
               end
           elseif indexCons <= 2*nu*M
               if mod(indexCons,2) == 1
                   u1min = [u1min;indexCons];
                   u1min = sort(u1min);
               else
                   u2min = [u2min;indexCons];
                   u2min = sort(u2min);
               end
           elseif indexCons <= (2*nu*M+ny*P)
               if mod(indexCons,2) == 1
                   y1max = [y1max;indexCons];
                   y1max = sort(y1max);
               else
                   y2max = [y2max;indexCons];
                   y2max = sort(y2max);
               end
           else
               if mod(indexCons,2) == 1
                   y1min = [y1min;indexCons];
                   y1min = sort(y1min);
               else
                   y2min = [y2min;indexCons];
                   y2min = sort(y2min);
               end
           end
           
           [consInfo,consInfoNum] = addToConsInfo(indexCons,consInfo,consInfoNum,nu,ny,M,P);
           [hpW_new,lpW_new] = updatePW(consInfo,consInfoNum);
           
           % Update hpW and lpW (only non-antecedent)
           hpW = []; lpW = [];
           if ~isempty(u1max)
               hpW = [hpW;u1max(1)];
               for j = 2:length(u1max)
                   lpW = [lpW;u1max(j)];
               end
           end
           if ~isempty(u2max)
               hpW = [hpW;u2max(1)];
               for j = 2:length(u2max)
                   lpW = [lpW;u2max(j)];
               end
           end
           if ~isempty(u1min)
               hpW = [hpW;u1min(1)];
               for j = 2:length(u1min)
                   lpW = [lpW;u1min(j)];
               end
           end
           if ~isempty(u2min)
               hpW = [hpW;u2min(1)];
               for j = 2:length(u2min)
                   lpW = [lpW;u2min(j)];
               end
           end
           if ~isempty(y1max)
               hpW = [hpW;y1max(1)];
               for j = 2:length(y1max)
                   lpW = [lpW;y1max(j)];
               end
           end
           if ~isempty(y2max)
               hpW = [hpW;y2max(1)];
               for j = 2:length(y2max)
                   lpW = [lpW;y2max(j)];
               end
           end
           if ~isempty(y1min)
               hpW = [hpW;y1min(1)];
               for j = 2:length(y1min)
                   lpW = [lpW;y1min(j)];
               end
           end
           if ~isempty(y2min)
               hpW = [hpW;y2min(1)];
               for j = 2:length(y2min)
                   lpW = [lpW;y2min(j)];
               end
           end    
           
%            % Update hpW and lpW (both non-antecedent and non-successive)
%            hpW = []; lpW = [];
%            if ~isempty(u1max)
%                hpW = [hpW;u1max(1)];
%                if length(u1max) > 1
%                    hpW = [hpW;u1max(length(u1max))];
%                end
%                for j = 2:length(u1max)-1
%                    lpW = [lpW;u1max(j)];
%                end
%            end
%            if ~isempty(u2max)
%                hpW = [hpW;u2max(1)];
%                if length(u2max) > 1
%                    hpW = [hpW;u2max(length(u2max))];
%                end
%                for j = 2:length(u2max)-1
%                    lpW = [lpW;u2max(j)];
%                end
%            end
%            if ~isempty(u1min)
%                hpW = [hpW;u1min(1)];
%                if length(u1min) > 1
%                    hpW = [hpW;u1min(length(u1min))];
%                end
%                for j = 2:length(u1min)-1
%                    lpW = [lpW;u1min(j)];
%                end
%            end
%            if ~isempty(u2min)
%                hpW = [hpW;u2min(1)];
%                if length(u2min) > 1
%                    hpW = [hpW;u2min(length(u2min))];
%                end
%                for j = 2:length(u2min)-1
%                    lpW = [lpW;u2min(j)];
%                end
%            end
%            if ~isempty(y1max)
%                hpW = [hpW;y1max(1)];
%                if length(y1max) > 1
%                    hpW = [hpW;y1max(length(y1max))];
%                end
%                for j = 2:length(y1max)-1
%                    lpW = [lpW;y1max(j)];
%                end
%            end
%            if ~isempty(y2max)
%                hpW = [hpW;y2max(1)];
%                if length(y2max) > 1
%                    hpW = [hpW;y2max(length(y2max))];
%                end
%                for j = 2:length(y2max)-1
%                    lpW = [lpW;y2max(j)];
%                end
%            end
%            if ~isempty(y1min)
%                hpW = [hpW;y1min(1)];
%                if length(y1min) > 1
%                    hpW = [hpW;y1min(length(y1min))];
%                end
%                for j = 2:length(y1min)-1
%                    lpW = [lpW;y1min(j)];
%                end
%            end
%            if ~isempty(y2min)
%                hpW = [hpW;y2min(1)];
%                if length(y2min) > 1
%                    hpW = [hpW;y2min(length(y2min))];
%                end
%                for j = 2:length(y2min)-1
%                    lpW = [lpW;y2min(j)];
%                end
%            end           
           
       end
   end
end

zStar = 1/2*xStar'*G*xStar + c'*xStar;
end
