% 这是一个通过运行正常 asm 算法来检测 wgsQP 算法正确性的程序
% 具体内容见 2015年8月11日 科研笔记
% August. 11, 2015
% Yi

clc;clear;

% % 测例1
% H = [ 4.5267, -3.9095,  0.6937, -7.1302,  1.2138, -0.9079;
%     -3.9095, 42.3583, -7.1494, 11.0149, -1.0405,  0.7782;
%     0.6937, -7.1494,  3.3094, -2.8661,  0.3464, -0.2591;
%     -7.1302, 11.0149, -2.8661, 41.4638, -6.8516,  5.1248;
%     1.2138, -1.0405,  0.3464, -6.8516,  3.2103, -0.9053;
%     -0.9079,  0.7782, -0.2591,  5.1248, -0.9053,  2.6771];
% c = [16.8930; -53.6424; 9.4920; -47.2980; 7.3800; -5.5200];
% lub= [-2;-2;-2;-2;-2;-2;-2;-2;-2;-2;-2;-2];
% lx = [-2;-2;-2;-2;-2;-2];
% ux = [2;2;2;2;2;2];
% lg = [-3;-3;-3;-3;-3;-3];
% AA = [-1,  1,  0,       0,       0,       0;
%     -0.0704,  1.3926, -0.2460,  0.1840,  0,       0;
%     -0.2467,  0.2115, -0.0704,  1.3926, -0.2460,  0.1840;
%     1, -1,  0,       0,       0,       0;
%     0.0704, -1.3926,  0.2460, -0.1840,  0,       0;
%     0.2467, -0.2115,  0.0704, -1.3926,  0.2460, -0.1840];
% invH = inv(H);
% 
% A = [eye(6,6);-eye(6,6);AA];
% b = [lub;lg];
% x = [2;-1;0;0;0;0];
% w = [7,13];
% wf = [7];
% wl = [1];
% nf = 1;
% ml = 1;
% maxIter = 50;

% 测例2
H = [ 7,    8.2,  8.7, 7;
      8.2,  9.8, 10.2, 8;
      8.7, 10.2, 11.7, 9;
      7,    8,    9,  10];
c = [1;1;2;3];
lub= [-4;-4;-4;-4;-4;-4;-4;-4;];
lx = [-4;-4;-4;-4];
ux = [4;4;4;4];
lg = [2;-3];
AA = [1,1,0,0;0,1,0,1];
invH = inv(H);

A = [eye(4,4);-eye(4,4);AA];
b = [lub;lg];
x = [2;0;-4;-3];
w = [3,9,10];
maxIter = 50;

% % 测例3
% H = [ 7,    8.2,  8.7, 7;
%       8.2,  9.8, 10.2, 8;
%       8.7, 10.2, 11.7, 9;
%       7,    8,    9,  10];
% c = [1;1;2;3];
% lub= [-4;-4;-4;-4;-4;-4;-4;-4;];
% lg = [2;1];
% AA = [1,1,0,0;1,0,1,0];
% invH = inv(H);
% A = [eye(4,4);-eye(4,4);AA];
% b = [lub;lg];
% x = [3;0;0;-4];
% w = [4];
% maxIter = 50;


% % 来自于测试失败时的测例
% %load failedData1
% %load failedData2
% %load failedData3
% %load failedData4
% %load failedData5
% load wgsFail2
% ndec = length(H_ori);
% invH = inv(H_ori);
% A = [eye(ndec,ndec);-eye(ndec,ndec);AA];
% b = [lx;-ux;lg];

% % 其他一些 wgs 错误的数据
% %load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\wgsFailData1.mat');
% load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\wgsFail1.mat');
% ndec = length(c);
% invH = inv(H);
% A = [eye(ndec,ndec);-eye(ndec,ndec);AA];
% b = [lx;-ux;lg];

% % 对float进行测试的一些测例 (只有General Constraints的情况)
% %load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\floatFail1.mat');
% %load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\floatFail2.mat');
% load('D:\Users\Yi\Documents\MATLAB\DSP\WGS\floatFail3.mat');
% % Scaling
% ndec = length(c);
% 
% % SH = zeros(ndec,ndec);
% % for i = 1:ndec
% %     SH(i,i) = 1/H(i,i);
% % end
% % H = SH'*H*SH;
% % c = SH'*c;
% % AA = AA * SH;
% % x0 = linsolve(SH,x0);
% 
% 
% invH = inv(H);
% A = AA;
% b = lg;
% %x = x0;

model.Q = sparse(0.5*H);
model.A = sparse(AA);
model.obj = c;
model.rhs = lg;
model.sense = '>';
model.lb = lx;
model.ub = ux;

%gurobi_write(model, 'qp.lp');
results = gurobi(model);
x_gb = results.x;

opts = optimoptions('quadprog','Algorithm','active-set');
x_quad = quadprog(H,c,-A,-b,[],[],[],[],[],opts);

%[x_asm, ~, iterStar, ~] = asm(H,invH,c,A,b,x,[],100);

x_wgs = wgsQP(H,c,AA,lx,ux,lg,[],[],0,0,x);


%diff_asm_quad = max(abs(x_asm-x_quad));
diff_wgs_quad = max(abs(x_wgs-x_quad));


0.5*x_wgs'*H*x_wgs + c'*x_wgs
