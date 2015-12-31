% delete a specific constraint from umin,etc.
function [u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min] = deleteConstraint(u1max,u2max,u1min,u2min,y1max,y2max,y1min,y2min, indexCons, nu, M, ny, P)

if indexCons <= nu*M
    if mod(indexCons,2) == 1
        u1max(find(u1max==indexCons)) = [];
    else
        u2max(find(u2max==indexCons)) = [];
    end
elseif indexCons <= 2*nu*M
    if mod(indexCons,2) == 1
        u1min(find(u1min==indexCons)) = [];
    else
        u2min(find(u2min==indexCons)) = [];
    end
elseif indexCons <= (2*nu*M+ny*P)
    if mod(indexCons,2) == 1
        y1max(find(y1max==indexCons)) = [];
    else
        y2max(find(y2max==indexCons)) = [];
    end
else
    if mod(indexCons,2) == 1
        y1min(find(y1min==indexCons)) = [];
    else
        y2min(find(y2min==indexCons)) = [];
    end
end

end