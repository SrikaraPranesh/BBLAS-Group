/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Manchester, UK,
 *  University of Tennessee, US.
 *
 * @generated from test/test_ztrsm_batch.c, normal z -> d, Sat Oct 27 15:01:40 2018
 *
 **/
#include "test.h"
#include "flops.h"
#include "bblas.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define REAL

/***************************************************************************//**
 *
 * @brief Tests BATCHED DTRSM.
 *
 * @param[in,out] param - array of parameters
 * @param[in]     run - whether to run test
 *
 * Sets used flags in param indicating parameters that are used.
 * If run is true, also runs test and stores output parameters.
 ******************************************************************************/
void test_dtrsm_batch(param_value_t param[], bool run)
{
	//================================================================
	// Mark which parameters are used.
	//================================================================
	param[PARAM_NG     ].used = true;
	param[PARAM_GS     ].used = true;
	param[PARAM_INCM   ].used = true;
	param[PARAM_INCG   ].used = true;
	param[PARAM_SIDE   ].used = true;
	param[PARAM_UPLO   ].used = true;
	param[PARAM_TRANSA ].used = true;
	param[PARAM_DIAG   ].used = true;
	param[PARAM_INFO   ].used = true;
	param[PARAM_DIM    ].used = PARAM_USE_M | PARAM_USE_N;
	param[PARAM_ALPHA  ].used = true;
	if (! run)
		return;

	//================================================================
	// Set parameters
	//================================================================

	int group_count       = param[PARAM_NG].i;
	int inc_group         = param[PARAM_INCG].i;
	int first_group_size  = param[PARAM_GS].i;
	int group_sizes[group_count];
	for (int i=0; i < group_count; i++) {
		group_sizes[i] = first_group_size + i*inc_group;
	}

	bblas_enum_t transa[group_count];
	bblas_enum_t uplo[group_count];
	bblas_enum_t side[group_count];
	bblas_enum_t diag[group_count]; 
	for (int i=0; i < group_count; i++) { // Todo: assign different trans value
		transa[i] = bblas_trans_const(param[PARAM_TRANS].c);
		uplo[i]  =  bblas_uplo_const(param[PARAM_UPLO].c);
		side[i]  = bblas_side_const(param[PARAM_SIDE].c);
		diag[i]  = bblas_diag_const(param[PARAM_DIAG].c);
		
	}

	int *m = (int*)malloc((size_t)group_count*sizeof(int));
	int *n = (int*)malloc((size_t)group_count*sizeof(int));
	int size_incre = param[PARAM_INCM].i;
	m[0] = param[PARAM_DIM].dim.m;
	n[0] = param[PARAM_DIM].dim.n;
	for (int i = 1; i < group_count; ++i) {
		m[i] = m[i-1] + size_incre;
		n[i] = n[i-1] + size_incre;
	}


	int *lda = (int*)malloc((size_t)group_count*sizeof(int));
	int *ldb = (int*)malloc((size_t)group_count*sizeof(int));
	int *Am  = (int*)malloc((size_t)group_count*sizeof(int));

	for (int i = 0; i < group_count; ++i) {
		if (side[i] == BblasLeft) {
			Am[i]    = m[i];
		}
		else {
			Am[i]    = n[i];
		}

		lda[i] = imax(1, Am[i]);
		ldb[i] = imax(1, m[i]);
	}

	int test = param[PARAM_TEST].c == 'y';
	double eps = LAPACKE_dlamch('E');

#ifdef COMPLEX
	double alpha[group_count];
	for (int i = 0; i < group_count; i++) {
		alpha[i] =  param[PARAM_ALPHA].z;
	}
#else
	double alpha[group_count];
	for (int i = 0; i < group_count; i++) {
		alpha[i] = creal(param[PARAM_ALPHA].z);
	}
#endif

	//================================================================
	// Allocate and initialize arrays.
	//================================================================

	int batch_count =0;
	for (int i = 0; i < group_count; i++) {
		batch_count += group_sizes[i];
	}

	double **A =
		(double**)malloc((size_t)batch_count*sizeof(double*));
	assert(A != NULL);

	double **B =
		(double**)malloc((size_t)batch_count*sizeof(double*));
	assert(B != NULL);

	double **Bref = NULL;
	if (test) {
		Bref = (double**)malloc(
				(size_t)batch_count*sizeof(double*));
		assert(Bref != NULL);
	}


	int seed[] = {0, 0, 0, 1};
	lapack_int retval;
	int  group_start=0;
	int  group_end =0;
	for (int group_iter= 0; group_iter < group_count; group_iter++) {
		group_start = group_end;
		group_end += group_sizes[group_iter];
		for (int matrix_iter= group_start; matrix_iter < group_end; matrix_iter++) {

			A[matrix_iter] = (double*)malloc(
					(size_t)lda[group_iter]*n[group_iter]*sizeof(
						double));
			assert(A[matrix_iter] != NULL);

			B[matrix_iter] = (double*)malloc(
					(size_t)ldb[group_iter]*n[group_iter]*sizeof(
						double));
			assert(B[matrix_iter] != NULL);

			retval = LAPACKE_dlarnv(1, seed, (size_t)lda[group_iter]*n[group_iter], 
					A[matrix_iter]);
			assert(retval == 0);
            for (int i = 0; i <  n[group_iter]; i++ ) {
                A[matrix_iter][i + lda[group_iter]*i] += i;
            }
			retval = LAPACKE_dlarnv(1, seed, (size_t)ldb[group_iter]*n[group_iter], 
					B[matrix_iter]);
			assert(retval == 0);

			if (test) {
				Bref[matrix_iter] = (double*)malloc(
						(size_t)ldb[group_iter]*n[group_iter]*sizeof(
							double));
				assert(Bref[matrix_iter] != NULL);

				memcpy(Bref[matrix_iter], B[matrix_iter], (size_t)ldb[group_iter]*
						n[group_iter]*sizeof(double));
			}
		}
	}

	//Set info
	int info_size;
	switch (bblas_info_const(param[PARAM_TRANSA].c)) {
		case BblasErrorsReportAll :
			info_size = batch_count +1;
			break;
		case BblasErrorsReportGroup :
			info_size = group_count +1;
			break;
		case BblasErrorsReportAny :
		case BblasErrorsReportNone :
			info_size = 1;
			break;
		default :
			bblas_error ("illegal value of info");
			return;
	}

	int *info = (int*) malloc((size_t)info_size*sizeof(int))  ;
	info[0] = bblas_trans_const(param[PARAM_TRANSA].c);

	//================================================================
	// Run and time BBLAS.
	//================================================================
	bblas_time_t start = gettime();

	blas_dtrsm_batch(group_count, (const int *)group_sizes,
			BblasColMajor, (const bblas_enum_t *)side, (const bblas_enum_t *)uplo,
			(const bblas_enum_t *)transa, (const bblas_enum_t *)diag,
			(const int *)m, (const int *)n,
			(const double *)alpha, (double const *const *)A, (const int *)lda,
											                                    B, (int const *)ldb,
			info);

	bblas_time_t stop = gettime();
	bblas_time_t time = stop-start;

	param[PARAM_TIME].d = time;

	double flops = 0;
	for (int group_iter = 0; group_iter < group_count; group_iter++) {
		flops += flops_dtrmm(side[group_iter], m[group_iter], n[group_iter])
			*group_sizes[group_iter];
	}
	param[PARAM_MFLOPS].d = flops / time / 1e6;

	//=====================================================================
	// Test Batched API results by comparing to regular mutiple blas calls .
	//=====================================================================
	if (test) {
		double zmone = -1.0;
		double error = 0.0;
		double work[1];
		group_end = 0;
		for (int group_iter= 0; group_iter < group_count; group_iter++) {
			group_start = group_end;
			group_end += group_sizes[group_iter];
			for (int matrix_iter= group_start; matrix_iter < group_end; matrix_iter++) {

				cblas_dtrsm(CblasColMajor, (CBLAS_SIDE)side[group_iter], (CBLAS_UPLO)uplo[group_iter],
						(CBLAS_TRANSPOSE)transa[group_iter], (CBLAS_DIAG)diag[group_iter],
						m[group_iter], n[group_iter],
                        (alpha[group_iter]), A[matrix_iter], lda[group_iter],
						                             Bref[matrix_iter], ldb[group_iter]);

				cblas_daxpy((size_t)ldb[group_iter]*n[group_iter], (zmone), Bref[matrix_iter], 1, 
						B[matrix_iter], 1);

				error = LAPACKE_dlange_work(
						LAPACK_COL_MAJOR, 'F', m[group_iter], n[group_iter], B[matrix_iter], ldb[group_iter], work);
			}
		}
		param[PARAM_ERROR].d = error;
		param[PARAM_SUCCESS].i = error < 3*eps;
	}

	//================================================================
	// Free arrays.
	//================================================================

	for (int matrix_iter = 0; matrix_iter < batch_count; matrix_iter++) { 

		free(A[matrix_iter]);
		free(B[matrix_iter]);

		if (test)
			free(Bref[matrix_iter]);
	}
	free(A);
	free(B);

	if (test)
		free(Bref);

	free(n);
	free(m);
	free(Am);

	free(lda);
	free(ldb);
}
