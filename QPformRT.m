% 调节命题中计算QP命题参数的函数


function [H, F, G, W, E] = QPformRT(N, R, Q, A, B, C, D, c_ceil, c_floor, d_ceil, d_floor,CC)

global nu nx ny
global noc nic

noc = ny;


% 计算P_s, Q_s，就是推导中带方框的两个变量
%P = zeros(ny,ny); % 为了和输出跟踪命题一致
%P_s = zeros(ny*N,ny*N);
Q_s = zeros(nx*N,nx*N);
for i = 0:N-1
    pos = i*nx;
    for j = 1:nx
        matrix = CC'*Q*CC;
        for k = 1:nx
            %P_s(pos+j,pos+k) = P(j,k);
            Q_s(pos+j,pos+k) = matrix(j,k);
        end
    end 
end
Qbar = zeros(nx*N,ny);
for i = 0:N-1
    pos = i*nx;
    for j = 1:nx
        matrix = CC'*Q;
        for k = 1:ny
            Qbar(pos+j,k) = matrix(j,k);
        end
    end 
end


% 计算H
H11 = zeros(nu*N, nu*N);
for i = 0:N-1
    pos = i*nu;
    for j = 1:nu
        H11(pos+j, pos+j) = R(j,j);
    end
end

% 计算Mbar
Mbar = [];
for i = 0:N-1
    Mbar = [Mbar;calMi(A,B,i,N)];
end

% 计算B_s
B_s = zeros(nu*N,nu*N);
for i = 0:N-1
    posr = i*nu;
    for j = 0:N-1
        posc = j*nu;
        if (i >= j)
            matrix = eye(nu,nu);
            for l = 1:nu
                for m = 1:nu
                    B_s(posr+l,posc+m) = matrix(l,m);
                end
            end
        end
    end
end

H = H11 + B_s'*Mbar'*Q_s*Mbar*B_s;
H = 2*H;

% 计算Abar
Abar = zeros(ny*N,nx);
for i = 1:N
    pos = (i-1)*nx;
    matrix = A^i;
    for j = 1:nx
        for k = 1:nx
            Abar(pos+j,k) = matrix(j,k);
        end
    end
end

% 计算Ibar
Ibar = zeros(nu*N,nu);
for i = 0:N-1
    pos = i*nu;
    matrix = eye(nu,nu);
    for j = 1:nu
        for k = 1:nu
            Ibar(pos+j,k) = matrix(j,k);
        end
    end
end


% 计算F
F = [2*Abar'*Q_s*Mbar*B_s;2*Ibar'*Mbar'*Q_s*Mbar*B_s;-2*Qbar'*Mbar*B_s];

% 计算G
G1 = zeros(noc*N, nu*N);
G2 = zeros(nic*N, nu*N);
for i = 0:N-1
    for j = 0:i
        delta = i-j;
        block = CC*C*A^(delta)*B;
        row = i*noc;
        col = j*nu;
        for kr = 1:noc
            for kc = 1:nu
                G1(row+kr,col+kc) = block(kr,kc);
            end
        end
    end
end
for i = 0:N-1
    for j = 0:N-1
        row = i*nic;
        col = j*nu;
        if i == j
            for kr = 1:nic
                for kc = 1:nu
                    G2(row+kr,col+kc) = D(kr,kc);
                end
            end
        end
    end
end
Gu = [-G1;G1;-G2;G2];
G = Gu*B_s;

% 计算W
W1 = c_ceil*ones(noc*N,1);
W2 = -c_floor*ones(noc*N,1);
W3 = d_ceil*ones(nic*N,1);
W4 = -d_floor*ones(nic*N,1);
W = [-W1;-W2;-W3;-W4];

% 计算E
E1 = zeros(noc*N,nx);
for i = 0:N-1
    block = C*A^(i+1);
    for j = 1:noc
        for col = 1:nx
            E1(i*noc+j,col) = block(j,col);
        end
    end
end
E2 = zeros(nic*N,nx);
Erg = [E1;-E1;E2;E2];

E = [Erg,-Gu*Ibar,zeros(2*(noc*N+nic*N),ny)];

end