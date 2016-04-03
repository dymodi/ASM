%% Hardware In Loop simulation with DSP
% Test ASM solver and WGS solver in MPC problems
% Mar.30, 2016
% Yi Ding
% Solver1 = ASM, Solver2 = WGS;

% clc;clear;

% % Rotating antenna model
% H = [4.1404, 3.6272, 3.2295; 3.6272, 3.3613, 2.9082];
% c = [-21.0266;-18.3786;-15.9347];
% A = -[1,0,0;0,1,0;0,0,1;-1,0,0;0,-1,0;0,0,-1;1,0,0;1,1,0;1,1,1;-1,0,0;-1,-1,0;-1,-1,-1];
% b = -[1;1;1;1;1;1;2;2;2;2;2;2];
% x = [0;0;0];

% % 测例2
% H = [ 7,8.2,  8.7, 7;8.2,  9.8, 10.2, 8;8.7, 10.2, 11.7, 9;7, 8,  9, 10];
% c = [1;1;2;3];
% lub= [-4;-4;-4;-4;-4;-4;-4;-4;];
% lx = [-4;-4;-4;-4];
% ux = [4;4;4;4];
% lg = [2;-3];
% AA = [1,1,0,0;0,1,0,1];
% invH = inv(H);
% A = [eye(4,4);-eye(4,4);AA];
% b = [lub;lg];
% w = [3,9,10];
% x = [2;0;-4;-3];
% maxIter = 50;

% % Solver option
% solverOpt = 2;
% % Trans option (do we need to trans H and A)
% transOpt = 1;   % 1: yes we need; 0: no, we don't need

% %串口设置：
% s=serial('COM4');           %创建串口对象s，串口端号COM
% set(s,'BaudRate',115200);   %设定串口s的波特率
% set(s,'Timeout',10);        %设定串口s失效时间
% fopen(s);                   %打开串口s

function [z,time,iter] = dspSolver(H,c,A,b,x0,w,solverOpt,transOpt,s)

% 通讯初始化
Token_read = 255;           % Read data from DSP
Token_write = 240;          % Write data to DSP
Token_init = 230;           % Initialization
Token_succ = 250;
count_read = single(1);count_write = single(1); %读写校验初始化
temp_read = [];temp_write = [];temp_token=[];   %用来记录每个周期的buffer，查错

[mc,ndec] = size(A);
if ~isempty(x0)
    x = zeros(ndec,1);
    for i = 1:ndec
        x(i) = x0(i);
    end
end
if isempty(x0)
    opt.Display='off';
    x = linprog(zeros(ndec,1),-A,-b,[],[],[],[],[],opt);
    if min(A*x-b) < -1e-5
        error('Correction failed, Please offer a feasible starting point!');
    end
end

invH = inv(H);
mc = single(mc);   
ndec = single(ndec);
wSize = single(length(w));
H = single(H);
c = single(c);
A = single(A);
b = single(b);
x = single(x);
x_asm = single(zeros(ndec,1));
w = single(w);
invH = single(invH);

% Check initial working set
if ~isempty(w)
    for i = 1: wSize
        if max(abs(A(w(i),:)*x-b(w(i)))) > 0.0001
            error('Wrong initial working set.');
        end
    end
end

% Check solver option
if solverOpt ~= 1 && solverOpt ~= 2   
    error('Wrong solver option!');
end


%% Init mc, ndec and transOpt
Buffer_write = typecast([count_read,ndec,mc,transOpt],'uint32');%Buffer_write初始化
fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
for kk = 1:100
    Token = fread(s,1,'uint8');
    %fprintf('Token is %d\n',Token);
    if Token == Token_succ
        %fprintf('mc and ndec initialization successful.\n');
        count_read = count_read + 1;
        break;
    end
end

if transOpt == 1
    [~,count_read] = iniTrans(s,H,c,A,b,invH,count_read);
elseif transOpt == 0
else
    error('Wrong trans option!');
end

for ttt = 1:10
    Token = fread(s,1,'uint8');                     %循环读端口
    %fprintf('Token is %d\n',Token);
    if (Token == Token_read)
        %% Trans c
        %fprintf('Trans c.\n')
        for i = 1:ndec
            Buffer_write = typecast([count_read,c(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('Trans c(%d) successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('Trans c failed?');
            end
        end
        %% Trans b
        %fprintf('Trans b.\n')
        for i = 1:mc
            Buffer_write = typecast([count_read,b(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('Trans b(%d) successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('Trans b failed?');
            end
        end
        %% Trans x
        %fprintf('Trans x.\n')
        for i = 1:ndec
            Buffer_write = typecast([count_read,x(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('Trans b(%d) successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('Trans b failed?');
            end
        end
        %% Trans w
        %fprintf('Trans w.\n')
        Buffer_write = typecast([count_read,wSize],'uint32');
        fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
        for kk = 1:20
            Token = fread(s,1,'uint8');
            if Token == Token_succ
                %fprintf('Trans b(%d) successful.\n',i);
                break;
            end
        end
        for i = 1:wSize
            Buffer_write = typecast([count_read,w(i)],'uint32');
            fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
            for kk = 1:20
                Token = fread(s,1,'uint8');
                if Token == Token_succ
                    %fprintf('Trans b(%d) successful.\n',i);
                    break;
                end
            end
            if kk == 20
                error('Trans b failed?');
            end
        end
        %% Trans solver option
        %fprintf('Trans solver option.\n')
        Buffer_write = typecast([count_read,solverOpt],'uint32');
        fwrite(s,Buffer_write,'uint32');            %将准备好的数据写入
        for kk = 1:20
            Token = fread(s,1,'uint8');
            if Token == Token_succ
                %fprintf('Trans b(%d) successful.\n',i);
                break;
            end
        end
        count_read = count_read + 1;
    elseif (Token == Token_write)
        % Read xStar
        for i = 1:ndec
            Buffer_read = typecast(uint32(fread(s,2,'uint32')),'single');
            %fprintf('count_write is %d\n',count_write);
            %fprintf('Buffer_read is %d\n',Buffer_read)
            if(count_write ~= Buffer_read(1));          %count校验是否正确？
                error('Count_write verify failed!');    %报错
            else
                x_asm(i) = Buffer_read(2);
            end
        end
        Buffer_read = typecast(uint32(fread(s,2,'uint32')),'single');
        if(count_write ~= Buffer_read(1));          %count校验是否正确？
            error('Count_write verify failed!');    %报错
        else
            iter_DSP_ASM = Buffer_read(2);
        end
        Buffer_read = typecast(uint32(fread(s,2,'uint32')),'single');
        if(count_write ~= Buffer_read(1));          %count校验是否正确？
            error('Count_write verify failed!');    %报错
        else
            time_DSP_ASM = Buffer_read(2);
        end
        %count_write = count_write + 1;
        time = time_DSP_ASM;
        iter = iter_DSP_ASM;
        z = x_asm;
        return;
    end
end

