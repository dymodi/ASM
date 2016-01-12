% Update hpW, lpW, consInfo and consInfoNum in Constraints Selection
% strategy for dual ASM method (Delete a cons from working set)
% 2016/1/12 Yi DING
% In fact, we add the blockCons back to consInfo

function [hpW,lpW,consInfo,consInfoNum] = updatePW_del_dual(hpW,lpW,...
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
consInfoNum(ioId) = consInfoNum(ioId) + 1;
consInfo(consInfoNum(ioId),ioId) = blockCons;
% Cons in consInfo must be ordered
consInfo(1:consInfoNum(ioId),ioId) = sort(consInfo(1:consInfoNum(ioId),ioId));
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