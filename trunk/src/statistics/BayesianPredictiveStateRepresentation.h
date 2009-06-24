/* -*- Mode: c++;  -*- */
/*VER: $Id: MarkovChain.h,v 1.7 2006/08/17 05:35:00 olethros Exp $*/
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef BAYESIAN_PSR_H
#define BAYESIAN_PSR_H

#include "BayesianMarkovChain.h"
#include <vector>
#include <map>
#include "Vector.h"

/**
   \ingroup StatisticsGroup
 */
/*@{*/


typedef std::map<int, real, std::greater<int> > BeliefMap;
typedef BeliefMap::iterator BeliefMapIterator;

/// A Markov Chain
class BayesianPredictiveStateRepresentation : public BayesianMarkovChain
{
public:
    std::vector<BeliefMap> beliefs;

    BayesianPredictiveStateRepresentation (int n_states, int n_models, float prior, bool dense = true);


    inline real get_belief_param(int model, int src)
    {
        BeliefMapIterator i = beliefs[model].find(src);
		if (i==beliefs[model].end()) {
			return 0.0;
		} else {
			return i->second;
		}
    }

    virtual ~BayesianPredictiveStateRepresentation();

    
    /* Training and generation */
    virtual void ObserveNextState (int state);
    virtual float NextStateProbability (int state);
    virtual void Reset();
    virtual int generate();
    virtual int generate_static();
    
};
/*@}*/
#endif