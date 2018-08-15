# -*- coding: cp936 -*-
# optimization test, y = (x-3)^2
from matplotlib.pyplot import figure, hold, plot, show, xlabel, ylabel, legend


def f(x):
    "The function we want to minimize"
    return (x-3)**2


def f_grad(x):
        "gradient of function f"
        return 2*(x-3)


x = 0
y = f(x)
err = 1.0
maxIter = 300
curve = [y]
it = 0
step = 0.1
# 下面展示的是我之前用的方法，看上去貌似还挺合理的，但是很慢
while err > 1e-4 and it < maxIter:
    it += 1
    gradient = f_grad(x)
    new_x = x - gradient * step
    new_y = f(new_x)
    new_err = abs(new_y - y)
    if new_y > y:       # 如果出现divergence的迹象，就减小step size
        step *= 0.8
    err, x, y = new_err, new_x, new_y
    print ('err:', err, ', y:', y)
    curve.append(y)

print('iterations: ', it)
figure(); hold(True); plot(curve, 'r*-')
xlabel('iterations'); ylabel('objective function value')

# 下面展示的是backtracking line search，速度很快
x = 0
y = f(x)
err = 1.0
alpha = 0.25
beta = 0.8
curve2 = [y]
it = 0

while err > 1e-4 and it < maxIter:
    it += 1
    gradient = f_grad(x)
    step = 1.0
    while f(x - step * gradient) > y - alpha * step * gradient**2:
        step *= beta
    x = x - step * gradient
    new_y = f(x)
    err = y - new_y
    y = new_y
    print('err:', err, ', y:', y)
    curve2.append(y)

print('iterations: ', it)
plot(curve2, 'bo-')
legend(['gradient descent I used', 'backtracking line search'])
show()
