%% A m-file used to form a spring-damper-mass system
% Related content can be found in the article
% Fast Model Predictive Control Using Online Optimization
% 关于原理的推导可以参看8月16日的科研记录

% M must be equal or greater than 2
function [A,B] = formMDS(M,k,c,m)

nx = 2*M;
nu = M-1;

A = zeros(nx,nx);
B = zeros(nx,nu);

A(1,2) = 1;
A(2,1) = -2*k/m;
A(2,2) = -2*c/m;
A(2,3) = k/m;
A(2,4) = c/m;
A(2*M-1,2*M) = 1;
A(2*M,2*M-3) = k/m;
A(2*M,2*M-2) = c/m;
A(2*M,2*M-1) = -k/m;
A(2*M,2*M) = -c/m;
for i = 2:M-1
    A(2*i-1,2*i) = 1;
    A(2*i,2*i-3) = k/m;
    A(2*i,2*i-2) = c/m;
    A(2*i,2*i-1) = -2*k/m;
    A(2*i,2*i) = -2*c/m;
    A(2*i,2*i+1) = k/m;
    A(2*i,2*i+2) = c/m;
end

B(2,1) = 1/m;
B(2*M,M-1) = -1/m;
for i = 2:M-1
   B(2*i,i-1) = -1/m; 
   B(2*i,i) = 1/m; 
end


end