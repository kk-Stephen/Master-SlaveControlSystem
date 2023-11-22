import math
import numpy as np
def f(v_l,v_r,e_p):
    result = -0.19106790564451598 + 1.01182957 * e_p - 0.8883062 * v_l + 1.04625623 * v_r + 2.11397743 * pow(e_p, 2) - 2.63160815 * e_p * v_l - 1.64255329 * e_p * v_r + 0.53318287 * pow(v_l, 2) - 0.11932006 * v_l * v_r - 0.05247556 * pow(v_r, 2) - 2.02088685 * pow (e_p, 3) + 5.24817082 * pow(e_p, 2) * v_l + 1.92340517 * pow(e_p, 2) * v_r - 4.77130578 * e_p * pow(v_l, 2) - 3.11973691 * e_p * v_l * v_r - 0.34055776 * e_p * pow(v_r, 2) + 1.53578212 * pow(v_l, 3) + 1.5739318 * pow(v_l, 2) * v_r + 0.3162112 * v_l * pow(v_r, 2) - 0.34074226 * pow(v_r, 3)
    return result

def costf(we, wv, vl, vr, ep):
    cost = we * pow(ep[0], 2)
    for i in range(0, 3):
        cost += we * ep[i+1] + wv * abs(vl[i] - vr[i])
    return cost
initial_e = 1.3
vl1 = 0
vl2 = 0
vl3 = 0
vr1 = 0
vr2 = 0
vr3 = 0
vl = [vl1,vl2,vl3]
vr = [vr1,vr2,vr3]
e1 = f(vl[0], vr[0],initial_e)
e2 = f(vl[1], vr[1],e1)
e3 = f(vl[2], vr[2],e2)

ep = [initial_e, e1, e2, e3]

print(costf(0.8,0.2,vl,vr,ep))



# def gradient():


# def sgd(x0, learning_rate=0.01, num_epochs=100):
#     x = x0.copy()  # 初始参数
#     for epoch in range(num_epochs):
#         # 计算梯度
#         grad = gradient(x)
#         # 更新参数
#         x = x - learning_rate * grad
#         # 打印每轮的结果
#         print(f"Epoch {epoch + 1}/{num_epochs}, x: {x}, f(x): {f(x)}")

#     return x

# # 设置初始参数
# initial_x = np.array([1.0, 2.0, -3.0, 4.0, -5.0, 6.0])

# # 运行随机梯度下降
# result = sgd(initial_x)