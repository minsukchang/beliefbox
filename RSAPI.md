# Introduction #

Rollout sampling approximate policy iteration is a policy iteration algorithm that uses intelligent sampling of a Markov decision process via rollouts, so as to minimise the amount of time spent simulating to obtain an improved policy.

# References #

C. Dimitrakakis, M. Lagoudakis, "Rollout Sampling Approximate Policy Iteration", Machine Learning Journal, 2008

C. Dimitrakakis, M. Lagoudakis, "Algorithms and Bounds for Rollout Sampling Approximate Policy Iteration", European Workshop on Reinforcement Learning, 2008

These algorithms are implemented in

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/RSAPI.h

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/RSAPI.cc