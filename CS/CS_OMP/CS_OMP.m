function re_matrix = CS_OMP(block_size, S, MER_MATRIX, sparse_level)

%���ָ����źŸ���
N = block_size;
[M, P] = size(S);
%��������
%if K<20
    m = 2*sparse_level;
%end;
%if K>=20
 %   m = M;
%end;

re_matrix = zeros(1,N);                             %  ���ع�������(�任��)����                     
Aug_t = [];                                         %  ��������(��ʼֵΪ�վ���)
r_n = S;                                            %  �в�ֵ
T = MER_MATRIX; 

product = [];
pos_array = [];
for times=1:m;                                    %  ��������
%times=1;
%while norm(r_n)>=10^-6
   % for col=1:N;                                  %  �ָ����������������
 %       product(col) = abs(T(:,col)'* r_n);          %  �ָ�������������Ͳв��ͶӰϵ��(�ڻ�ֵ)
    product = abs(T' * r_n);
        
%    end
    [val,pos] = max(product);                       %  ���ͶӰϵ����Ӧ��λ��
    Aug_t = [Aug_t,T(:,pos)];                       %  ��������
    T(:,pos) = zeros(M,1);                          %  ѡ�е������㣨ʵ����Ӧ��ȥ����Ϊ�˼��Ұ������㣩
    aug_y = (Aug_t'*Aug_t)^(-1)*Aug_t'* S;           %  ��С����,ʹ�в���С
    r_n = S - Aug_t * aug_y;                            %  �в�
    pos_array(times) = pos;                         %  ��¼���ͶӰϵ����λ��
  %  times=times+1;           %
end
re_matrix(pos_array) = aug_y;                           %  �ع�����������
%hat_x=real(Psi'*hat_y.');                         %  ���渵��Ҷ�任�ع��õ�ʱ���ź�
