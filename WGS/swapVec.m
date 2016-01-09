%% swapVec swap a vector v at two positions p1 and p2
% August 20, 2015

function v = swapVec(v,p1,p2)

item = v(p1,:);
v(p1,:) = v(p2,:);
v(p2,:) = item;

end