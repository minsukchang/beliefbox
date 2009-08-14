/* -*- Mode: C++; -*- */
// copyright (c) 2009 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KNNMODEL_H
#define KNNMODEL_H


class TrajectorySample
{
    Vector s;
    int a;
    real r;
    Vector s2;
    TrajectorySample(Vector s_, int a_, real r_, Vector s2_)
        : s(s_), a(a_), r(r_), s2(s2_)
    {
    }
        
    
};

class KNNModel
{
protected:
    std::vector<Vector> point_set;
public:	
    struct PointDistance
    {
        Vector& x;
        real d;
    };

    void AddElement(Vector x)
    {
        point_set.push_back(x);
    }

    std::vector<PointDistance> FindKNearestNeigbours(Vector x)
    {
        std::vector<real> d(point_set.size());
        for (uint i=1; i<point_set.size(); ++i) {
            x.distance(L)
        }
    }
};


#endif