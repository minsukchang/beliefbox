/* -*- Mode: c++ -*- */
/* VER: $Id: MathFunctions.h,v 1.2 2006/11/06 15:48:53 cdimitrakakis Exp cdimitrakakis $ */
// copyright (c) 2006 by Christos Dimitrakakis <christos.dimitrakakis@gmail.com>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef MAKE_MAIN
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>


#include "Matrix.h"
#include "MatrixNorm.h"
#include "Distribution.h"
#include "NormalDistribution.h"
#include "EasyClock.h"
#include "Random.h"
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <stdexcept>

void SpeedTest();


int main()
{
    int N = 3;
    int n_errors = 0;
    Matrix I = Matrix::Unity(N,N);
    Matrix W(N,N);
    Matrix x(N,N);
    Vector u(N);
    Matrix D(N,1);
    Vector v(N);
    
    for (int i=0; i<N; ++i) {
        u[i] = i + 1;
        v[i] = i*2;
    }
    
    Matrix Res = OuterProduct(u, v);
    Res.print(stdout);
    printf("outer product\n");

    Matrix three_by_four(N + 1, N + 2);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            W(i,j) = urandom();
            printf ("%f ", W(i,j));
        }
        D(i,0) = urandom();
        printf("\n");
    }
    

    Vector A = W * v;
    //Matrix A = v * W;

    A.print(stdout);

    
    Matrix X(N,N);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            X(i,j) = urandom();
        }
    }

    printf("W:\n");
    W.print(stdout);

    printf("I:\n");
    I.print(stdout);
    
    printf("-----------\n");
    printf("# W==W*I: ");

    if (W!=I*W) {
        n_errors++;
        printf ("FAILED\n");
    } 
    if (W==I*W) {
        printf ("OK\n");
    }

    printf("# (W*W)' == (W*W')': ");
    if (W*Transpose(W) == Transpose(W*Transpose(W))) {
        printf("OK\n");
    } else {
        n_errors++; printf("FAILED\n");
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            X(i,j) = urandom();
        }
    }
	
    printf ("# I = 0 ");
    if (Matrix::Null(N,N)!=I) {
        printf ("OK"); 
    } else {
        n_errors++; printf ("FAILED"); 
    }

    bool caught;
    try {
        caught = false;
        printf("# Invalid matrix multiplication: ");
        three_by_four*I;
    }


    catch (std::domain_error) {
        caught = true;
        printf ("OK - Domain error caught\n");
    }
    
    if (!caught) {
        n_errors++;
        printf ("FAILED - Domain error not caught\n");
    }
    
 
    if (W*2.0 != W+W) {
        n_errors++;
        printf ("# matrix-scalar multiplication FAILED\n");
    } else {
        printf ("# matrix-scalar multiplication OK\n");
    }

    printf("u'*I: ");
    (Transpose(Matrix(u))*I).print(stdout);
    printf ("# vector transposition and multiplication OK\n"); 

    printf("I*u: ");
    ((const Matrix&) I*(const Vector&) u).print(stdout);
    printf ("# OK\n"); 

	printf("W Kronecker I:");
    W.Kron(I).print(stdout);
	printf("#OK\n");
	
    printf("V*z: ");
    Matrix V(2,4);
    Vector z(4);
    for (int i=0; i<V.Rows(); ++i) {
        for (int j=0; j<V.Columns(); ++j) {
            V(i,j) = urandom();
        }
    }
    for (int j=0; j<z.Size(); ++j) {
        z(j)= urandom();
    }
    ((const Matrix&) V*(const Vector&) z).print(stdout);

    try {
        caught = false;
        printf("u*I:\n");
        (u*I).print(stdout);
    }

    catch (std::domain_error) {
        caught = true;
        printf ("# OK: Domain error caught\n");
    }

    if (!caught) {
        n_errors++;
        printf ("# ERR - Domain error not caught\n");
    }

    {
        printf("u*D': ");
        Matrix X = (u*Transpose(D));
        printf ("# vector and matrix transpose OK\n"); 
    }

    try {
        caught = false;
        printf("u*D:\n");
        ((Matrix) (u*D)).print(stdout);
    }
    catch (std::domain_error) {
        caught = true;
        printf ("# OK: Domain error caught\n");
    }
    if (!caught) {
        n_errors++;
        printf ("# ERR - Domain error not caught\n");
    }



    printf("Q = W, W = 2W\n");
    Matrix Q = W;
    W = W*2;
    //W.print(stdout);

    printf ("# 2W - Q\n");
    //(W - Q*2).print(stdout);
    fflush(stdout);
    if (W-Q*2 != Matrix::Null(N,N)) {
        fprintf (stderr, "Difference not NULL\n");
        n_errors++;
    }

    if (n_errors) {
        printf ("%d tests FAILED\n", n_errors);
    } else {
        printf ("All tests OK\n");
    }
    
    printf("Testing Decomposition of matrix:\n");
    W = Q * Transpose(Q);
    W.print(stdout);
    printf("Cholesky:\n");
	W.Cholesky().print(stdout);
    
    printf("LU:\n");
    real det;
	W.print(stdout);
    std::vector<Matrix> LU= W.LUDecomposition(det);
    LU[0].print(stdout);
    LU[1].print(stdout);
	
	printf("QR:\n");
	std::vector<Matrix> QR = W.QRDecomposition();
	printf("\n");
	QR[0].print(stdout);
	printf("\n");
    QR[1].print(stdout);
	printf("\n");
	W.print(stdout);
    
    printf("Testing inverse.\n");
	printf("W\n");
    W.print(stdout);
    printf("LU Inverse of W:\n");
    Matrix inv_LU = W.Inverse_LU();
    Matrix inv_Ch = W.Inverse_Cholesky();
	inv_LU.print(stdout);
    printf("Default Inverse of W:\n");
    Matrix invW = W.Inverse();
    invW.print(stdout);
    

    
    real inv_delta = FrobeniusNorm(inv_LU - invW);
    if (inv_delta > 1e-6) {
        fprintf (stderr, "LU differs from GSL inverse by %f over F-Norm of LU inverse\n",
                 inv_delta);
		fprintf(stderr, "------- ERROR BEGIN -------\n");
		fprintf(stderr, "LU Inverse:\n");
        (inv_LU - invW).print(stderr);
		fprintf(stderr, "Default inverse:\n");
		invW.print(stderr);
		fprintf(stderr, "Difference:\n");
        (inv_LU - invW).print(stderr);
		fprintf(stderr, "-------- ERROR END --------\n");
        n_errors++;
    }

    printf("Inverse of Inverse of W:\n");
    Matrix reinvW = invW.Inverse();
    reinvW.print(stdout);
    Matrix ShouldBeUnity = W * invW;
	real inv_unity = FrobeniusNorm(ShouldBeUnity - Matrix::Unity(N, N));
	if (inv_unity > 1e-6) {
		fprintf(stderr, "------- ERROR BEGIN -------\n");
		fprintf(stderr, "W W^{-1} \\neq 1\n");
		ShouldBeUnity.print(stderr);
		fprintf(stderr, "-------- ERROR END --------\n");
	}

    if (n_errors) {
        printf ("# %d ERRORS found\n", n_errors);
    } else {
        printf ("# All tests OK\n");
    }
    printf ("Performance testing:\n");
    {
        double start_time = GetCPU();
        SpeedTest();
        double end_time = GetCPU();
        printf ("Total time: %f\n", end_time - start_time);
    }
    return n_errors;
}

