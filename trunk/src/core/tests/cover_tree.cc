/* -*- Mode: C++; -*- */
// copyright (c) 2010 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef MAKE_MAIN

#include "CoverTree.h"
#include "Random.h"
#include "Vector.h"
#include <vector>

int main(int argc, char** argv)
{
    CoverTree tree;

	if (argc != 4) {
		fprintf(stderr, "Usage: cover_tree points dimensions n_trials\n");
		exit(-1);
	}
    int n_points = atoi(argv[1]);
    int n_dimensions = atoi(argv[2]);
    int n_trials = atoi(argv[3]);
    printf ("Testing with %d points and %d dimensions\n", n_points, n_dimensions);
    std::vector<Vector> X(n_points);

    for (int i=0; i<n_points; i++) {
        X[i].Resize(n_dimensions);
        for (int j=0; j<n_dimensions; j++) {
            X[i][j] = urandom();
        }
    }
    
	printf ("# Inserting points\n");
    for (int i=0; i<n_points; i++) {
        tree.Insert(X[i]);
    }    

	int n_errors = 0;
	for (int i=0; i<n_trials; ++i) {
		printf ("# test :%d\n", i);

		Vector Q(n_dimensions);
		for (int j=0; j<n_dimensions; j++) {
            Q[j] = urandom();
		}
		CoverTree::Node* node = tree.NearestNeighbour(Q);
		if (node) {
			Vector best_point = node->point;
			real dist = INF;
			int arg_min = -1;
			for (int k=0; k<n_points; ++k) {
				real dist_k = tree.metric(X[k], Q);
				if (dist_k < dist) {
					dist = dist_k;
					arg_min = k;
				}
			}

			real error = tree.metric(best_point, X[arg_min]);

			if (error > 0.000001) {
				printf("## Distance is too big: %f ##########\n", error);
				printf("Query: "); Q.print(stdout);
				printf("Found: (%f) ", tree.metric(Q, node->point)); best_point.print(stdout);
				printf("Best: (%f) ", dist); X[arg_min].print(stdout);
				Vector Q_alt = X[arg_min];
				CoverTree::Node* node_alt = tree.NearestNeighbour(Q_alt);
				printf("Alternative result: "); node_alt->point.print(stdout);
				n_errors++;
			}
		} else {
			printf ("NULL\n");
		}
	}
	if (!n_errors) {
		printf("Test OK\n");
	}
    return n_errors;
}

#endif
