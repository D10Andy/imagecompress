%main.m
%������
function main(filename)
clc;
I=imread(filename);
I=im2double(I);
n=input('��ͼ��С��ĳ߶�(4��n��32)��');
while (n<=4)|(n>32)
    if n<=4
        disp('ϵ�������С�����������룡');
    else
        disp('ϵ������������������룡');
    end
    n=input('�趨ϵ�������С(n��n)��');
end
mi=input('�趨��ֵ��(0���ˣ�1)��');
while mi>=1
    if mi<=0
        disp('��ֵ��С�����������룡');
    else
        disp('��ֵ�������������룡');
    end
    mi=input('�趨��ֵ�ˣ�');
end
disp('��ʼ���롭������');
T=dctmtx(n);   %����n��n��DCTϵ�������
B=blkproc(I,[n n],'P1*x*P2',T,T');   %�����άDCT
B1=blkproc(B,[n n],'x.*((abs(x./P1)>1))',mi);    %��ֵ����
[len,total]=RLE(B1);  %���г̱���ѹ��ͼ������
[I2,maxm,maxn]=decode(n);%���ݱ�������ͼ��
imdisp(I,I2,mi,n,maxm,maxn,len,total);%�Զ�����ʾ����