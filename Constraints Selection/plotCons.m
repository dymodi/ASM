% This is a m code to plot constraints Ax <= b
% Now we only consider 2-dimensional cases
% Yi
% 12/29/15

%load cons

A = OMEGA_L;
b = omega_r;

x = -25:0.1:25;
for i = 1:length(b)    
    y = zeros(length(x),1);
    for j = 1:length(x)
        y(j) = (b(i) - A(i,1)*x(j))/A(i,2);
    end
    plot(x,y);axis([-30,30,-30,30]);
    hold on;
end