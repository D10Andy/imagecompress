function vector_X = matrix2vector(temp_matrix, m, n, lab)
 
vector_X = [];
if lab == 1          %按行
    for i = 1 : m
       vector_X(n*(i-1)+1 : n*i) = temp_matrix(i, 1 : n);
    end;
end;
if lab == 0      %按列
    for i = 1 : n
         vector_X(m*(i-1)+1 : m*i) = temp_matrix(1 : m, i);
    end;
end;

    
