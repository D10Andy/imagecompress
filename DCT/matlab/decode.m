%decode.m
%���ݱ�������ͼ��
function [recov,maxm,maxn]=decode(maxtri)   %���������recovΪ�ָ��Ľ�ѹ��ͼ��
                                %�����������recov���ɱ���ָ�����ͼ�����
                                %          ��maxm,maxnΪ�ָ�ͼ��Ĺ��
                                
%%%%%%%%%����ͼ��%%%%%%%%%%
fprintf('\n\n����ͼ�񡭡�����\n')
load imcode.mat %�������
len=length(code);%���볤��
index=1;        %��ǰ����
maxm=code(1);
maxn=code(2);      %��ȡͼƬsize��Ϣ
imag=zeros(maxm,maxn);   %ͼƬ�����ʼ��Ϊ0
index=index+2;
m=1;n=1;        %��ǰ��������ص�
while index<len;
    zero=code(index);%�����ġ�0���ĸ���
    index=index+1;
    data=code(index);
    index=index+1;
    if (n+zero)<=maxn%������zero����0��
        n=n+zero;
    elseif (n+zero-maxn)<=maxn
        m=m+1;
        n=n+zero-maxn;
    else
        m=m+ceil((n+zero)/maxn)-1;
        n=mod((n+zero),maxn);
    end
    imag(m,n)=data;	%**�ڷǡ�0���㣬���϶�Ӧ��ϵ��ֵ**
    if n<maxn
        n=n+1;
    else m<maxm
        n=1;
        m=m+1;
    end
end
T=dctmtx(maxtri);
recov=blkproc(imag,[maxtri maxtri], 'P1*x*P2',T',T); %DCT��任
disp('ͼ��������ϣ�')

%%%%%%%%%%����ͼ��%%%%%%%%%
disp('*****************����ѹ��ͼ��*****************');
imname=input('�ļ�����������չ������','s');
imname=[imname,'(',int2str(maxtri),'��',int2str(maxtri),')','.png'];
imwrite(recov,imname);
fprintf('ͼ��%s��������ϣ�',imname);