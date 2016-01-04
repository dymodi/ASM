% Update hpW and lpW with consInfo and consInfoNum
% In fact, it should be Create instead of Update
% Here we consider only non-antecedent

function [hpW,lpW] = updatePW(consInfo,consInfoNum)

hpW = []; lpW = [];
for i = 1:length(consInfoNum)
    if consInfoNum(i) > 0        
        % Only Consider no-antecedent
        hpW = [hpW;consInfo(1,i)];
        for j = 2:consInfoNum(i)
            lpW = [lpW;consInfo(j,i)];
        end

%         % Consider both no-antecedent and no-successive
%         hpW = [hpW;consInfo(1,i)];
%         if consInfoNum(i) > 1
%             hpW = [hpW;consInfo(consInfoNum(i),i)];
%         end
%         for j = 2:consInfoNum(i)-1
%             lpW = [lpW;consInfo(j,i)];
%         end        

    end        
end

hpW = sort(hpW);
lpW = sort(lpW);

end