% Form the rotation matrix from the Givens rotations
% [G,y] = planerot(x)

function P = formRot(G,i,j,m)

P = eye(m,m);
P(i,i) = G(1,1);
P(j,j) = G(2,2);
P(i,j) = G(1,2);
P(j,i) = G(2,1);

end