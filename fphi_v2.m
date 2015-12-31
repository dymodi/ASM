%fphi是自定义的计算参数F和φ的函数
%Version 2 @2014.4.15 for MIMO system

function [F,Phi] = fphi_v2(A_e,B_e,C_e,Np,Nc)
[m1,n1] = size(A_e);
[m2,n2] = size(B_e);
[m3,n3] = size(C_e);

%计算F阵与φ阵
%F = zeros(Np*m3,n1);
F = [];
for i=1:Np
    F = [F;C_e * A_e^i];
end
%v = zeros(Np*m3,n2);
v = [];
for i=1:Np 
    v = [v;C_e*A_e^(i-1)*B_e];
end
Phi = zeros(Np*m3,Nc*n2);
Phi(:,1:n2) = v;
for i=n2+1:n2:Nc*n2 
    %k = floor(i/n2);
    k = (i-1)/n2;
    Phi(:,i:i+n2-1)=[zeros(k*m3,n2);v(1:Np*m3-k*m3,1:n2)];
end
%BarRs=ones(Np,1);
%Phi_Phi= Phi'*Phi;
%Phi_F= Phi'*F;
%Phi_R=Phi'*BarRs;