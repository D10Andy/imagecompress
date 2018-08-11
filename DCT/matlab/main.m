%main.m
%主程序
function main(filename)
clc;
I=imread(filename);
I=im2double(I);
n=input('子图像小块的尺度(4≤n≤32)：');
while (n<=4)|(n>32)
    if n<=4
        disp('系数矩阵过小，请重新输入！');
    else
        disp('系数矩阵过大，请重新输入！');
    end
    n=input('设定系数矩阵大小(n×n)：');
end
mi=input('设定阈值λ(0＜λ＜1)：');
while mi>=1
    if mi<=0
        disp('λ值过小，请重新输入！');
    else
        disp('λ值过大，请重新输入！');
    end
    mi=input('设定阈值λ：');
end
disp('开始编码…………');
T=dctmtx(n);   %产生n×n的DCT系数矩阵块
B=blkproc(I,[n n],'P1*x*P2',T,T');   %计算二维DCT
B1=blkproc(B,[n n],'x.*((abs(x./P1)>1))',mi);    %阈值处理
[len,total]=RLE(B1);  %用行程编码压缩图像数据
[I2,maxm,maxn]=decode(n);%根据编码生成图像
imdisp(I,I2,mi,n,maxm,maxn,len,total);%自定义显示函数