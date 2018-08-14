function y=block_meas(x,R);          %x为需要分块进行观测的矩阵，R是观测矩阵

[m,n]=size(x);
m1=m/2;

obs_meas=R;
X1=x(1:m1,:);                     %将原来的图像矩阵分成两个矩阵
X2=x((m1+1):m,:);

y1=obs_meas*X1                 %对X1进行观测
y2=obs_meas*X2                  %对X2进行观测

y=[y1;y2];