void SpeedTest()
{
    {
        int N = 768;
        
        Matrix A = Matrix::Unity(N, N);
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                A(i,j) += urandom();
            }
        }
        
        A = Transpose(A) * A;

        {
            int s;
            gsl_matrix * M = gsl_matrix_alloc (N, N);
            gsl_matrix * inverse = gsl_matrix_alloc (N, N);
            gsl_permutation * perm = gsl_permutation_alloc (N);
            
            for (int i=0; i<N; ++i) {
                for (int j=0; j<N; ++j) {
                    gsl_matrix_set(M, i, j, A(i,j));
                }
            }
            double start_time = GetCPU();
            // Make LU decomposition of matrix m
            gsl_linalg_LU_decomp (M, perm, &s);
            double mid_time = GetCPU();
            // Invert the matrix m
            gsl_linalg_LU_invert (M, perm, inverse);
            double end_time = GetCPU();
            printf("GSL: %f %f %f\n",
                   mid_time - start_time,
                   end_time - mid_time,
                   end_time - start_time);
            gsl_matrix_free(M);
            gsl_matrix_free(inverse);
            gsl_permutation_free(perm);
        }

        {
            double start_time = GetCPU();
            real det;
            Matrix tmp(A);
            std::vector<Matrix> Z = tmp.LUDecomposition(det, 1e-6);
            double mid_time = GetCPU();
            Matrix C = A.Inverse(Z[0], Z[1]);
            double end_time = GetCPU();
            printf("Cholesky: %f %f %f\n",
                   mid_time - start_time,
                   end_time - mid_time,
                   end_time - start_time);
        }

        {
            double start_time = GetCPU();
            Matrix U = A.Cholesky(1e-6);
            double mid_time = GetCPU();
            Matrix L(U, false);
            L.Transpose();
            Matrix C = A.Inverse(L, U);
            double end_time = GetCPU();
            printf("LU: %f %f %f\n",
                   mid_time - start_time,
                   end_time - mid_time,
                   end_time - start_time);
        }

        {
            double start_time = GetCPU();
            Matrix C = A.Inverse();
            double end_time = GetCPU();
            printf("Default: %f\n",
                   end_time - start_time);
        }


    }
    for (int iter=0; iter<1; iter++) {

        int K = ceil(urandom() * 100);
        int M = ceil(urandom() * 100);
        int N = ceil(urandom() * 100);
        
        Matrix A(K, M);
        for (int i=0; i<K; ++i) {
            for (int j=0; j<M; ++j) {
                A(i,j) = urandom();
            }
        }
        Matrix B(M, N);
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                B(i,j) = urandom();
            }
        }
        Matrix D(K, N);
        for (int i=0; i<K; ++i) {
            for (int j=0; j<N; ++j) {
                D(i,j) = urandom();
            }
        }

        for (int k=0; k<10; ++k) {
            D += A*B;
        }
        
    }
}




#endif

/*
          AMD 64 3200 | Intel Atom N270
REFERENCE 9.5 (10.5)  | 55 (56)
MULTIPLIC 7.5 (8.3)   | 62 (62)

Multiplication
--------------
Cholesky: 1.760000 6.190000 7.950000
LU: 1.610000 8.520000 10.130000
Total time: 28.140000

Cholesky: 1.760000 6.240000 8.000000
LU: 1.330000 8.830000 10.160000
Total time: 25.840000

*/
