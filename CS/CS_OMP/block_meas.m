function y=block_meas(x,R);          %xΪ��Ҫ�ֿ���й۲�ľ���R�ǹ۲����

[m,n]=size(x);
m1=m/2;

obs_meas=R;
X1=x(1:m1,:);                     %��ԭ����ͼ�����ֳ���������
X2=x((m1+1):m,:);

y1=obs_meas*X1                 %��X1���й۲�
y2=obs_meas*X2                  %��X2���й۲�

y=[y1;y2];

