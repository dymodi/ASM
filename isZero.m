% 设计一个判断浮点数向量是否为0的函数
% 若向量x中的每一项都小于阈值theta，认为浮点数向量x为0
% 丁一
% 2014.12.8



function flag = isZero(x,theta)
flag = 1;

for i = 1:length(x)
   if (abs(x(i)) > theta) 
       flag = 0;
       break;
   end
end

end