# Master-Slave Control System


## RS ASS2 Proposal

Topic: Master-Slave Control System Based on Ant Queue Behavior for Confined Space Rescue: A Controller Comparison Study


## Task Domain / Context

This study aims to design and evaluate a master-slave control system for three 3Pi+ robots, inspired by the queue formation behaviour of ants. The leader robot will use line-following sensors to follow a predefined path and collision sensors to avoid obstacles, while the follower robots will use bumper sensors to maintain a fixed distance from the leader. The main objectives of this study are: (1) to assess the feasibility of the leader robot performing line-following and obstacle avoidance tasks in confined spaces using only line-following and collision sensors; and (2) to investigate the impact of using different controllers for the leader and follower robots on the performance and robustness of the master-slave system.


# Hypothesis

We hypothesize that: (1) the leader robot will be able to perform line-following and obstacle avoidance tasks in confined spaces with a high success rate using only line-following and collision sensors; and (2) the follower robots will have different followability levels depending on the type of controller used for the master-slave system. We expect that the model predictive control (MPC) controller will provide the best performance and robustness for both the leader and follower robots, followed by the proportional-integral-derivative (PID) controller and the bang-bang controller.


# Data & Results

We will collect data on the success rates of the master-slave system in completing line-following and obstacle avoidance tasks under different scenarios and with different combinations of controllers. We will also record data from the leader’s reflection sensors and collision sensors, as well as the follower’s bumper sensors, when tasks are unsuccessful, to analyze the reasons for the failure. We will compare and contrast the performance of different controllers in various scenarios, and evaluate their strengths and weaknesses.


# Method
We will implement bang-bang, PID, and MPC controllers separately for the leader and follower robots. We will test different combinations of controllers for the master-slave system, such as MPC-MPC, MPC-PID, MPC-bang-bang, PID-PID, PID-bang-bang, and bang-bang-bang-bang. We will design different experimental scenarios to challenge the master-slave system, such as straight paths, curves, bends, intersections, narrow passages, etc. We will measure the success rates of the master-slave system in completing each scenario with each combination of controllers. We will also monitor and record sensor data from the leader and follower robots when tasks are unsuccessful, to identify the causes of failure. We will use statistical methods to analyze the data and compare the performance of different controllers in various scenarios.


# What do you think will be your main Learning Achievement demonstrated in the report of your experiment conducted
Explore the feasibility of our ant queue-inspired master-slave system in completing confined space assistance tasks. Analyze the impact of different controllers on the performance of the master-slave system and summarize the suitable scenarios for each controller. Evaluate and compare the advantages and disadvantages of different control methods (MPC, PID, BANGBANG) in accomplishing master-slave control.




