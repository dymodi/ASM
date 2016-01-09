
% 自己写的 planerot 函数

function G = myplanerot(x)

if abs(x(2)) < 0.000001
    G = [1,0;0,1];
else
    r = norm(x);
    G = [x'; -x(2) x(1)]/r;    
end

end

