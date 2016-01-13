% Update hpW, lpW, consInfo and consInfoNum in Constraints Selection
% strategy for dual ASM method (Delete a cons from working set)
% 2016/1/12 Yi DING
% In fact, we add the blockCons back to consInfo

function [hpW,lpW,consInfo,consInfoNum,consHaveAct] = updatePW_del_dual(hpW,lpW,...
    consInfo,consInfoNum,consHaveAct,blockCons,ny,nu,M,P)

% Update consInfo (Here we only consider cons on u and y)
if blockCons <= nu*M
    ioId = mod(blockCons,nu);
    if ioId == 0
        ioId = nu;
    end 
    rowCons = floor((blockCons-1)/nu)+1;
elseif blockCons <= 2*nu*M
    ioId = mod(blockCons,nu)+nu;
    if ioId == nu
        ioId = 2*nu;
    end
    rowCons = floor((blockCons-nu*M-1)/nu)+1;
elseif blockCons <= 2*nu*M+ny*P
    ioId = mod(blockCons-2*nu,ny)+2*nu;
    if ioId == 2*nu
        ioId = 2*nu+ny;
    end
    rowCons = floor((blockCons-2*nu*M-1)/ny)+1;
else
    ioId = mod(blockCons-2*nu,ny)+2*nu+ny;
    if ioId == 2*nu+ny
        ioId = 2*nu+2*ny;
    end
    rowCons = floor((blockCons-2*nu*M-ny*P-1)/ny)+1;
end

if consInfo(rowCons,ioId) ~= -1
    error('ConsInfo update error!');
end
consInfo(rowCons,ioId) = blockCons;

for i = 1:consInfoNum(1,ioId)
    consHaveAct(1,ioId) = 0;
    if consInfo(i,ioId) == -1
        consHaveAct(1,ioId) = 1;
        break;
    end
end

% We try not to update hpW and lpW after delete a constraint
% New understanding of updating hpW and lpW
hpW = [];
lpW = [];
for i = 1:length(consInfoNum)
    if consHaveAct(1,i) == 0
        hpW = [hpW;consInfo(1,i)];
        for j = 2:consInfoNum(i)
            lpW = [lpW;consInfo(j,i)];
        end
    else
        for j = 1:consInfoNum(i)
            if (consInfo(j,i) == -1) && (j < consInfoNum(i)) && (consInfo(j+1,i)~= -1)
                hpW = [hpW;consInfo(j+1,i)];
            elseif (consInfo(j,i) ~= -1) && ( j == 1 || (consInfo(j-1,i) ~= -1))
                lpW = [lpW;consInfo(j,i)];
            end
        end
    end
end



% Wrong understanding of updating hpW and lpW
% consInfoNum(ioId) = consInfoNum(ioId) + 1;
% consInfo(consInfoNum(ioId),ioId) = blockCons;
% % Cons in consInfo must be ordered
% consInfo(1:consInfoNum(ioId),ioId) = sort(consInfo(1:consInfoNum(ioId),ioId));
% % Update hpW and lpW
% hpW = [];
% lpW = [];
% for j = 1:length(consInfoNum)
%     if consInfoNum(j) > 0
%         hpW = [hpW;consInfo(consHighInd(1,j),j)];
%         if consInfo(1,j) == 0
%             error('Illegal Constraint!');
%         end
%     end
% end
% for j = 1:length(consInfoNum)
%     if consInfoNum(j) > 1
%         for k = 1:consInfoNum(j)
%             if k ~= consHighInd(1,j)
%                 lpW = [lpW;consInfo(k,j)];
%                 if consInfo(k,j) == 0
%                     error('Illegal Constraint!');
%                 end
%             end
%         end
%     end
% end


end