% 一个用于计算M_i的小函数
% 2015.6.29

function Mi = calMi(A,B,i,N)

[nx,nu] = size(B);

Mi = zeros(nx,nu*N);

for j = 0:i
    pos = j*nu;
    matrix = A^(i-j)*B;
    for k = 1:nx
        for l = 1:nu
            Mi(k,pos+l) = matrix(k,l);
        end
    end    
end

end
