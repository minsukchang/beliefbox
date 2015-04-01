# Introduction #

Inverse Reinforcement Learning is the problem of estimating the preferences and policy of an agent acting in a dynamic environment. In particular, this code implements:

**C. Dimitrakakis, C. Rothkopf, "Bayesian Multi-Task Inverse Reinforcement Learning", EWRL 2011.**

**C. Rothkopf, C. Dimitrakakis, "Preference elicitation and inverse reinforcement learning", ECML 2011.**


# Details #

The ECML paper describes a number of Markov Chain Monte Carlo methods for Bayesian inverse RL and preference elicitation. One of these includes estimation of the actual reward sequence that the agent observes during his lifetime. This model is implemented in

https://code.google.com/p/beliefbox/source/browse/trunk/src/models/PolicyRewardBelief.h

https://code.google.com/p/beliefbox/source/browse/trunk/src/models/PolicyRewardBelief.cc


The EWRL paper describes a generalisation of the first model to the case where the data is coming from multiple demonstrations, each with its own, unknown reward function. It then develops a hierarchical Bayesian models to estimate the distribution of reward functions for both the population and the individual demonstrations. This model is implemented in:

https://code.google.com/p/beliefbox/source/browse/trunk/src/models/PopulationPolicyRewardBelief.h

https://code.google.com/p/beliefbox/source/browse/trunk/src/models/PopulationPolicyRewardBelief.cc

> In addition, it introduces an alternative prior structure for inverse reinforcement learning, that is more efficient with larger amounts of data. This is implemented in:

https://code.google.com/p/beliefbox/source/browse/trunk/src/models/RewardPolicyBelief.h


https://code.google.com/p/beliefbox/source/browse/trunk/src/models/RewardPolicyBelief.cc
