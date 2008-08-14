// -*- Mode: C++; -*-
// copyright (c) 2008 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TOY_UCT_SHOPPING_PROBLEM_H
#define TOY_UCT_SHOPPING_PROBLEM_H

#include "PolicyEvaluation.h"
#include "ValueIteration.h"
#include "BetaDistribution.h"
#include "Random.h"
#include "EasyClock.h"

#include <list>
#include <vector>
#include <set>

class BanditPrior {
public:
    std::vector<BetaDistribution> prior;
    BanditPrior()
    {
    }
    BanditPrior(std::vector<BetaDistribution> prior_)
        : prior(prior_)
    {}

    BanditPrior(int n_actions, real alpha, real beta)
    {
        for (int i=0; i<n_actions; i++) {
            prior.push_back(BetaDistribution(alpha, beta));
        }
    }
    BetaDistribution getActionReward(int action)
    {
        assert(action >= 0 && action < (int) prior.size());
        return prior[action];
    }
    BetaDistribution& ActionReward(int action)
    {
        assert(action >= 0 && action < (int) prior.size());
        return prior[action];
    }
};

/// a prior distribution on the number of arms
class BanditBelief
{
protected:
    int n_actions;
    BanditPrior prior;
public:
    BanditBelief()
    {
        n_actions = 0;
    }
    /// Create a belief
    BanditBelief(int n_actions_, real alpha, real beta)
        : n_actions(n_actions_),
          prior(n_actions, alpha, beta)
    {
    }
    ~BanditBelief()
    {
        for (int i=0; i<n_actions; i++) {
            //    delete prior[i];
        }
    }
    BanditPrior getPrior()
    {
        assert(n_actions > 0);
        return prior;
    }
    void update(int state, int action, real reward, int next_state)
    {
        assert (action >= 0 && action < n_actions);
        assert (approx_eq(reward, 0.0) || approx_eq(reward, 1.0));
        prior.ActionReward(action).calculatePosterior(reward);
    }

    real getProbability(int state, int action, real reward, int next_state)
    {
        assert (action >= 0 && action < n_actions);
        real p = prior.ActionReward(action).getMean();
        if (approx_eq(reward, 0.0)) {
                return 1.0 - p;
        } else if (approx_eq(reward, 1.0)) {
            return p;
        } else {
                fprintf (stderr, "Reward of %f is illegal for s,a=0,0\n", reward);
                exit(-1);
        }
        return 0.0;
    }
    
    /// Gives the greedy return starting from a particular state
    real getGreedyReturn(int state, real gamma)
    {
        std::vector<real> p(n_actions);
        int arg_max = 0;
        for (int i=0; i<n_actions; i++) {
            p[i] = prior.ActionReward(i).getMean();
            if (p[i] > p[arg_max]) {
                arg_max = i;
            }
        }
        real p_max = p[arg_max];
        real R = p_max;
        real U = R / (1.0 - gamma);
        return U;
    }

    /// Gives the Thompson return
    real sampleReturn(int state, real gamma)
    {
        std::vector<real> p(n_actions);
        int arg_max = 0;
        for (int i=0; i<n_actions; i++) {
            p[i] = prior.ActionReward(i).generate();
            if (p[i] > p[arg_max]) {
                arg_max = i;
            }
        }
        real p_max = p[arg_max];
        real R = p_max;
        real U = R / (1.0 - gamma);
        return U;
    }
};

template <typename BanditBelief>
class BeliefTree
{
protected:
    std::vector<Distribution*> densities;
public:
    class Edge;
    class Node
    {
    public:
        BanditBelief belief;
        int state;
        std::vector<Edge*> outs;
        int index;
        int depth;
        std::vector<real> U;
    };
    
    class Edge
    {
    public:
        Node* src; ///< source node
        Node* dst; ///< destination node
        int a; ///< action taken
        real r; ///< reward received
        real p; ///< probability of path
        Edge (Node* src_, Node* dst_, int a_, real r_, real p_)
            : src(src_), dst(dst_), a(a_), r(r_), p(p_)
        {
        }
    };

    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
    
    int n_states;
    int n_actions;
    BeliefTree(BanditBelief prior,
               int state,
               int n_states_,
               int n_actions_)
        :
        n_states(n_states_),
        n_actions(n_actions_)
    {
        Node* root = new Node;
        root->belief = prior;
        root->state = state;
        root->index = 0;
        root->depth = 0;

        nodes.push_back(root);
    }

