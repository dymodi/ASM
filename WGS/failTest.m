clc;clear;
%load apiFail
%load apiFail2   % cond(H) = 1e9, float failed!
load apiFail3   % cond(H) = 1e8, float failed!
%load apiFail4   % cond(H) = 1e10, float failed!
%load apiFail5   % cond(H) = 1e8, float failed!
%load apiFail6   % cond(H) = 1e8, float failed!
%load apiFail7   % cond(H) = 1e8, float failed!
%load apiFail8   % cond(H) = 1e9, float failed!
%load apiFail9   % cond(H) = 1e8, float failed!
%load apiFail10  % cond(H) = 3e7, float failed!
%load apiFail11  % cond(H) = 1e9, float failed!

%mex -g wgsQPMEX.c;
%mex -g wgsQPMEX_double.c;


%% [z, time, iter] = wgsSolver(H, f, AA, lg, lx, ux, boxIndex, x0, wf_out, wl_out, precisionFlag)

[ndec,~] = size(H);



opts = optimoptions('quadprog','Algorithm','active-set','MaxIter',2000);
[z_quad,~,~,output] = quadprog(H,h,G,b,[],[],[],[],[],opts);
%[z_quad,~,~,output] = quadprog(H,h,G,b,[],[],[-inf*ones(12,1);-0.09],[inf*ones(12,1);0.09],[],opts);
iter_quad = output.iterations;


x0 = linprog(zeros(ndec,1),G,b);

invH = inv(H);
[x_asm, ~, iter_asm, ~] = asm(H,invH,h,-G,-b,x0,[],1000);

diff_asm_QUAD = abs(x_asm - z_quad);

[xStar,iter_wgs] = wgsQP(H,h,-G,[],[],-b,[],[],0,0,x0);

diff_wgs_QUAD = abs(xStar - z_quad);


[z,timeGw,iterGw] = wgsSolver(H,h,-G,-b,[],[],[],[],[],2);   
%[z,timeGw,iterGw] = wgsSolver(H,h,-G,-b,[-0.09],[0.09],[13],[],[],[],2);   

diff_wgsC_QUAD = abs(z - z_quad);
