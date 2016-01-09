% This is a wrapper function that call wgsQP.c functions

clc;clear

%% Precision decide
precisionFlag = 2;  % 1: single precision, 2: double precision
if precisionFlag == 1
    mex -g wgsQPMEX.c
elseif precisionFlag ==2
    mex -g wgsQPMEX_double.c
else
    error('Wrong precisionFlag!');
end


%Data1  
H = [ 4.5267, -3.9095,  0.6937, -7.1302,  1.2138, -0.9079;
     -3.9095, 42.3583, -7.1494, 11.0149, -1.0405,  0.7782;
      0.6937, -7.1494,  3.3094, -2.8661,  0.3464, -0.2591;
     -7.1302, 11.0149, -2.8661, 41.4638, -6.8516,  5.1248;
      1.2138, -1.0405,  0.3464, -6.8516,  3.2103, -0.9053;
     -0.9079,  0.7782, -0.2591,  5.1248, -0.9053,  2.6771];
c = [16.8930; -53.6424; 9.4920; -47.2980; 7.3800; -5.5200];
lx= [-2;-2;-2;-2;-2;-2];
ux= [2;2;2;2;2;2];
lg = [-3;-3;-3;-3;-3;-3];
nbc = length(lx);
AA = [-0.2460,  0.1840,  0,       0,       0,       0;
    %-1,  1,  0,       0,       0,       0;
    -0.0704,  1.3926, -0.2460,  0.1840,  0,       0;
    -0.2467,  0.2115, -0.0704,  1.3926, -0.2460,  0.1840;
    0.2460, -0.1840,  0,       0,       0,       0;
    %1, -1,  0,       0,       0,       0;
    0.0704, -1.3926,  0.2460, -0.1840,  0,       0;
    0.2467, -0.2115,  0.0704, -1.3926,  0.2460, -0.1840];
wf = [11,12,0,0,0,0];
%wf = [7,0,0,0,0,0];
wl = [0,0,0,0,0,0];
%wl = [1,0,0,0,0,0];
nf = 2;
%nf = 1;
ml = 0;
%ml = 1;
x = [0;0;0;0;2;2];
%x = [2;-1;0;0;0;0];
ndec = 6;
ngc = 6;

% %Data2
% H = [ 7,    8.2,  8.7, 7;
%       8.2,  9.8, 10.2, 8;
%       8.7, 10.2, 11.7, 9;
%       7,    8,    9,  10];
% c = [1;1;2;3];
% lx= [-4;-4;-4;-4];
% ux = [4;4;4;4];
% lg = [2;-3];
% nbc = length(lx);
% AA = [1,1,0,0;0,1,0,1];
% wf = [3,0,0,0];
% wl = [1,2,0,0];
% nf = 1;
% ml = 2;
% x = [2;0;-4;-3];
% ndec = 4;
% ngc = 2;

% %Data3
% H = [ 7,    8.2,  8.7, 7;
%       8.2,  9.8, 10.2, 8;
%       8.7, 10.2, 11.7, 9;
%       7,    8,    9,  10];
% c = [1;1;2;3];
% lx = [-4;-4;-4;-4;];
% ux = [4;4;4;4];
% lg = [2;1];
% nbc = length(lx);
% AA = [1,1,0,0;1,0,1,0];
% wf = [4,0,0,0];
% wl = [0,0,0,0];
% nf = 1;
% ml = 0;
% x = [3;0;0;-4]; % 正确的测试初始值
% % x = [3;0;0;-3]; % 测试Error用的错误初值
% ndec = 4;
% ngc = 2;


% % C failed data 1
% load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\CfailedData1.mat');
% [ngc,ndec] = size(AA);
% nf = 0;
% ml = 0;
% nbc = length(lx);

    %% Memoray allocation for C code
    largeSize = max([ndec,ngc])+1;
    orderPermu = int32(zeros(ndec,1));
    H_ori = zeros(ndec,ndec);
    c_ori = zeros(ndec,1);
    Af = zeros(ndec,ndec);
    Lv = zeros(ndec,ndec);
    Yv = zeros(ndec,ndec);
    Rv = zeros(ndec,ndec);
    pvStar = zeros(ndec,1);
    p = zeros(ndec,1);
    gx = zeros(ndec,1);
    isInWl = int32(zeros(ngc,1));
    uv = zeros(ndec,1);
    vl = zeros(ndec,1);
    wv = zeros(ndec,1);
    lambdal = zeros(ndec,1);
    lambdaf = zeros(ndec,1);
    lambda = zeros(ndec,1);
    P_c = zeros(ndec,ndec);
    G_c = zeros(2,2);    
    tmpVec1 = zeros(largeSize,1);
    tmpVec2 = zeros(ndec,1);
    tmpMat1 = zeros(ndec,ndec);
    tmpMat2 = zeros(ndec,ndec);
    tmpMat3 = zeros(ndec,ndec);
    tmpMat4 = zeros(ndec,ndec);
    tmpMat5 = zeros(ndec,ndec);
    tmpMat6 = zeros(ndec,ndec);
    wf = int32(zeros(ndec,1));
    wl = int32(zeros(ndec,1));
    iter_c = int32(zeros(1,1));
    if precisionFlag == 1
        H_ori = single(H_ori);
        c_ori = single(c_ori);
        Af = single(Af);
        Lv = single(Lv);
        Yv = single(Yv);
        Rv = single(Rv);
        pvStar = single(pvStar);
        p = single(p);
        gx = single(gx);
        uv = single(uv);
        vl = single(vl);
        wv = single(wv);
        lambdal = single(lambdal);
        lambdaf = single(lambdaf);
        lambda = single(lambda);
        P_c = single(P_c);
        G_c = single(G_c);
        tmpVec1 = single(tmpVec1);
        tmpVec2 = single(tmpVec2);
        tmpMat1 = single(tmpMat1);
        tmpMat2 = single(tmpMat2);
        tmpMat3 = single(tmpMat3);
        tmpMat4 = single(tmpMat4);
        tmpMat5 = single(tmpMat5);
        tmpMat6 = single(tmpMat6);
    end
    H_c = H;
    c_c = c;
     AA_c = [];   
    for i=1:ngc
        AA_c = [AA_c;AA(i,:)'];
    end
    lg_c = lg;
    u_ini_c = x;
    if precisionFlag == 1
        xStar = wgsQPMEX(single(H_c),single(c_c),single(AA_c),...
            single(lg_c),single(lx),single(ux),wf,wl,single(u_ini_c), ...
            orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv, ...
            pvStar, p, gx, isInWl,uv,vl,wv, ...
            lambdal,lambdaf,lambda, P_c,G_c, ...
            tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6, 0, 0, iter_c, int32(1000));
    elseif precisionFlag == 2
        xStar = wgsQPMEX_double(H_c,c_c,AA_c,lg_c,lx,ux,wf,wl,u_ini_c, ...
            orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv, ...
            pvStar, p, gx, isInWl,uv,vl,wv, ...
            lambdal,lambdaf,lambda, P_c,G_c, ...
            tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6, 0, 0, iter_c, int32(1000));
    else
        error('Wrong precisionFlag!');
    end