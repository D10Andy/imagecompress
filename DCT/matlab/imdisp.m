%imdisp.m
%������ʾԭͼ��ѹ��ͼ����Ϣ
function imdisp(I,I2,mi,maxtri,maxm,maxn,len,total)

%%%%%%%%%һ�������Ϣ%%%%%%%%%%
fprintf('\n\n\n*******************������*******************');
fprintf('\nͼ����%d��%d',maxm,maxn);
fprintf('\n���볤�ȣ�%d',len);
rate=ceil(len/(maxm*maxn)*100);%����ѹ���ٷֱ�
fprintf('\n����ѹ�������� ���볤�ȡ����ظ�����100%c��%d%c','%',rate,'%');
rate1=ceil(total/(maxm*maxn)*100);%ʧ�����:���Ե�ϵ����������ϵ������
fprintf('\nͼ��ʧ����ƣ� ���Ե�ϵ������ϵ����100%c��%d%c','%',rate1,'%');

%%%%%%%%%������ʾͼ��%%%%%%%%%
figure;imshow(I);title('ԭͼ��');
words=['��=','0.'];
n=0;
while mi<1
    n=n+1;
    mi=mi*10;
end
for ii=1:n-1
    words=[words,'0'];
end
words=[words,int2str(mi),' (',int2str(maxtri),'��',int2str(maxtri),')'];
figure;imshow(I2);title(words);