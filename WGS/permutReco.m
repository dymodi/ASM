%% permutReco Recover a permuted matrix/vector using the permute matrix p
% Note that if the input is a matrix, the row order is recovered
% August 20, 2015

function oriMat = permutReco(mat, p, m, n)

oriMat = zeros(m,n);
for i = 1:m
    oriMat(p(i),:) = mat(i,:);
end

end
