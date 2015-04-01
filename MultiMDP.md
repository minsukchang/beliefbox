# Introduction #

This is a paper on obtaining better lower (but also upper) bounds in Bayesian reinforcement learning. This can be used both to evaluate the near-optimality of a policy, as well as to perform near-optimal action selection online.

# References #

C. Dimitrakakis, "Robust Bayesian reinforcement learning through tight lower bounds", EWRL 2011



# Code for Multi-MDP value iteration #

This code performs value iteration on a discrete distribution of MDPs in order to obtain a lower bound

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/MultiMDPValueIteration.h

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/MultiMDPValueIteration.cc

# Code for online algorithm #

This code uses the Multi-MDP Value Iteration algorithm to perform online action selection. Using the upper-bound option, action selection is performed using upper bounds instead.

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/SampleBasedRL.h

https://code.google.com/p/beliefbox/source/browse/trunk/src/algorithms/SampleBasedRL.cc