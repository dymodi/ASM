%% colRot Rotation of two columns to produce zero on the right colum
% September 20, 2015

function mat = colRot(mat,G,i,j)

%matNew = mat;

% matNew(i,:) = G(1,:) * [mat(i,:);mat(j,:)];
% matNew(j,:) = G(2,:) * [mat(i,:);mat(j,:)];

matTmp = G * [mat(:,i)';mat(:,j)'];

mat(:,i) = matTmp(1,:)';
mat(:,j) = matTmp(2,:)';

end