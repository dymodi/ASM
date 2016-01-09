%% Generates random QPs with 
%  - dimensions n: optimization variables
%               mg: general contraints
%               mb: box constraints
%               asg: number of active general constraints
%               asb: number of active box constraints
%    
%  - condition number       (cond)
%  - # of active constraints at the optimum (as)
% 
%
%  The problem is in the form
%
%   min z'Hz+h'z
%   s.t.     A1z<=b1
%           lz<=z<=uz
%           OR
%           Az<=b
%
%..........................................................................
% (C) 2014-2015 by Gionata Cimini, Universit?Politecnica delle Marche

function [H,h,A,b,A1,b1,lz,uz,x_star]=generateQP(n,mg,mb,asg,asb,cond)

if asg>mg || asb>mb
    error('The number of constraints in the active set must be <= than the total number of constraints.')
end
if asg+asb>n
    error('The number of constraints in the active set must be <= than the number of optimization variables.')
end

% % % Generate random symmetric Q with given condition number, as in [1, p.127]
% %  %
% %  % [1] Bierlaire, Toint, Tuyttens, "On Iterative Algorithms for Linear LS Problems
% %  % with Bound Constraints", Linear Algebra and Its Applications, 143:111, 1991
% %  S=diag(exp(-log(cond)/4:log(cond)/2/(n-1):log(cond)/4));
% %  [U,~]=qr((rand(n,n)-.5)*200);
% %  [V,~]=qr((rand(n,n)-.5)*200);
% %  H=U*S*V';
% %  H=H'*H;

H=full(sprand(n,n,1,1/sqrt(cond)));         % generate the hessian with given condition number
H=(H*H')/2;                                 % make it symmpetric positive definite

while det(H) < 10^n
    H = H * 10;
end

A1=[];
if mg>0
    A1=full(sprand(mg,n,1,1));                  % generate the general constraints matrix
end
rg=randperm(mg,asg);                        % select randomly the active contraints (general)
rb=randperm(mb,asb)+mg;                     % select randomly the active contraints (box)
r=[rg,rb];                                  % collects all the active constraints
half_mb=ceil(mb/2);
% form the box matrix
Ae1=eye(half_mb);   Ae2=-eye(mb-half_mb);   
if ~isempty(Ae1)
    Ae1(1,n)=0;     Ae1=Ae1(:,randperm(n));
end
if ~isempty(Ae2)
Ae2(1,n)=0;     Ae2=Ae2(:,randperm(n));
end
uz=Inf*ones(n,1);     lz=-uz;

%% solve in the condensed for
A=[A1;Ae1;Ae2];   clear Ae1 Ae2;
x_star=randn(n,1);
for i=1:mg+mb
    if any(i==r)   
        b(i,1)=A(i,:)*x_star;
        u(i,1)=rand(1)*100;        
    else
        b(i,1)=A(i,:)*x_star+abs(randn)*100;
        u(i,1)=0;
    end
    if i>mg && i<mg+half_mb+1
        uz(A(i,:)==1)=b(i,1);
    elseif i>mg+half_mb
        lz(A(i,:)==-1)=-b(i,1);
    end
end
if(rank(A)<size(A,2))
    error('the matrix is not full rank')
end
h=-(H*x_star+A'*u);

%% split into box
b1=b(1:mg,:);
