%% permut Permute a matrix/vector using the permute matrix p
% Note that if the input is a matrix, the row order is permuted
% August 20, 2015

function mat = permut(oriMat, p, m, n)

mat = zeros(m,n);
for i = 1:m
    mat(i,:) = oriMat(p(i),:);
end

end