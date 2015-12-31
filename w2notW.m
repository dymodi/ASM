% 生成working set w 的补集 notW
% 2014.12.8
% dy

function notW = w2notW(w,mc)
notW = 1:mc;
for i = 1:length(w)
   notW(find(notW == w(i))) = [] ;
end
end