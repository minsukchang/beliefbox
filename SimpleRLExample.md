This page describes how to compile and run a simple reinforcement learning test-bench.

## Compilation ##

After downloading the source code, type

make

This should compile all the sub-directories.

Then enter the directory

src/algorithms/tests

and execute:

make online\_algorithms

If the process completes without errors, we are ready to run a small test.

## A small test ##

First, make sure the program runs. Do:

./bin/online\_algorithms --help

to get a list of options. As an example, try running the following command:

./bin/online\_algorithms --n\_runs 10 --environment Chain --gamma 0.95 --n\_steps 1000 --epsilon 0.0 --algorithm QLearning >out

This executes the QLearning algorithm on the Chain environment. All the run statistics are collected into the stdout, and you can use grep to extract the information you need. The most important ones are:

RUN\_REWARD - shows the total and discounted reward obtained in a run

EPISODE\_RETURN - shows the number of runs an episode number was reached, as well as the total and discounted reward obtained in that episode (only useful for episodic tasks)

INST\_PAYOFF - shows the average instantaneous payoff per time-step, with the first number being the number of runs the statistic was collected for