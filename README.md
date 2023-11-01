# Master-Slave Control System
Master-Slave Control System Based on Ant Queue Behavior for Confined Space Rescue: A Controller Comparison Study

## RS ASS2 Proposal
Topic: Master-Slave Control System Based on Ant Queue Behavior for Confined Space Rescue: A Controller Comparison Study
Task Domain / Context
We will employ three 3Pi+ robots to create a master-slave control system inspired by ant queue behavior. The leader will utilize line-following sensors and collision sensors for obstacle avoidance, while the followers will use collision sensors to follow the leader. We aim to explore the feasibility of the leader performing line-following and obstacle avoidance tasks in confined spaces. Additionally, we will investigate the impact of using different controllers for the leader and followers within this master-slave system.

#Hypothesis
We expect to explore the feasibility of the leader performing line-following and obstacle avoidance in confined spaces using line-following and collision sensors. Simultaneously, we aim to assess the influence of applying different controllers to the followers in my master-slave system. We will implement Model Predictive Control (MPC) along with collision sensors to achieve master-slave control for the three robots (one leader and two followers). We anticipate enhancing the robots' performance in following a specified path and will compare the differences in effectiveness between MPC, PID, and BANG BANG controllers.

# Data & Results
Record the success rates of the master-slave system in completing line-following and obstacle avoidance tasks to compare the performance of different controllers in these tasks.

Monitor and record changes in sensors for the leader and followers during the tasks to analyze the potential differences in the performance of different controllers. The most critical data include the leader's path tracking error and the followers' environmental interaction data. Path tracking error helps assess the leader's behavioral changes when colliding with followers. Environmental interaction data reflects the stability of the followers. Additionally, data on energy consumption of the robots need to be collected to compare the merits of different strategies.

# Method
We will implement bang-bang, PID, and MPC controllers separately for the leader and followers. Different combinations of leaders and followers with different controllers will be experimented with and compared for task success rates.

Experimental scenarios include straight paths, curves, bends, etc. Performance of different combinations will be analyzed in various scenarios.

Record data from leader's reflection sensors and collision sensors when tasks are unsuccessful, as well as collision sensor data from the followers. This data will be compared and analyzed against successful tasks.

# What do you think will be your main Learning Achievement demonstrated in the report of your experiment conducted
Explore the feasibility of our ant queue-inspired master-slave system in completing confined space rescue tasks. Analyze the impact of different controllers on the performance of the master-slave system and summarize the suitable scenarios for different controllers. Evaluate and compare the advantages and disadvantages of different control methods (MPC, PID, BANGBANG) in accomplishing master-slave control.




