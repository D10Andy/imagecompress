clc
clear all
 
X=imread('lena_256.jpg');
 X=double(X);
  Y1=dct2(X);
  
  
 subplot(1,3,2);
 imshow(uint8(Y1));
 title('DCT�任ͼ');