# Introduction #

This project implements a number of common algorithms for
problems in sequential inference and decision making.

It also includes some highly experimental code. The codebase
is extremely unstable and the API likely to change at any time.

This is a summary of the main features of the code-base:

# Algorithms #

- Expectation-Maximisation
- Gradient Bayesian RL
- Policy Iteration
- Q-Learning
- Rollout Classification Policy Iteration
- Rollout Sampling Approximate Policy Iteration
- Monte-Carlo Gradient Bayesian RL
- Monte-Carlo Upper and Lower bound Bayesian RL (extension of Thompson sampling)
- Multi-MDP Backwards Induction
- MWAL
- Sarsa
- Stochastic branch and bound for belief tree search (using MC bounds)
- Thompson sampling
- Value Iteration (with action elimination)
- UCB, UCRL

# Environments #

- Acrobot
- Bike
- Blackjack
- Cartpole
- ContextBandit
- Continuous Chain
- Corridor
- Discrete Chain
- Discretiser (for continuous environments)
- Double Loop
- Environment
- Gridworld
- Inventory management
- Linear context bandit
- Linear dynamic quadratic
- Mountaincar (2d and 3d)
- POMDP Maze
- Optimistic Task
- Puddleworld
- Random MDPs
- Riverswim

# Models #

- Bayesian Non-Parametric Conditional Density Estimation
- Conjugate Priors (e.g. Normal/Wishart, Multinomial/Dirichlet)
- Context Trees and Bayesian Variable Order Markov Models
- Hidden Markov Models
- Inverse Reinforcement Learning Models
- KNN classifier
- Linear classifiers
- MDP Models
- Multitask Inverse Reinforcement Learning Models
- Neural Networks

# Core Classes #

Matrices, Vectors, Graphs
KD-Trees, Cover Trees