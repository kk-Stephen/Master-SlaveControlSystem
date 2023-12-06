import seaborn as sns
import matplotlib.pyplot as plt

# Assuming you have success rates for each leader-follower pair
success_rates = [
    [1.0, 0.8, 0.0],  # Success rates for leader 'b' with followers 'b', 'w', 'p'
    [1.0, 0.7, 0.0],  # Success rates for leader 'w' with followers 'b', 'w', 'p'
    [1.0, 1.0, 0.1],  # Success rates for leader 'p' with followers 'b', 'w', 'p'
]

leaders = ['p', 'w', 'b']
followers = ['b', 'w', 'p']

# Create a heatmap using Seaborn
sns.set()
plt.figure(figsize=(8, 6))
ax = sns.heatmap(success_rates, annot=True, cmap="YlGnBu", fmt=".2f", xticklabels=followers, yticklabels=leaders)
plt.title('Success Rate of Leader-Follower Pairs')
plt.xlabel('Followers')
plt.ylabel('Leaders')
plt.show()