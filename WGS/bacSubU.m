% Solve a linear system with upper-triangular matrix using backward substitution
% U * x = y;

function x = bacSubU(U,y,flag)

if flag == 1
    U = U';
end

n = length(y);
x = zeros(n,1);

x(n) = y(n)/U(n,n);
for m = 1:n-1
    i = n-m;
    tmp = 0;
    for j = i+1:n
        tmp = tmp + U(i,j)*x(j);
    end
    x(i) = (y(i) - tmp)/U(i,i);        
end
end