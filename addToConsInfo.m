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
% The following only considers y
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

% The following considers constraints on u and y
% elseif indexCons <= 3*nu*M
%     nId = mod(indexCons,nu)+2*nu;
%     if nId == 2*nu
%         nId = 3*nu;
%     end
% elseif indexCons <= 4*nu*M
%     nId = mod(indexCons,nu)+3*nu;
%     if nId == 3*nu
%         nId = 4*nu;
%     end
% elseif indexCons <= 4*nu*M+2*ny*P
%     nId = mod(indexCons-4*nu*M,ny)+4*nu;
%     if nId == 4*nu
%         nId = 4*nu+ny;
%     end
% else
%     nId = mod(indexCons-4*nu*M,ny)+4*nu+ny;
%     if nId == 4*nu+ny
%         nId = 4*nu+2*ny;
%     end
% end


consInfoNum(nId) = consInfoNum(nId) + 1;
consInfo(consInfoNum(nId),nId) = indexCons;
consInfo(1:consInfoNum(nId),nId) = sort(consInfo(1:consInfoNum(nId),nId));
end
