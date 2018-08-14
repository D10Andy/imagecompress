function re_matrix = CS_OMP(block_size, S, MER_MATRIX, sparse_level)

%待恢复的信号个数
N = block_size;
[M, P] = size(S);
%迭代次数
%if K<20
    m = 2*sparse_level;
%end;
%if K>=20
 %   m = M;
%end;

re_matrix = zeros(1,N);                             %  待重构的谱域(变换域)向量                     
Aug_t = [];                                         %  增量矩阵(初始值为空矩阵)
r_n = S;                                            %  残差值
T = MER_MATRIX; 

product = [];
pos_array = [];
for times=1:m;                                    %  迭代次数
%times=1;
%while norm(r_n)>=10^-6
   % for col=1:N;                                  %  恢复矩阵的所有列向量
 %       product(col) = abs(T(:,col)'* r_n);          %  恢复矩阵的列向量和残差的投影系数(内积值)
    product = abs(T' * r_n);
        
%    end
    [val,pos] = max(product);                       %  最大投影系数对应的位置
    Aug_t = [Aug_t,T(:,pos)];                       %  矩阵扩充
    T(:,pos) = zeros(M,1);                          %  选中的列置零（实质上应该去掉，为了简单我把它置零）
    aug_y = (Aug_t'*Aug_t)^(-1)*Aug_t'* S;           %  最小二乘,使残差最小
    r_n = S - Aug_t * aug_y;                            %  残差
    pos_array(times) = pos;                         %  纪录最大投影系数的位置
  %  times=times+1;           %
end
re_matrix(pos_array) = aug_y;                           %  重构的谱域向量
%hat_x=real(Psi'*hat_y.');                         %  做逆傅里叶变换重构得到时域信号
