function RE_MATRIX = vector2matrix(RE_VECTOR, m, n, lable)

RE_MATRIX = zeros(m, n);
if lable == 1           %按行存
    for i = 1 : m
        RE_MATRIX(i, 1:n) = RE_VECTOR(n*(i-1)+1 : n*i);
    end;
end;
if lable == 0           %按列存
    for i = 1 : n
        RE_MATRIX(1:m, i) = RE_VECTOR(m*(i-1)+1 : m*i);
    end;
end;

    

