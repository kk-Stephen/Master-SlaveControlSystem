# Master-SlaveControlSystem
Master-Slave Control System Based on Ant Queue Behavior for Confined Space Rescue: A Controller Comparison Study

# RS ASS2 Proposal

# Topic: **Master-Slave Control System Based on Ant Queue Behavior for Confined Space Rescue: A Controller Comparison Study**

## Task Domain / Context

我们将使用3个3Pi+组成受蚂蚁队列启发的主从控制系统。领导者通过反射传感器进行巡线和碰撞传感器进行障碍物规避，跟随者通过碰撞传感器对领导者进行跟随。我们将探索领导者和跟随着使用同种的控制器和不同控制器对该主从跟随系统的影响。

## Hypothesis

我们期待探索领导者使用巡线和碰撞传感器实现领导者在狭小空间中巡线与避障的可行性。同时得出在我的主从跟随系统中，跟随者应用不同控制器对其跟随性的影响。
通过应用Model Predictive Control(MPC)和碰撞传感器来实现三辆小车的主从控制（一个leader 2个follower）。我们期待提升小车沿指定路径行驶的表现，同时对比和PID以及BANG BANG的效果差异。


## Data & Results

记录主从系统完成巡线任务以及避障任务的成功率，以比较不同的控制器在该任务上的性能。

监控并记录任务过程中领导者和跟随者的传感器变化以尝试分析不同控制器表现纯在差异的原因。
最重要的数据是leader的路径跟踪误差以及follower的环境交互数据。路径跟踪误差帮助判断leader在被follower碰撞的过程中的行为变化。环境交互数据反映了follower的稳定性。除此之外，机器人的能量消耗数据也需要被收集从而比较不同策略间的优劣。


## Method

我们将在领导者和跟随者上分别实现bang-bang，PID和MPC控制器。并将拥有不同控制器的领导者和跟随者交叉组合进行实验并比较任务成功率。

实验场景包括：直线、曲线、弯道等。在不同场景分析不同组合的表现。

记录任务不成功时，领导者的反射传感器和碰撞传感器的数据，跟随者碰撞传感器的数据。与成功任务进行比较分析。


### What do you think will be your main Learning Achievement demonstrated in the report of your experiment conducted

探索我们的蚂蚁队列主从跟随系统在完成狭小空间救援任务的可行性。分析不同控制器对主从跟随系统性能的影响，总结不同控制器的适用场景。
The pros and cons of different control methods (MPC, PID, BANGBANG) to accomplish master-slave control comparison and analysis.
