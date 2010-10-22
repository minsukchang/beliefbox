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

#ifndef KNN_CLASSIFIER_H
#define KNN_CLASSIFIER_H

#include "Vector.h"
#include "KDTree.h"
#include <list>
#include <vector>
#include "Classifier.h"


class KNNClassifier : public  Classifier<Vector, int, Vector>
{
public:
    class DataSample
    {
    public:
        Vector x; ///< point
        int label; ///< label
        DataSample(const Vector& x_, const int label_)
            : x(x_), label(label_)        
        {
        }
    };
protected:
    int n_classes;
    int n_dim;
    int K;
    KDTree<DataSample> kd_tree;
    std::list<DataSample> samples;
    void AddSample(const DataSample sample);
public:	
    Vector output;
    KNNClassifier(const int n_dim_, const int n_classes_, const int K_);
    virtual ~KNNClassifier();
    virtual int Classify(const Vector& x)
    {
        return ArgMax(Output(x));
    }
    virtual Vector& Output(const Vector& x);
    virtual real Observe(const Vector& x, const int& label)
    {
        AddSample(DataSample(x, label));
		return Output(x)(label);
    }
	void Show()
	{
		kd_tree.Show();
	}
};




#endif