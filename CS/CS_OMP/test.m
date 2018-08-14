%%****************************************************
% 测量数和迭代次数有待调整



clc;
clear all;
tic
C = 4;% 原值是4
B = 8;% 原值是8，   B是分块的大小
K = 16;% 原数据是8
M = 32;%选取的矩阵的行数 原数据是32ge
X_TEST = imread('lena_256.jpg');


[a,b] = size(X_TEST);
%subplot(1,2,1);
imshow(X_TEST);
title('lena256*256原图像');

in_X1= double(X_TEST);            %in_X1是0-255的数值
in_X = im2double(X_TEST);          %in_X1是0-1的数值    归一化后的值

index_col = 1;
out_Y1 = CS(in_X, C, B, index_col, K, M);
%index_row = 1;
%out_Y2 = CS(in_X, C, B, index_row, K, M);

%AVR_Y = (out_Y1+out_Y2)/2;
AVR_Y = out_Y1
%T_MSE = 0;
%Z1 = im2double(Z);

%for i = 1 : a
%    for j = 1 : b
 %      mse = (in_X(i,j) - AVR_Y(i,j))^2;
 %      T_MSE = mse + T_MSE ;
 %   end
%end

%subplot(1,2,2);


AVR_Y;
AVR_Y1 = AVR_Y * 255;
AVR_Y = round(AVR_Y1);
%for i = 1 : a
%    for j = 1 : b
%        mse = (X_TEST(i,j) - AVR_Y(i,j))^2;
%        T_MSE = mse + T_MSE ;
%    end
%end
figure;
imshow(AVR_Y, [0, 255]);
% title('OMP重构结果');
errorx=sum(sum(abs(AVR_Y1-in_X1).^2))   %  MSE误差
psnr=10*log10(255*255/(errorx/a/b))   %  PSNR
%  误差(PSNR)

%T_MSE = T_MSE * 255^2
%MSE = sqrt(T_MSE/(a*b))
%PSNR = 10 * log10(255^2/MSE)
toc


