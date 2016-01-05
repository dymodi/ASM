% Solve equality constrained QP problem with Schur-Complement Method
% Algorithm based on book Numerical Optimization, Section 16.2
% z = 1/2x'Gx + c'x, s.t. Ax=b
% Yi Ding, 2014/12/6

% Input:
% G,c,A,b: QP parameters
% invG: Inversion of G, used in Schur-Complement method
% Output:
% xStar: Optimal variable
% zStar: Optimal objective function value
% iterStar: Iteration count

function [xStar, zStar, iterStar] = eqp(G,invG,c,A,b,x,consNum) 

iterStar = 0;
% Check whether the problem is unconstrained
if (consNum == 0)
   xStar = -invG*c;
   %zStar = 0.5 * xStar'*G*xStar + c'*xStar
   zStar = -1;
   return
end

iterStar = iterStar + 1;
h = A*x-b;
g = c+G*x;
equation_b = A*invG*g-h;
lambda = linsolve(A*invG*A',equation_b);

p = invG * (A'*lambda - g);
x = x + p;
    
xStar = x;
zStar = -1;
%zStar = 0.5 * xStar'*G*xStar + c'*xStar;

end