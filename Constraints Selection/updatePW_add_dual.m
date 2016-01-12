% Update hpW, lpW, consInfo and consInfoNum in Constraints Selection
% strategy for dual ASM method (Add a cons from working set)
% 2016/1/12 Yi DING
% In fact, we remove the blockCons from consInfo

function [hpW,lpW,consInfo,consInfoNum] = updatePW_add_dual(hpW,lpW,...
    consInfo,consInfoNum,blockCons,ny,nu,M,P)

% Update consInfo (Here we only consider cons on u and y)
if blockCons <= nu*M
    ioId = mod(blockCons,nu);
    if ioId == 0
        ioId = nu;
    end 
elseif blockCons <= 2*nu*M
    ioId = mod(blockCons,nu)+nu;
    if ioId == nu
        ioId = 2*nu;
    end
elseif blockCons <= 2*nu*M+ny*P
    ioId = mod(blockCons-2*nu,ny)+2*nu;
    if ioId == 2*nu
        ioId = 2*nu+ny;
    end
else
    ioId = mod(blockCons-2*nu,ny)+2*nu+ny;
    if ioId == 2*nu+ny
        ioId = 2*nu+2*ny;
    end
end


rmId = find(consInfo(:,ioId)==blockCons);
if isempty(rmId)
    error('Cons to delete not found!');
end

for j = rmId:consInfoNum(ioId)-1
    consInfo(j,ioId) = consInfo(j+1,ioId);
end
consInfo(consInfoNum(ioId),ioId) = 0;
consInfoNum(ioId) = consInfoNum(ioId) - 1;

% Update hpW and lpW
hpW = [];
lpW = [];
for j = 1:length(consInfoNum)
    if consInfoNum(j) > 0
        hpW = [hpW;consInfo(1,j)];
        if consInfo(1,j) == 0
            error('Illegal Constraint!');
        end
    end
end
for j = 1:length(consInfoNum)
    if consInfoNum(j) > 1
        for k = 2:consInfoNum(j)
            lpW = [lpW;consInfo(k,j)];
            if consInfo(k,j) == 0
                error('Illegal Constraint!');
            end
        end
    end
end


end