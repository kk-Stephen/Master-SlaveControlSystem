import math
def f(v_l,v_r,e_p):
    result = -0.19106790564451598 + 1.01182957 * e_p - 0.8883062 * v_l + 1.04625623 * v_r + 2.11397743 * pow(e_p, 2) - 2.63160815 * e_p * v_l - 1.64255329 * e_p * v_r + 0.53318287 * pow(v_l, 2) - 0.11932006 * v_l * v_r - 0.05247556 * pow(v_r, 2) - 2.02088685 * pow (e_p, 3) + 5.24817082 * pow(e_p, 2) * v_l + 1.92340517 * pow(e_p, 2) * v_r - 4.77130578 * e_p * pow(v_l, 2) - 3.11973691 * e_p * v_l * v_r - 0.34055776 * e_p * pow(v_r, 2) + 1.53578212 * pow(v_l, 3) + 1.5739318 * pow(v_l, 2) * v_r + 0.3162112 * v_l * pow(v_r, 2) - 0.34074226 * pow(v_r, 3)
    return result
def costf(we, wv, vl, vr, ep):
    cost = we * pow(ep[0], 2)
    for i in range(0, 4):
        cost += we * ep[i+1] + wv * abs(vl[i] - vr[i])
    return cost

vl = [1,2,3]
vr = [1,2,3]
ep = [100, f(vl[0], vr[0]), f(vl[1], vr[1]), f(vl[2], vr[2])]