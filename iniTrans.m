%% Transfer parameter H,c,A,b from MATLAB to DSP
% Mar.31,2016
% Yi Ding

function [flag,count_read] = iniTrans(s,H,c,A,b,invH,count_read)

% 通讯初始化
Token_read = 255;           % Read data from DSP
Token_write = 240;          % Write data to DSP
Token_init = 230;           % Initialization
Token_succ = 250;
temp_read = [];temp_write = [];temp_token=[];   %用来记录每个周期的buffer，查错
[mc,ndec] = size(A);
flag = 1;

mc = single(mc);
ndec = single(ndec);
H = single(H);
c = single(c);
A = single(A);
b = single(b);

%% Initialization
for k = 1:200
    Token = fread(s,1,'uint8');                     %循环读端口
    temp_token = [temp_token,Token];
    %fprintf('Token is %d\n',Token);
    if (Token == Token_init) && (count_read == 1)
        error('Wrong count_read!');
    elseif (Token == Token_init) && (count_read == 2)
        %% Init H
        %fprintf('H initialization.\n')
        for i = 1:ndec
            for j = 1:ndec
                Buffer_write = typecast([count_read,H(i,j)],'uint32');
                fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
                temp_write = [temp_write,Buffer_write];
                for kk = 1:20
                    Token = fread(s,1,'uint8');
                    temp_token = [temp_token,Token];
                    if Token == Token_succ
                        %fprintf('H(%d,%d) initialization successful.\n',i,j);
                        break;
                    end
                end
                if kk == 20
                    error('H initialization failed?');
                end
            end
        end
        count_read = count_read + 1;
    elseif (Token == Token_init) && (count_read == 3)
        %% Init c
        %fprintf('c initialization.\n')
        for i = 1:ndec
            Buffer_write = typecast([count_read,c(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('c(%d) initialization successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('c initialization failed?');
            end
        end
        count_read = count_read + 1;
    elseif (Token == Token_init) && (count_read == 4)
        %% Init A
        %fprintf('A initialization.\n')
        for i = 1:mc
            for j = 1:ndec
                Buffer_write = typecast([count_read,A(i,j)],'uint32');
                fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
                for kk = 1:20
                    Token = fread(s,1,'uint8');
                    if Token == Token_succ
                        %fprintf('A(%d,%d) initialization successful.\n',i,j);
                        break;
                    end
                end
                if kk == 20
                    error('A initialization failed?');
                end
            end
        end
        count_read = count_read + 1;
    elseif (Token == Token_init) && (count_read == 5)
        %% Init b
        %fprintf('b initialization.\n');
        for i = 1:mc
            Buffer_write = typecast([count_read,b(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('b(%d) initialization successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('b initialization failed?');
            end
        end
        count_read = count_read + 1;
    elseif (Token == Token_init) && (count_read == 6)
        %% Init invH
        %fprintf('invH initialization.\n');
        for i = 1:ndec
            for j = 1:ndec
                Buffer_write = typecast([count_read,invH(i,j)],'uint32');
                fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
                for kk = 1:20
                    Token = fread(s,1,'uint8');
                    if Token == Token_succ
                        %fprintf('invH(%d,%d) initialization successful.\n',i,j);
                        break;
                    end
                end
                if kk == 20
                    error('invH initialization failed?');
                end
            end
        end
        count_read = count_read + 1;
        break;
    end
end

end