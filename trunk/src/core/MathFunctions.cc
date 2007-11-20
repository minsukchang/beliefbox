// -*- Mode: c++ -*-
/* VER: $Id: MathFunctions.c,v 1.2 2006/11/06 15:48:53 cdimitrakakis Exp cdimitrakakis $ */
// copyright (c) 2004 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "MathFunctions.h"
#include <cmath>
#include <cassert>





/// Softmax an array \f$p_i = e^{\beta Q_i}/\sum_j^n{e^{\beta Q_i}}\f$
void SoftMax (int n, real* Q, real* p, real beta)
{
    real sum = 0.0;

    // Necessary for avoiding infinities.
    int arg_max = ArgMax(n, Q);
    real max = Q[arg_max];

    for (int i=0; i<n; i++) {
        p[i] = exp (beta * (Q[i]-max));
        sum += p[i];
    }
    sum = 1.0/sum;
    for (int i=0; i<n; i++) {
        p[i] *= sum;
    }
}
    
/// Softmin an array \f$p_i = e^{-\beta Q_i}/\sum_j^n{e^{-\beta Q_i}}\f$
void SoftMin (int n, real* Q, real* p, real beta)
{
    real sum = 0.0;

    // Necessary for avoiding infinities.
    int arg_min = ArgMin(n, Q);
    real min = Q[arg_min];

    for (int i=0; i<n; i++) {
        p[i] = exp (-beta * (Q[i]-min));
        sum += p[i];
    }
    sum = 1.0/sum;
    for (int i=0; i<n; i++) {
        p[i] *= sum;
    }
}
    
    
/// Normalise a vector to a destination vector (low level)
///
/// src is the source vector.
/// dst is the destination vector.
/// n_elements is the number of elements. 
/// As pointers are raw, make sure n_elements is correct.
/// It is safe for src and dst to point at the same vector.
void Normalise (real* src, real* dst, int n_elements)
{
    real sum = 0;
    for (int i=0; i<n_elements; i++) {
        sum += src[i];
    }
    if (sum==0) {
        for (int i=0; i<n_elements; i++) {
            dst[i] = src[i];
        }
        return;
    }
    assert(sum>0);
    for (int i=0; i<n_elements; i++) {
        dst[i] = src[i]/sum;
    }
}

/// Return \f$|\sum_i^n (a_i-b_i)^2|\f$
real SquareNorm (real* a, real* b, int n)
{
    real sum = 0;
    for (int i=0; i<n; i++) {
        register real d = (*a++) - (*b++);
        sum += d*d;
    }
    return sum;
}

/// Return \f$|\sum_i^n (a_i-b_i)^2|^{1/2}\f$
real EuclideanNorm (real* a, real* b, int n)
{
    real sum = 0;
    for (int i=0; i<n; i++) {
        register real d = (*a++) - (*b++);
        sum += d*d;
    }
    return sqrt(sum);
}

/// Return \f$|\sum_i^n (a_i-b_i)^p|^{1/p}\f$
real LNorm (real* a, real* b, int n, real p)
{
    real sum = 0;
    for (int i=0; i<n; i++) {
        register real d = (*a++) - (*b++);
        sum += pow(d,p);
    }
    return pow(sum,1.0/p);
}

/// Return \f$\sum_i^n a_i\f$
real Sum (real* a, int n)
{
    real sum = 0;
    for (register int i=0; i<n; i++) {
        sum += *a++;
    }
    return sum;
}
