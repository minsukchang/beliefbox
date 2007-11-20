/* -*- Mode: C++; -*- */
/* VER: $Id: Distribution.h,v 1.3 2006/11/06 15:48:53 cdimitrakakis Exp cdimitrakakis $*/
// copyright (c) 2006 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef DIRICHLET_H
#define DIRICHLET_H

#include "Distribution.h"
#include "MultinomialDistribution.h"

class DirichletDistribution : public VectorDistribution
{
protected:
    int n;
    Vector a;
public:
    DirichletDistribution(int n);
    virtual ~DirichletDistribution();
    virtual void generate(Vector* x);
    virtual Vector generate();
    virtual real pdf(Vector* x);
    virtual void update(Vector* x);
	Vector GetParameters();
};


#endif

