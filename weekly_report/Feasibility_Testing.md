| Degree         | L       | R       | Delta |
| -------------- | ------- | ------- | ----- |
| 90             | 3800    | 4100    | 300   |
| 100            | 3500    | 3900    | 400   |
| 110            | 3500    | 4000    | 500   |
| 120            | 3650    | 4150    | 500   |
| 130            | 3800    | 4500    | 700   |
| 140            | 4000    | 4900    | 900   |
| 150            | 4100    | 5200    | 1100  |
| 160            | 3600    | 5300    | 1700  |
| 170极限        |         |         |       |
|                |         |         |       |
| 前车直发红外线 | 800-160 | 800-160 |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |
|                |         |         |       |

data from robot and build a model to generate best papemrters

linear regression to adjust PID

# Feasibility Testing

## Relationship between the angle of the reflection plane and the difference of bumper sensors

Purpose: Determine whether or not the difference of the bumper sensor will be linearly related to the angle of the reflection plane.

Methods: Rotate the reflective plane counterclockwise from 0 to 90 degrees and record the sensor difference.

Result: From 0 to 70 degrees, the sensor's difference is linearly related to the magnitude of the angle of rotation of the reflective plane.

![angle_sensor](D:\Github\Master-SlaveControlSystem\images\angle_sensor.jpg)

## Recognizability of turnaround signals from leaders

Purpose: Determine if the follower's sensors can distinguish between the infrared emitted by itself and the infrared emitted by the leader.

Methods: Rotate the leader robot and record the sensors values of follower.

Result: When the follower receives infrared light emitted by the leader, the value of its sensors are much lower.

<img src="D:\Github\Master-SlaveControlSystem\images\feedback_sig.jpg" alt="feedback_sig" style="zoom:50%;" />