% Solve a linear system with lower-triangular matrix using forward substitution
% L * y = b;

function y = fowSubL(L,b,flag)

% flag == 0, means L is naturally an lower-triangular matrix
% flag == 1, means L will be lower-triangular after transpose

if flag == 1
    L = L';
end

n = length(b);
y = zeros(n,1);
y(1) = b(1)/L(1,1);

for i = 2:n
    tmp = 0;
    for j = 1:i-1
        tmp = tmp + L(i,j)*y(j);
        fprintf('%f, %f, %f\n',L(i,j),y(j),tmp);
    end
    tmp = b(i) - tmp;
    y(i) = tmp/L(i,i);
    fprintf('tmp: %f, y(i): %f\n',tmp,y(i));
end


end
