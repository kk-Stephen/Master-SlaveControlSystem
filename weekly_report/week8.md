# Model Predictive Control

## Parameters

- Controller sample time
- Prediction Horizon
- Control Horizon
- Constrains 
- Weights
  - Smooth
  - Setpoint tracking

## State variables 

Purpose: Define the position of the robot cart relative to the line.



Methods: Map the sensor values to the position of the car relative to the line.



$$e = {{2 ( R - L)} \over { R + L }} $$

## Control inputs

Velocity of left and right wheel.



$$v_l $$

and

$$v_r $$

## Mathematical model

Purpose: Relate the state variables and the control inputs for future prediction.



$$ {\Delta}e = f (v_l, v_r) $$


or


$$ e = f (v_l, v_r, e')$$

$$f(vl,vr,ep) = -0.191 + 1.012vl - 0.888vr + 1.046ep + 2.114vl^2 - 2.632vlvr - 1.643vlep + 0.533vr^2 - 0.119vrep + 0.052ep^2
- 2.021vl^3 + 5.248vl^2vr + 1.923vl^2ep - 4.771vlvr^2 - 3.120vlevr - 0.341vlep^2 + 1.536vr^3 + 1.574vr^2ep + 0.316vrep^2 - 0.341ep^3$$



### Challenge: How to generate the function $`f`$ ?

Propose methods:

- Available mathematical model
- Fit a function using machine learning method. **(Data?)**

## Cost function

Purpose: Make the cart reach the target point smoothly.

Methods: Determine the cost from smoothness and the cost from the target point.


$$ Cost = \sum\limits_{i = 0 }^{p} w_e e_{k+i}^2 + \sum\limits_{i = 0}^{p - 1}w_u \Delta u_{k+i}^{2} $$



where $$\Delta u = \left|v_l - v_r\right| - c$$

## Optimization

Purpose: Find the optimal control.

Methods: SGD / Adam
