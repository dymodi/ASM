

% QR decomposition based on Givens rotation

function [Q, R] = myqr(A)
[row,col] = size(A);
R = A;
Q = eye(row,row);

if row > col
    colTimes = col;
else
    colTimes = row-1;
end

for i = 1:colTimes
    for j = 1:row-i
        G = myplanerot([R(row-j,i);R(row-j+1,i)]); 
        disp([R(row-j,i);R(row-j+1,i)]);
        R = rowRot(R,G,row-j,row-j+1);
        Q = rowRot(Q,G,row-j,row-j+1);
        disp(R);
        disp(Q);
    end    
end


end