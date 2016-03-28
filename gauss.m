%% Gauss elimination for solving linear equations
% Algorithms according to Wikipedia
% Mar 25th, 2016

function [A] = gauss(A)

[row,col] = size(A);
iter = min([row;col]);
for k = 1:iter    
    [~,i_max] = max(abs(A(k:row,k)));
    i_max = i_max + k - 1;
    %disp(A);disp(i_max);
    if A(i_max,k) == 0
        error('Matrix is singular!');
    end
    tmpRow = A(k,:);
    A(k,:) = A(i_max,:);
    A(i_max,:) = tmpRow;
    for i = k+1:row
        m = A(i,k)/A(k,k);
        for j = k+1:col
            A(i,j) = A(i,j)-A(k,j)*m;
        end
        A(i,k) = 0;
    end    
end

end