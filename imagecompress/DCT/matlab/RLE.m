%RLE.m
%用行程编码，压缩图像数据
function [len,total]=RLE(I)   %输入参数：I为二维图像数据；
                              %输出参数：①len为编码长度；②total为总的0个数
[m,n]=size(I);
code=[m,n]; %压缩图像数据
total=0;%系数为0的总个数
zero=0;%连续的‘0’的个数
data=0;%非‘0’的数
for ii=1:m;
    for jj=1:n;
        if I(ii,jj)==0;
            zero=zero+1;total=total+1;
        else
            data=I(ii,jj);
            code=[code,zero,data];%生成编码
            zero=0;%连续的‘0’个数清0
        end
    end
end
len=length(code);%编码长度
disp('编码生成完毕！');
save -double 'imcode.mat' code;
disp('编码保存在文件“imcode.mat”中！');