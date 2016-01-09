% This is a first test of QR factorization WGS method
% July 30, 2015
% Yi @ZJU

clc;clear;

mL = 6;
nV = 6;

Av = rand(mL,nV);
Rv = triu(rand(nV,nV),0);

A = Av*inv(Rv);
[Q,R] = qr(A');
Yv = Q(:,1:mL);  % The choice of Y and L need to be checked when mL and nV changed
Lv = R(1:mL,:)';
Lv*Yv';

% 
% a = rand(1,nV);
% Av_bar = [A;a]
% q = linsolve(Rv',a');
% tau = 1;        % The choice of tau is of no reference
% z = tau*(eye(nV,nV)-Yv*Yv')*q;
% Yv_bar = [Yv,z];
% 
% l = Yv'*a';
% gamma = z'*a';
% Lv_bar = [Lv,zeros(mL,1);l',gamma];
% Lv_bar*Yv_bar'

%% 以下内容参照20150806的科研笔记
A_bar = A;
A_bar(6,:) = A(3,:);
A_bar(3:5,:) = A(4:6,:);
S = Lv;
S(6,:) = Lv(3,:);
S(3:5,:) = Lv(4:6,:);
S*Yv';

[G,y] = planerot([S(3,3);S(3,4)]);
P = formRot(G,3,4,6);
S'
P*S'
