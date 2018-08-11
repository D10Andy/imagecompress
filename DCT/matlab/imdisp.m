%imdisp.m
%用于显示原图像、压缩图像信息
function imdisp(I,I2,mi,maxtri,maxm,maxn,len,total)

%%%%%%%%%一、输出信息%%%%%%%%%%
fprintf('\n\n\n*******************输出结果*******************');
fprintf('\n图像规格：%d×%d',maxm,maxn);
fprintf('\n编码长度：%d',len);
rate=ceil(len/(maxm*maxn)*100);%计算压缩百分比
fprintf('\n理论压缩比例： 编码长度÷像素个数×100%c≈%d%c','%',rate,'%');
rate1=ceil(total/(maxm*maxn)*100);%失真估计:忽略的系数个数÷总系数个数
fprintf('\n图像失真估计： 忽略的系数÷总系数×100%c≈%d%c','%',rate1,'%');

%%%%%%%%%二、显示图像%%%%%%%%%
figure;imshow(I);title('原图像');
words=['λ=','0.'];
n=0;
while mi<1
    n=n+1;
    mi=mi*10;
end
for ii=1:n-1
    words=[words,'0'];
end
words=[words,int2str(mi),' (',int2str(maxtri),'×',int2str(maxtri),')'];
figure;imshow(I2);title(words);