% 一个Practical的ASM程序，用于比较和测试
% 解决形如：z = 1/2x'Gx + c'x, s.t. Ax>b的问题

% 2014.12.6
% 丁一

% Input:
% G: QP命题参数
% c: QP命题参数
% A: QP命题参数(约束矩阵系数）
% b: QP命题参数(约束矩阵系数）
% x: ASM初始点(可行点)
% w：初始点对应的积极约束（初始Work Set）

% Output:
% xStar: 求解得到的最优点
% zStar: 最优点对应的目标函数
% iterStar: ASM的迭代次数

function [xStar, zStar, iterStar, finalAS] = asm(G,invG,c,A,b,x,w,maxIter) 

[mc,ndec] = size(A);
iterStar = 0;

% Give Warrings if the initial point is infeasible!
if min(A*x-b) < -1e-6
   error('Infeasible initial point!'); 
   %display('Infeasible initial point!');
   %return;
end


for i = 1:maxIter
    if i == maxIter
        error('maxIter reached!');
    end
        
    
    iterStar = iterStar + 1;
    g = G*x+c;
    
    % 根据w准备A和b
    % 每个周期的setSize很重要
    setSize = length(w);
    Aw = zeros(setSize,ndec);
    bw = zeros(setSize,1);
   for j = 1:setSize
      Aw(j,:)  = A(w(j),:);
   end
   
   % 求解等式约束命题
   [p, ~, ~] = eqp(G,invG,g,Aw,bw,zeros(ndec,1),setSize);
   
   if (isZero(p,1e-5) == 1)  % 注意这里的p是算出来的浮点数向量，不能用p是否等于0直接判断
       % lambda = (G*x+c)./Aw(); 
       lambda = linsolve(Aw',g);    % 这里隐含的是一个方程组求解啊……
       if (setSize == 0 || min(lambda) >= 0)
           xStar = x;
           finalAS = w;
           if ~isempty(w)
               disp('Not empty optimal active set.');
           end
           break;
       else
           [~,index] = min(lambda);
           w(index) = [];   % Matlab中动态删除这一招有点厉害
       end
   else
       notW = w2notW(w,mc);
       Anotw = zeros(mc-setSize,ndec);
       bnotw = zeros(mc-setSize,1);
       for j = 1:mc-setSize
           Anotw(j,:)  = A(notW(j),:);
           bnotw(j) = b(notW(j));
       end
       
       % 计算alpha
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
           tmpW = w;
           w = zeros(setSize+1,1);
           w(1:setSize) = tmpW;
           w(setSize+1) = notW(indexMin);
       end
   end
end

zStar = 1/2*xStar'*G*xStar + c'*xStar;
end