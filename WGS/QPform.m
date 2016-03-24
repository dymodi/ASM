%% Compute the parameters used in a regulation problem
% N: Horizon


function [H, F, G, W, E] = QPform(N, R, P, Q, A, B, C, D, c_ceil, c_floor, d_ceil, d_floor)

global nu nx
global noc nic

% 计算H
H1 = zeros(nu*N, nu*N);
H2 = zeros(nu*N, nu*N);
for i = 0:N-1
    % 这里计算H2i
    if i == N-1
        H2i = B'*P*B;
    else
        H2i = B'*Q*B;
        for j = 1:N-i-2
            H2i = H2i+B'*(A^j)'*Q*(A^j)*B;
        end
        H2i = H2i + B'*(A^(N-i-1))'*P*(A^(N-i-1))*B;
    end
    pos = i*nu;
    for j = 1:nu
        H1(pos+j, pos+j) = R(j,j);
    end
    for kx = 1:nu
        for ky = 1:nu
            H2(pos+kx, pos+ky) = H2i(kx, ky);
        end
    end
end
H = H1 + H2;

% 计算F
F = zeros(nx, nu*N);
for i = 0:N-1
    % 这里计算Fi
    if i == N-1
        Fi = (A^N)'*P*B;
    else
        Fi = (A^N)'*P*A^(N-i-1)*B;
        for j = 0:N-i-2
            Fi = Fi + A^(i+1)'*Q*A^j*B;
        end
    end
    posX = i*nu + 1;
    for col = 1:nu
        for row = 1:nx
            F(row, posX+col-1) = Fi(row,col);
        end
    end    
end

% 计算G
G1 = zeros(noc*N, nu*N);
G2 = zeros(nic*N, nu*N);
for i = 0:N-1
    for j = 0:i
        delta = i-j;
        block = C*A^(delta)*B;
        row = i*noc;
        col = j*nu;
        for kr = 1:noc
            for kc = 1:nu
                G1(row+kr,col+kc) = block(kr,kc);
            end
        end
    end
end
if ~isempty(D)
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
    G = [-G1;G1;-G2;G2];
else
    G = [-G1;G1];
end

% 计算W
W1 = c_ceil*ones(noc*N,1);
W2 = -c_floor*ones(noc*N,1);
if ~isempty(D)
    W3 = d_ceil*ones(nic*N,1);
    W4 = -d_floor*ones(nic*N,1);
    W = [-W1;-W2;-W3;-W4];
else
    W = [-W1;-W2];
end

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
if ~isempty(D)
    E = [E1;-E1;E2;E2];
else
    E = [E1;-E1];
end

end