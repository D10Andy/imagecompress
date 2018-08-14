function out = CS(X, const_C, BLOCK_SIZE, INDEX, sparse_level, NUM)


[M, N] = size(X);
out = zeros(M,N);   % 使输入和输出的维数相同
B = BLOCK_SIZE;     % 分块处理的
block_size = B * B;
m = M /B;
n = N / B;
block_num = m * n;  % 小块的数量
Z = ones(M, N);     % 全1矩阵，作用？
mesur_num = zeros(1, m*n);  % 1*1024，作用？

ind = 1;
    for i = 1: m
        for j = 1: n
            % 对每一个小分块块分别处理

 
            temp1 = zeros(B, B);
            % 提取该分块的值
            temp1 = X(B*(i-1)+1 : B*i, B*(j-1)+1 : B*j);
            Y = dct2(temp1);    % 对该分块进行离散余弦变换
            %计算该块中0系数的个数
            
  %          Y1 = abs(Y);
           % Y2 = Y1 * 255;
           % Y3 = round(Y2);
  %          Y3 = round(Y1);
            
   %         temp_matrix = find(abs(Y3) < 1);
   %         [count1, count2] = size(temp_matrix);
   %         count = count1 * count2;
    %        matrix1D(ind) = count;
            
            %非0个数 即稀疏度
            
            
            %MER_NUM = round(const_C*sparse_level*log(block_size/sparse_level));  %有待调整
            MER_NUM = NUM;
            
            mesur_num(ind) = MER_NUM;
            ind = ind + 1;
        
            %merix to vector
            vector_X = matrix2vector(Y, B, B, INDEX);
            X1 = vector_X';
            %CS
            % randn是一个产生标准正态分布或矩阵的函数
            % MER_NUM = 32, B = 8   则会产生（32*8）的矩阵
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



