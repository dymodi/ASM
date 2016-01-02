% Add a constraint to the consInfo matrix according to its category
% Yi
% 12/28/15

function [consInfo,consInfoNum] = addToConsInfo(indexCons,consInfo,consInfoNum,nu,ny,M,P)
if indexCons <= nu*M
    nId = mod(indexCons,nu);
    if nId == 0
        nId = nu;
    end
elseif indexCons <= 2*nu*M
    nId = mod(indexCons,nu)+nu;
    if nId == nu
        nId = 2*nu;
    end
elseif indexCons <= (2*nu*M+ny*P)
    nId = mod(indexCons-2*nu*M,ny)+2*nu;
    if nId == 2*nu
        nId = 2*nu+ny;
    end
else
    nId = mod(indexCons-2*nu*M,ny)+2*nu+ny;
    if nId == 2*nu+ny
        nId = 2*nu+2*ny;
    end
end
consInfoNum(nId) = consInfoNum(nId) + 1;
consInfo(consInfoNum(nId),nId) = indexCons;
consInfo(1:consInfoNum(nId),nId) = sort(consInfo(1:consInfoNum(nId),nId));
end
