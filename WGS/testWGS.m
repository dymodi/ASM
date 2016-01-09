%..........................................................................
% (C) 2015 by Gionata Cimini
clc;clear;
%% init
%set(0,'defaulttextinterpreter','latex')
quadopt=optimoptions('quadprog');
quadopt.Algorithm='interior-point-convex';
quadopt.MaxIter=1000;
quadopt.TolCon=1.0000e-8; % default: 1e-8
quadopt.TolFun=1.0000e-8; % default: 1e-8
quadopt.TolX=1.0000e-8;   % default: 1e-8
quadopt.Display='none';

% %% Mex file preparation
% mex -g wgsQPMEX.c
% mex -g wgsQPMEX_double.c

%% params
nQP=10;             % the number of QPs (Gionata: 30)
maxIter=1000;

ntest=1;
% test1= general
% test2= box

%% test MEX file
[H,h,G,b,G1,b1,lz,uz,zstar]=generateQP(5,0,10,0,2,1e5); 
[z,~,~] = wgsSolver(H,h,-G1,-b1,lz,uz,[],[],[],2);

%% iter -------------------------------------------------------------------
range=5:1:15;
kmax=length(range);
for j=1:kmax
    i=range(j);
    %% generate the problem
    %%%%% m = randi([13 17],1,1);
    n=i*1;
    m=3*n;
    for k=1:nQP
        %% generate the problem
        [H,h,G,b,G1,b1,lz,uz,zstar]=generateQP(n,0,m,0,n-3,1e4);           
        %% solve the problem    
        quadTime = tic;
        [z,~,~,status]=quadprog(H,h,G1,b1,[],[],lz,uz,[],quadopt);
        timeQ(j,k)=toc(quadTime);
        iterQ(j,k)=status.iterations;
        zoptQ(j,k)=norm(z-zstar);
        
        [z,timeWb(j,k),iterWb(j,k)] = wgsSolver(H,h,-G1,-b1,lz,uz,[],[],[],1);
        zoptWb(j,k)=norm(z-zstar);
        if norm(z-zstar)>0.01
            a=1;
        end
        [z,timeW(j,k),iterW(j,k)] = wgsSolver(H,h,-G,-b,[],[],[],[],[],1);
        zoptW(j,k)=norm(z-zstar);
        %fprintf('det(H): %.8f\n', det(H));
        if zoptW(j,k) > 0.1
            fprintf('Error: %f\n', zoptW(j,k));
            SH = zeros(n,n);
            for i = 1:n
                SH(i,i) = 1/H(i,i);
            end
            H = SH'*H*SH;
            c = SH'*h;
            AA = -G * SH;
            while det(H) < 10^n
                H = H * 10;
                c = 10 * c;
            end            
            [z_scale,~,~] = wgsSolver(H,c,AA,-b,[],[],[],[],[],1);
            err = norm(SH*z_scale-zstar);
            %error('WGS failed!');
        end    

    end
    disp(j);
end
maxtimeQ=max(timeQ,[],2);   timeQ=mean(timeQ,2);     maxiterQ=max(iterQ,[],2);     iterQ=mean(iterQ,2);     zoptQ=max(zoptQ,[],2);      %QUADPROG                                                                               %QUADPROG
maxtimeW=max(timeW,[],2);   timeW=mean(timeW,2);    maxiterW=max(iterW,[],2);      iterW=mean(iterW,2);     zoptW=max(zoptW,[],2);      %WGS
maxtimeWb=max(timeWb,[],2);   timeWb=mean(timeWb,2);    maxiterWb=max(iterWb,[],2);      iterWb=mean(iterWb,2);     zoptWb=max(zoptWb,[],2);      %WGS


figure
subplot(3,1,1)
semilogy(range*5,timeQ,'r'); hold on; semilogy(range*5,timeW,'-.'); semilogy(range*5,timeWb,'k.-'); legend('quadprog','wgs','wgs box'); ylabel('Avg time'); xlabel('number of decision variables');
subplot(3,1,2)
semilogy(range*5,maxtimeQ,'r'); hold on; semilogy(range*5,maxtimeW,'-.'); semilogy(range*5,maxtimeWb,'k.-'); ylabel('Max time');xlabel('number of decision variables');
subplot(3,1,3)
semilogy(range*5,zoptQ,'r'); hold on;   semilogy(range*5,zoptW,'-.'); semilogy(range*5,zoptWb,'k.-');  ylabel('Error');xlabel('number of decision variables');
figure;
subplot(2,1,1)
plot(range*5,iterQ,'r'); hold on; plot(range*5,iterW); plot(range*5,iterWb,'k.-'); legend('quadprog','wgs','wgs box'); ylabel('Avg iter');xlabel('number of decision variables');
subplot(2,1,2)
plot(range*5,maxiterQ,'r'); hold on; plot(range*5,maxiterW); plot(range*5,maxiterWb,'k.-'); ylabel('Max iter');xlabel('number of decision variables');


