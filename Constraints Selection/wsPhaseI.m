% Modified Phase I, two LP
% First LP has equailty constraints based on previous optimal active set
% Second LP is invoked when first LP fails, and only give feasible point
% Details can be found in Research Note 20160305
% 2016.3.6
% Yi DING

function [x,LP1Fail,iniW] = wsPhaseI(OMEGA_L,omega_r,eqpSet,xtilde,flag)

LP1Fail = 0;
[mc,ndec] = size(OMEGA_L);
neq = length(eqpSet);
nic = mc - neq;
f = [zeros(ndec,1);ones(mc,1)];
ztilde = zeros(mc,1);
icSet = setdiff([1:mc]',eqpSet);
gammai = eye(neq,neq);
gammaj = -1*eye(nic,nic);
iniW = eqpSet;
Aec = [];

% If flag = 1, we solve from LP1,else we directly solve LP2
if flag == 1
    % LP1
    % Form Aeq and Ai
    if isempty(eqpSet)
        A = [OMEGA_L,gammaj;zeros(mc,ndec),-eye(mc,mc)];
        b = [omega_r;zeros(mc,1)];
        for i = 1:nic
            if ndec ~= length(xtilde)
                error('size error');
            end
            ztilde(i) = max([OMEGA_L(i,:)*xtilde-omega_r(i),0]);
        end
        utilde = [xtilde;ztilde];
        if max(A*utilde-b)>0.00001
            error('LP1 starting point infeasible');
        end
        u = linprog(f,A,b,[],[],[],[],utilde);
    else
        Aec = [];bec = [];
        Aic = [];bic = [];
        for j = 1:length(eqpSet)
            Aec = [Aec;OMEGA_L(eqpSet(j),:)];
            bec = [bec;omega_r(eqpSet(j),:)];
        end
        for j = 1:length(icSet)
            Aic = [Aic;OMEGA_L(icSet(j),:)];
            bic = [bic;omega_r(icSet(j),:)];
        end
        for i = 1:neq
            if Aec(i,:)*xtilde-bec(i) > 0
                gammai(i,i) = -1;
            end
        end
        Aeq = [Aec,gammai,zeros(neq,nic)];
        beq = bec;
        % A = [Aic,zeros(nic,neq),gammaj;zeros(nic,ndec),zeros(nic,neq),-eye(nic,nic)];
        % b = [bic;zeros(nic,1)];
        A = [Aic,zeros(nic,neq),gammaj;zeros(mc,ndec),-eye(mc,mc)];
        b = [bic;zeros(mc,1)];
        for i = 1:neq
            ztilde(i) = abs(Aec(i,:)*xtilde-bec(i));
        end
        for i = 1:nic
            ztilde(i+neq) = max([Aic(i,:)*xtilde-bic(i),0]);
        end
        utilde = [xtilde;ztilde];
        if max(A*utilde-b)>0.00001 || max(abs(Aeq*utilde-beq) > 0.00001)
            error('LP1 starting point infeasible');
        end
        u = linprog(f,A,b,Aeq,beq,[],[],utilde);
    end
    
    x = u(1:ndec);
    z = u(ndec+1:ndec+mc);
    
    if max(OMEGA_L*x-omega_r) > 1e-3 && max(abs(z)) < 0.0001
        LP1Fail = 1;
        % error('Infeasible initial point!');
    end
    
    if ~isempty(Aec)
        if max(abs(Aec*x-bec))> 0.0001
            disp('Wrong working set');
        end
    end
    
    if max(abs(z)) > 0.0001
        LP1Fail = 1;
    end
    
    if LP1Fail == 1 
        disp('LP1 infeasible, try solve LP2'); 
    else
        return
    end
end

% LP2
iniW = [];
gammaj = -1*eye(mc,mc);
A = [OMEGA_L,gammaj;zeros(mc,ndec),-eye(mc,mc)];
b = [omega_r;zeros(mc,1)];
for i = 1:mc
    if length(OMEGA_L(i,:)) ~= length(xtilde) || isempty(xtilde) || isempty(OMEGA_L(i,:))
        disp('dimension error');
    end
    ztilde(i) = max([OMEGA_L(i,:)*xtilde-omega_r(i),0]);
end
utilde = [xtilde;ztilde];
if max(A*utilde-b)>0.00001
    error('LP2 starting point infeasible');
end
u = linprog(f,A,b,[],[],[],[],utilde);
x = u(1:ndec);
z = u(ndec+1:ndec+mc);
if max(abs(z)) > 0.0001
    error('LP2 infeasible, no feasible starting point');
else
    
end