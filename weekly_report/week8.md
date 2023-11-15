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



### Challenge: How to generate the function $f$ ?

Propose methods:

- Available mathematical model
- Fit a function using machine learning method. **(Data?)**

## Cost function

Purpose: Make the cart reach the target point smoothly.

Methods: Determine the cost from smoothness and the cost from the target point.


$`{\sum_{n=1}^{10}}  n^2`$



$$ Cost = \sum\limits_{i = 0 }^{p}w*_ee_*{k+1}^2 + \sum\limits_{i = 0}^{p - 1}w*_u \Delta u_*{k+1}^{2} $$

$$ Cost = \sum_{i = 0 }^{p}w*_ee_*{k+1}^2$$

where $$\Delta u = \left|v_l - v_r\right| - c$$

## Optimization

Purpose: Find the optimal control.

Methods: SGD / Adam
