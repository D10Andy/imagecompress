%decode.m
%根据编码生成图像
function [recov,maxm,maxn]=decode(maxtri)   %输入参数：recov为恢复的解压缩图像
                                %输出参数：①recov是由编码恢复出的图像矩阵
                                %          ②maxm,maxn为恢复图像的规格
                                
%%%%%%%%%生成图像%%%%%%%%%%
fprintf('\n\n生成图像…………\n')
load imcode.mat %载入编码
len=length(code);%编码长度
index=1;        %当前码字
maxm=code(1);
maxn=code(2);      %读取图片size信息
imag=zeros(maxm,maxn);   %图片矩阵初始化为0
index=index+2;
m=1;n=1;        %当前矩阵的像素点
while index<len;
    zero=code(index);%连续的‘0’的个数
    index=index+1;
    data=code(index);
    index=index+1;
    if (n+zero)<=maxn%连续的zero个‘0’
        n=n+zero;
    elseif (n+zero-maxn)<=maxn
        m=m+1;
        n=n+zero-maxn;
    else
        m=m+ceil((n+zero)/maxn)-1;
        n=mod((n+zero),maxn);
    end
    imag(m,n)=data;	%**在非‘0’点，填上对应的系数值**
    if n<maxn
        n=n+1;
    else m<maxm
        n=1;
        m=m+1;
    end
end
T=dctmtx(maxtri);
recov=blkproc(imag,[maxtri maxtri], 'P1*x*P2',T',T); %DCT逆变换
disp('图像生成完毕！')

%%%%%%%%%%保存图像%%%%%%%%%
disp('*****************保存压缩图像*****************');
imname=input('文件名（无需拓展名）：','s');
imname=[imname,'(',int2str(maxtri),'×',int2str(maxtri),')','.png'];
imwrite(recov,imname);
fprintf('图像“%s”保存完毕！',imname);