%% swapMat swap a positive definite matrix m at two positions p1 and p2
% Achieve the function : H = Pi'*H*Pi; here Pi is the permute function

% August 20, 2015

function m = swapMat(m,p1,p2)

item = m(p1,:);
m(p1,:) = m(p2,:);
m(p2,:) = item;

item = m(:,p1);
m(:,p1) = m(:,p2);
m(:,p2) = item;

end