    ~BeliefTree()
    {
        for (int i=densities.size() - 1; i>=0; --i) {
            delete densities[i];
        }

        for (int i=nodes.size() - 1; i>=0; --i) {
            delete nodes[i];
        }

        for (int i=edges.size() - 1; i>=0; --i) {
            delete edges[i];
        }
    }
    /// Return 
    Node* ExpandAction(int i, int a, real r, int s, int verbose = 0)
    {
        Node* next = new Node;
        next->belief = nodes[i]->belief;
        next->state = s;
        next->index = nodes.size();
        next->depth = nodes[i]->depth + 1;

        real p = nodes[i]->belief.getProbability(nodes[i]->state, a, r, s);
        next->belief.update(nodes[i]->state, a, r, s);

        
        edges.push_back(new Edge(nodes[i],
                                 next, //nodes[nodes.size()-1],
                                 a, r, p));

        int k = edges.size() - 1;
        if (verbose >= 100) {
            printf ("Added edge %d : %d --(%d %f %f)-> %d\n",
                    k,
                    edges[k]->src->index,
                    edges[k]->a,
                    edges[k]->r,
                    edges[k]->p,
                    edges[k]->dst->index);
        }
                
        nodes[i]->outs.push_back(edges[k]);

        nodes.push_back(next);
        return nodes.back();
    }

    /// Expand a node in the tree
    void Expand(int i, int verbose = 0)
    {
        for (int a=0; a<n_actions; a++) {
            // If we play, there are two possibilities
            ExpandAction(i, a, 1.0, 0, verbose);
            ExpandAction(i, a, 0.0, 0, verbose); 
        }
    }

    std::vector<Node*>& getNodes()
    {
        return nodes;
    }

    DiscreteMDP CreateMDP(real gamma, int verbose = 0)
    {
        int n_nodes = nodes.size();
        int terminal = n_nodes;

        DiscreteMDP mdp(n_nodes + 1, n_actions, NULL, NULL);
        for (int i=0; i<n_nodes + 1; i++) {
            for (int a=0; a < n_actions; a++) {
                for (int j=0; j<n_nodes+1; j++) {
                    mdp.setTransitionProbability(i, a, j, 0.0);
                }
                //mdp.setTransitionProbability(i, a, i, 0.0);
            }
        }
        // no reward in the first state
        {
            Distribution* reward_density = 
                new SingularDistribution(0.0);
            densities.push_back(reward_density);
            for (int a=0; a<n_actions; a++) {
                mdp.setRewardDistribution(0,
                                          a,
                                          reward_density);
            }
        }

        for (int i=0; i<n_nodes; i++) {
            int n_edges = nodes[i]->outs.size();
            if (verbose >= 90) {
                printf ("Node %d has %d outgoing edges\n", i, n_edges);
            }
            for (int j=0; j<n_edges; j++) {
                Edge* edge = nodes[i]->outs[j];
                Distribution* reward_density = 
                    new SingularDistribution(edge->r);
                
                densities.push_back(reward_density);
                mdp.setTransitionProbability(i,
                                             edge->a,
                                             edge->dst->index,
                                             edge->p);
                if (verbose >= 90) {
                    printf ("%d: - a=%d - r=%f - p=%f ->%d\n", i, edge->a, edge->r, edge->p, edge->dst->index);
                }
                for (int a=0; a<n_actions; a++) {
                    mdp.setRewardDistribution(edge->dst->index,
                                              a,
                                              reward_density);
                }
            }
            
            if (!n_edges) {
                real mean_reward = nodes[i]->belief.getGreedyReturn(nodes[i]->state, gamma);
                for (int a=0; a<n_actions; a++) {
                    mdp.setTransitionProbability(i, a, terminal, 1.0);

                    Distribution* reward_density = 
                        new SingularDistribution(mean_reward);
                    densities.push_back(reward_density);
                    mdp.setRewardDistribution(i, a, reward_density);
                }
            }
        }

        for (int a=0; a<n_actions; a++) {
            Distribution* reward_density = 
                new SingularDistribution(0.0);
            densities.push_back(reward_density);
            mdp.setTransitionProbability(terminal, a, terminal, 1.0);
            mdp.setRewardDistribution(terminal, a, reward_density);
        }
        
        return mdp;
    }
};


enum ExpansionMethod {
    SerialExpansion = 0,
    RandomExpansion,  //1
    HighestMeanValue, //2
    HighestDiscountedMeanValue, //3
    ThompsonSampling, // 4
    DiscountedThompsonSampling, //5
    ThompsonBound, // 6
    DiscountedThompsonBound, //7
    HighProbabilityBound, // 8
    DiscountedHighProbabilityBound, // 9
    HighProbabilityBoundOnly, // 10
    DiscountedHighProbabilityBoundOnly, // 11
    DiscountedMeanHighProbabilityBound // 12
};

int MakeDecision(ExpansionMethod expansion_method,
                 int n_states,
                 int n_actions,
                 BanditBelief prior,
                 int state,
                 real gamma,
                 int n_iter,
                 int verbose,
                 int max_value_iterations,
                 FILE* fout = NULL);


#endif
