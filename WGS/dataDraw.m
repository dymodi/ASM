%% Data plots and analysis for asm,wgs and quadprog
% August 20, 2015

%clc;clear;

%load timeData5
%load timeData6  % Date6 has the information of C code
%load timeData7  % Date7 has the information of C code
%load timeData8  % Date8 has the information of C code (single and double)
%load timeData9  % Date9 has the information of C code (single and double)(10 horizon)
%load timeData10  % Date10 has the information of C code (single)(6 horizon)
%load timeData11  % Date11 has the information of C code (single)(10 horizon) (All pass)
%load timeData12  % Date12 has the information of C code (single)(10 horizon) (All pass)
%load timeData13  % Date13 has the information of C code (single)(10 horizon) (All pass)
%load timeData14  % Date14 has Gurobi(10 horizon)
load timeData15  % Date15 has Gurobi(10 horizon)

NumberOfHorzion = 10;

gbBarrierMaxTime5 = zeros(NumberOfHorzion,1);
gbSimplexMaxTime5 = zeros(NumberOfHorzion,1);
quadMaxTime5 = zeros(NumberOfHorzion,1);
wgsCMaxTime5_single = zeros(NumberOfHorzion,1);
wgsCMaxTime5_double = zeros(NumberOfHorzion,1);

gbBarrierAvgTime5 = zeros(NumberOfHorzion,1);
gbSimplexAvgTime5 = zeros(NumberOfHorzion,1);
quadAvgTime5 = zeros(NumberOfHorzion,1);
wgsCAvgTime5_single = zeros(NumberOfHorzion,1);
wgsCAvgTime5_double = zeros(NumberOfHorzion,1);

for i = 1:NumberOfHorzion
    gbBarrierMaxTime5(i) = max(time_Record(:,i,1));
    gbSimplexMaxTime5(i) = max(time_Record(:,i,2));
    quadMaxTime5(i) = max(time_Record(:,i,3));    
    wgsCMaxTime5_single(i) = max(time_Record(:,i,4));
    wgsCMaxTime5_double(i) = max(time_Record(:,i,5));
     
    gbBarrierAvgTime5(i) = mean(time_Record(:,i,1));
    gbSimplexAvgTime5(i) = mean(time_Record(:,i,2));
    quadAvgTime5(i) = mean(time_Record(:,i,3));    
    wgsCAvgTime5_single(i) = mean(time_Record(:,i,4));
    wgsCAvgTime5_double(i) = mean(time_Record(:,i,5));
end

ftsz = 15;
lbsz = 18;
figure
semilogy(gbBarrierMaxTime5,'r-*','linewidth',2);hold on;
semilogy(gbSimplexMaxTime5,'b-s','linewidth',2);hold on;
semilogy(quadMaxTime5,'c-o','linewidth',2);hold on;
semilogy(wgsCMaxTime5_single,'k-v','linewidth',2);hold on;
semilogy(wgsCMaxTime5_double,'m-x','linewidth',2);
legend('Gurobi(Barrier)','Gurobi(Simplex)','QUADPROG','WGS-C single','WGS-C double');
xlabel('Horizon N','FontSize',lbsz);ylabel('Maximum time [s]','FontSize',lbsz);
set(gca,'XTickLabel',{'10','20','30','40','50','60','70','80','90','100'},'fontsize',ftsz);

figure
semilogy(gbBarrierAvgTime5,'r-*','linewidth',2);hold on;
semilogy(gbSimplexAvgTime5,'b-s','linewidth',2);hold on;
semilogy(quadAvgTime5,'c-o','linewidth',2);hold on;
semilogy(wgsCAvgTime5_single,'k-v','linewidth',2);hold on;
semilogy(wgsCAvgTime5_double,'m-x','linewidth',2);
legend('Gurobi(Barrier)','Gurobi(Simplex)','QUADPROG','WGS-C single','WGS-C double');
xlabel('Horizon N','FontSize',lbsz);ylabel('Average time [s]','FontSize',lbsz);
set(gca,'XTickLabel',{'10','20','30','40','50','60','70','80','90','100'},'fontsize',ftsz);


% %% Draw TMP data from Simulink
% [len,~] = size(u_Record);
% len = len - 1;
% 
% for i = 1:len
%     diff_Single(i,1) = norm(diff_Single(i,:));
%     diff_Double(i,1) = norm(diff_Double(i,:));
%     diff_QUAD(i,1) = norm(diff_QUAD(i,:));
% end
% 
% figure;
% subplot(2,1,1);plot(u_Record(1:len,:));title('Aircraft model,u');
% subplot(2,1,2);plot(y_Record(1:len,:));title('Aircraft model,y');
% figure; 
% semilogy(diff_Single(1:len,1));hold on;title('Error between solvers and MPC toolbox');
% semilogy(diff_Double(1:len,1));hold on;
% semilogy(diff_QUAD(1:len,1));hold on;
% legend('diff Single','diff Double','diff QUAD');
% figure; 
% semilogy(time(1:len,1));hold on; title('Runtime of WGS and QUADPROG');
% semilogy(time(1:len,2));hold on;
% semilogy(time(1:len,3));hold on;
% legend('time Single','time Double','time QUAD');
% figure; 
% plot(iter(1:len,1));hold on;    title('Iterations of WGS and QUADPROG');
% plot(iter(1:len,2));hold on;
% plot(iter(1:len,3)); hold on;
% legend('iter Single','iter Double','iter QUAD');



