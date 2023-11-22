import math
def f(v_l,v_r,e_p):
    result = 0.80 * e_p - 0.74 * v_l + 0.01 * v_r - 0.02 * pow(e_p, 2) + 0.58 * e_p * v_l + 0.16 * e_p * v_r - 0.57 * pow(v_l, 2) - 0.52 * v_l * v_r - 0.12 * pow(v_r, 2)
    return result

def costf(we, wv, vl, vr, ep):
    cost = we * (pow(initial_e, 2) + pow(-0.19106790564451598 + 1.01182957 * initial_e - 0.8883062 * vl1 + 1.04625623 * vr1 + 2.11397743 * pow(initial_e, 2) - 2.63160815 * initial_e * vl1 - 1.64255329 * initial_e * vr1 + 0.53318287 * pow(vl1, 2) - 0.11932006 * vl1 * vr1 - 0.05247556 * pow(vr1, 2) - 2.02088685 * pow (initial_e, 3) + 5.24817082 * pow(initial_e, 2) * vl1 + 1.92340517 * pow(initial_e, 2) * vr1 - 4.77130578 * initial_e * pow(vl1, 2) - 3.11973691 * initial_e * vl1 * vr1 - 0.34055776 * initial_e * pow(vr1, 2) + 1.53578212 * pow(vl1, 3) + 1.5739318 * pow(vl1, 2) * vr1 + 0.3162112 * vl1 * pow(vr1, 2) - 0.34074226 * pow(vr1, 3), 2) +
    for i in range(0, 3):
        cost += we * ep[i+1] + wv * abs(vl[i] - vr[i])
    return cost

vl = [1,2,3]
vr = [1,2,3]
ep = [100, f(vl[0], vr[0]), f(vl[1], vr[1]), f(vl[2], vr[2])]