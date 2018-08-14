function out = CS(X, const_C, BLOCK_SIZE, INDEX, sparse_level, NUM)


[M, N] = size(X);
out = zeros(M,N);   % ʹ����������ά����ͬ
B = BLOCK_SIZE;     % �ֿ鴦���
block_size = B * B;
m = M /B;
n = N / B;
block_num = m * n;  % С�������
Z = ones(M, N);     % ȫ1�������ã�
mesur_num = zeros(1, m*n);  % 1*1024�����ã�

ind = 1;
    for i = 1: m
        for j = 1: n
            % ��ÿһ��С�ֿ��ֱ���

 
            temp1 = zeros(B, B);
            % ��ȡ�÷ֿ��ֵ
            temp1 = X(B*(i-1)+1 : B*i, B*(j-1)+1 : B*j);
            Y = dct2(temp1);    % �Ը÷ֿ������ɢ���ұ任
            %����ÿ���0ϵ���ĸ���
            
  %          Y1 = abs(Y);
           % Y2 = Y1 * 255;
           % Y3 = round(Y2);
  %          Y3 = round(Y1);
            
   %         temp_matrix = find(abs(Y3) < 1);
   %         [count1, count2] = size(temp_matrix);
   %         count = count1 * count2;
    %        matrix1D(ind) = count;
            
            %��0���� ��ϡ���
            
            
            %MER_NUM = round(const_C*sparse_level*log(block_size/sparse_level));  %�д�����
            MER_NUM = NUM;
            
            mesur_num(ind) = MER_NUM;
            ind = ind + 1;
        
            %merix to vector
            vector_X = matrix2vector(Y, B, B, INDEX);
            X1 = vector_X';
            %CS
            % randn��һ��������׼��̬�ֲ������ĺ���
            % MER_NUM = 32, B = 8   ��������32*8���ľ���
            mer_matrix = randn(MER_NUM, B*B);
            Y4 = mer_matrix * X1;
            
            %OMP
            RE_VECTOR = CS_OMP(block_size, Y4, mer_matrix, sparse_level);
            
            %vector to matrix
            RE_MATRIX = vector2matrix(RE_VECTOR, B, B, INDEX);
            S = idct2(RE_MATRIX);
            Z(B*(i-1)+1 : B*i, B*(j-1)+1 : B*j) = S;

        end;
     end;
     
T_M = 0;

for i =1:block_num
    T_M = T_M + mesur_num(i);
end;
M_R = T_M/(M*N)
out = Z;



