% Code to generate test date for failed cases
% Uncomment different part for different use

% % For Mass-Damper system
% c = F'*x_k;
% AA = Gs;
% lg = Ws+Es*x_k;
% x = u_ini;

% For Gionata's testWGS
ndec = length(h);
nbc = 1;
opt.Display='off';
opt.Algorithm='active-set';
c = h;
AA = -G;
lg = -b;
lx = -10000000;
ux = 10000000;
x0 = linprog(zeros(ndec,1),-AA,-lg,[],[],[lx;-inf*ones(ndec-nbc,1)],[ux;inf*ones(ndec-nbc,1)],[],opt);
x = x0;

fid = fopen('H.txt','wt');
[m,n] = size(H);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',H(i,j));
    end
end
fclose(fid);

fid = fopen('c.txt','wt');
[m,n] = size(c);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',c(i,j));
    end
end
fclose(fid);

fid = fopen('AA.txt','wt');
[m,n] = size(AA);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',AA(i,j));
    end
end
fclose(fid);

fid = fopen('lg.txt','wt');
[m,n] = size(lg);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',lg(i,j));
    end
end
fclose(fid);

fid = fopen('lx.txt','wt');
[m,n] = size(lx);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',lx(i,j));
    end
end
fclose(fid);

fid = fopen('ux.txt','wt');
[m,n] = size(ux);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',ux(i,j));
    end
end
fclose(fid);

fid = fopen('x.txt','wt');
[m,n] = size(x);
for i = 1:m
    for j = 1:n
        fprintf(fid,'%g\n',x(i,j));
    end
end
fclose(fid);