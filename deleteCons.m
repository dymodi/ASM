% Delete constraint from w and consInfo
% Yi
% 2015.12.28

function [w,consInfo,consInfoNum,hpW,lpW] = deleteCons(lambda,w,consInfo,consInfoNum,hpW,lpW)

if isempty(hpW)     % hpW is empty, we only consider lpW
    [~,index] = min(lambda);
    lpW(index) = [];
    indexCons = w(index);
    w(index) = [];
elseif isempty(lpW) % lpW is empty, we only consider hpW
    [~,index] = min(lambda);
    hpW(index) = [];   
    indexCons = w(index);
    w(index) = [];
else
    minLambdaHp = 100000000;
    minLambdaLp = 100000000; % Here thought 100000000 is large enough
    minIndexHp = 1;
    minIndexLp = 1;
    indexHpW = 1;
    indexLpW = 1;
    for j = 1:length(lambda)
        if indexHpW <= length(hpW) && hpW(indexHpW) == w(j)
            % Current constraint is a higher priority constraint
            if lambda(j) < minLambdaHp
                minLambdaHp = lambda(j);
                minIndexHp = indexHpW;
                indexWforHpW = j;
                if minLambdaHp < -0.0000001
                    break;      % 只要HP对于的lambda有小于0的就可以退出了
                end
            end
            indexHpW = indexHpW + 1;
        else
            % Current constraint is a lower priority constraint
            if lambda(j) < minLambdaLp
                minLambdaLp = lambda(j);
                minIndexLp = indexLpW;
                indexWforLpW = j;
            end
            indexLpW = indexLpW + 1;
        end
    end
    if minLambdaHp < -0.0000001     
        hpW(minIndexHp) = [];
        indexCons = w(indexWforHpW);
        w(indexWforHpW) = [];
    else       
        lpW(minIndexLp) = [];
        indexCons = w(indexWforLpW);
        w(indexWforLpW) = [];
    end
    
end

hasDelete = 0;
for i = 1:length(consInfoNum)
    if consInfoNum(i) > 0
        if (consInfo(consInfoNum(i),i) >= indexCons)
            for j = 1:consInfoNum(i)
                if (consInfo(j,i) == indexCons)
                    hasDelete = 1;
                    for k = j+1:consInfoNum(i)
                        consInfo(k-1,i) = consInfo(k,i);
                    end
                    consInfo(consInfoNum(i),i) = 0;
                    consInfoNum(i) = consInfoNum(i) - 1;
                end                
            end            
        end        
    end   
    if hasDelete == 1
        break;
    end
end

if hasDelete == 0
    error('Delete error!');
end

end