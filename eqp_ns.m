% Solve equality constrained QP problem with Null-Space Method
% Algorithm based on book Numerical Optimization, Section 16.2
% z = 1/2x'Gx + c'x, s.t. Ax=b
% Yi Ding, 2016/1/5

% Input:
% G,c,A,b: QP parameters
% length(indIndex) = m, index of m independent variable
% The function of indIndex is to partition A to B and N, AP = [B|N]
% Output:
% xStar: Optimal variable
% zStar: Optimal objective function value
% iterStar: Iteration count

function [xStar, zStar] = eqp_ns(G,c,A,b,x,indIndex) 

[m,n] = size(A);    % m: number of constraints; n: number of variables
P = eye(n,n);
indIndex = sort(indIndex);
for i = 1:m
    if indIndex(i) > m
        P(i,i) = 0;
        P(indIndex(i),indIndex(i)) = 0;
        P(i,indIndex(i)) = 1;
        P(indIndex(i),i) = 1;
    end
end
% Here P should be orthogonal
if ~isequal(eye(n,n),P'*P)
    error('P is not orthogonal!');
end
BN = A*P;
B = BN(:,1:m);
N = BN(:,m+1:n);
invB = inv(B);
Y = [invB;zeros(n-m,m)];
Z = [-invB*N;eye(n-m,n-m)];
if ~isequal(A*P*Z,zeros(m,n-m))
    error('Z should be null space of A');
end

% Here x usually is zero (Note that permutation is done at the same time)
h = (A*x-b);
g = P*(c+G*x);

py = linsolve(A*P*Y,-h);
pz = linsolve(Z'*P'*G*P*Z,-Z'*P'*G*P*Y*py-Z'*g);
p = Y*py+Z*pz;



xStar = x + inv(P)*p;
lambda = linsolve((A*P*Y)',Y'*(g+P'*G*P*p));
zStar = 0.5*xStar'*G*xStar + c'*xStar;

end