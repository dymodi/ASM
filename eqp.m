% 一个Practical的求解等式约束的QP命题的程序，用于为每周期ASM的求解服务
% 解决形如：z = 1/2x'Gx + c'x, s.t. Ax=b的问题

% 2014.12.6
% 丁一

% Input:
% G:    QP命题参数
% invG: G矩阵的逆，用于Schur-Complement方法中求解方程组
% c:    QP命题参数
% A:    QP命题参数(约束矩阵系数）
% b:    QP命题参数(约束矩阵系数）

% Output:
% xStar: 求解得到的最优点
% zStar: 最优点对应的目标函数
% iterStar: ASM的迭代次数

% 2014.12.6 测试通过

function [xStar, zStar, iterStar] = eqp(G,invG,c,A,b,x,consNum) 

iterStar = 0;

% 当等式约束问题退化为无约束的问题时
if (consNum == 0)
   xStar = -invG*c;
   %zStar = 0.5 * xStar'*G*xStar + c'*xStar
   zStar = -1;
   return
end


%L = chol(A*invG*A','lower');
%L = cf(A*invG*A');
%for i = 1:20


iterStar = iterStar + 1;
h = A*x-b;
g = c+G*x;
equation_b = A*invG*g-h;
%lambda = luEvaluate(L,L',equation_b);

lambda = linsolve(A*invG*A',equation_b);

p = invG * (A'*lambda - g);
x = x + p;




%     if (max([abs(p)]) < 1e-8)
%         break;
%     end
% end
    
xStar = x;
zStar = -1;
%zStar = 0.5 * xStar'*G*xStar + c'*xStar;

end