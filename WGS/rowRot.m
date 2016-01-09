%% rowRot Rotation of two rows to produce zero on the below row
% August 20, 2015

function mat = rowRot(mat,G,i,j)

%matNew = mat;

% matNew(i,:) = G(1,:) * [mat(i,:);mat(j,:)];
% matNew(j,:) = G(2,:) * [mat(i,:);mat(j,:)];

matTmp = G * [mat(i,:);mat(j,:)];

mat(i,:) = matTmp(1,:);
mat(j,:) = matTmp(2,:);

end