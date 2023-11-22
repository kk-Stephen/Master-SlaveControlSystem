import math
import numpy as np
def f(v_l,v_r,e_p):
    result = 0.80 * e_p - 0.74 * v_l + 0.01 * v_r - 0.02 * pow(e_p, 2) + 0.58 * e_p * v_l + 0.16 * e_p * v_r - 0.57 * pow(v_l, 2) - 0.52 * v_l * v_r - 0.12 * pow(v_r, 2)
    return result

def costf(we, wv, vl, vr, ep):
    cost = we * (pow(ep[1],2) + pow(ep[0], 2)) + wv * pow((vl - vr),2)
    return cost
e0 = 1.3
vl1 = 0.9826429931268026
vr1 = 1.1496637665611829
e1 = f(vl1, vr1,e0)
ep = [e0, e1]
# print(costf(0.8,0.2,vl1,vr1,ep))

def gradient(vl1,vr1,e0):
    return np.array([(2*vl1)/5 - (2*vr1)/5 + (8*((113*vl1)/100 - (57*e0)/100 + (13*vr1)/25 + 73/100)*((3*e0*e0)/200 - (57*e0*vl1)/100 - (159*e0*vr1)/1000 - (4*e0)/5 + (113*vl1*vl1)/200 + (13*vl1*vr1)/25 + (73*vl1)/100 + (3*vr1*vr1)/25 - (7*vr1)/1000))/5, (2*vr1)/5 - (2*vl1)/5 - (8*((159*e0)/1000 - (13*vl1)/25 - (6*vr1)/25 + 7/1000)*((3*e0*e0)/200 - (57*e0*vl1)/100 - (159*e0*vr1)/1000 - (4*e0)/5 + (113*vl1*vl1)/200 + (13*vl1*vr1)/25 + (73*vl1)/100 + (3*vr1*vr1)/25 - (7*vr1)/1000))/5])

def sgd(vl1,vr1,e0, learning_rate=0.01, num_epochs=100):
    for epoch in range(num_epochs):
        # 计算梯度
        grad = gradient(vl1,vr1,e0)
        e1 = f(vl1, vr1,e0)
        ep = [e0, e1]
        # 更新参数
        vl1 = vl1 - learning_rate * grad[0]
        vr1 = vr1 - learning_rate * grad[1]
        # 打印每轮的结果
        print(f"Epoch {epoch + 1}/{num_epochs}, vl1: {vl1},vr1: {vr1}, f(v_l,v_r,e_p): {costf(0.8,0.2,vl1,vr1,ep)}")

    return vl1,vr1


# 运行随机梯度下降
result = sgd(vl1,vr1,e0)
print(result[0],result[1])