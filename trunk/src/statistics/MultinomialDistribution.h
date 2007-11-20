/* -*- Mode: C++; -*- */
/* VER: $Id: Distribution.h,v 1.3 2006/11/06 15:48:53 cdimitrakakis Exp cdimitrakakis $*/
// copyright (c) 2004-2007 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MULTINOMIAL_DISTRIUBION_H
#define MULTINOMIAL_DISTRIUBION_H

#include "Vector.h"
#include "Distribution.h"

class MultinomialDistribution : public VectorDistribution
{
protected:
	Vector p;
public:
	MultinomialDistribution(int n);
	virtual ~MultinomialDistribution();
	virtual void generate(Vector* x);
	virtual Vector generate();
	virtual real pdf(Vector* x);
};

#endif
