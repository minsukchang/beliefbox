This is a family of methods that perform Bayesian inference on variable order Markov models.

# Efficient implementation #

## src/statististics/ ##

  * ContextTree - The BVMM
  * ContextTreeBMC - The Bayesian Markov chain
  * ContextTreeCTW - A naive CTW implementation
  * ContextTreePPM - The PPM-C.

## src/statistics/tests ##

context\_tree\_test.cc - test sequence prediction

# Old implementation (deprecated) #

This one uses a stl/map for every depth (so D of trees of depth 1, ... , D) instead of an actual tree structure of depth D and so is very slow and memory hungry.