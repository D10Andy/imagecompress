%RLE.m
%���г̱��룬ѹ��ͼ������
function [len,total]=RLE(I)   %���������IΪ��άͼ�����ݣ�
                              %�����������lenΪ���볤�ȣ���totalΪ�ܵ�0����
[m,n]=size(I);
code=[m,n]; %ѹ��ͼ������
total=0;%ϵ��Ϊ0���ܸ���
zero=0;%�����ġ�0���ĸ���
data=0;%�ǡ�0������
for ii=1:m;
    for jj=1:n;
        if I(ii,jj)==0;
            zero=zero+1;total=total+1;
        else
            data=I(ii,jj);
            code=[code,zero,data];%���ɱ���
            zero=0;%�����ġ�0��������0
        end
    end
end
len=length(code);%���볤��
disp('����������ϣ�');
save -double 'imcode.mat' code;
disp('���뱣�����ļ���imcode.mat���У�');