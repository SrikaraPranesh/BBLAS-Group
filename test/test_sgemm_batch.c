/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Manchester, UK,
 *  University of Tennessee, US.
 *
 * @generated from test/test_zgemm_batch.c, normal z -> s, Sat Oct 27 15:01:39 2018
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
 * @brief Tests BATCHED SGEMM.
 *
 * @param[in,out] param - array of parameters
 * @param[in]     run - whether to run test
 *
 * Sets used flags in param indicating parameters that are used.
 * If run is true, also runs test and stores output parameters.
 ******************************************************************************/
void test_sgemm_batch(param_value_t param[], bool run)
{
	//================================================================
	// Mark which parameters are used.
	//================================================================
	param[PARAM_NG     ].used = true;
	param[PARAM_GS     ].used = true;
	param[PARAM_INCM   ].used = true;
	param[PARAM_INCG   ].used = true;
	param[PARAM_TRANSA ].used = true;
	param[PARAM_TRANSB ].used = true;
	param[PARAM_INFO   ].used = true;
	param[PARAM_DIM    ].used = PARAM_USE_M | PARAM_USE_N | PARAM_USE_K;
	param[PARAM_ALPHA  ].used = true;
	param[PARAM_BETA   ].used = true;
	if (! run)
		return;


	//================================================================
	// Set parameters.
	//================================================================

	int group_count       = param[PARAM_NG].i;
	int inc_group         = param[PARAM_INCG].i;
	int first_group_size  = param[PARAM_GS].i;
	int group_sizes[group_count];
	for (int i=0; i < group_count; i++) {
		group_sizes[i] = first_group_size + i*inc_group;
	}

	bblas_enum_t transa[group_count];
	bblas_enum_t transb[group_count];
	for (int i=0; i < group_count; i++) { // Todo: assign different trans value
		transa[i]  = bblas_trans_const(param[PARAM_TRANSA].c);
		transb[i]  = bblas_trans_const(param[PARAM_TRANSB].c);
	}

	int inc_matrix_size = param[PARAM_INCM].i;
	int *m = (int*)malloc((size_t)group_count*sizeof(int));
	int *n = (int*)malloc((size_t)group_count*sizeof(int));
	int *k = (int*)malloc((size_t)group_count*sizeof(int));

	for (int i=0; i < group_count; i++) { // Todo: provide different inc par dimension
		m[i] = param[PARAM_DIM].dim.m + i*inc_matrix_size;
		n[i] = param[PARAM_DIM].dim.n + i*inc_matrix_size;
		k[i] = param[PARAM_DIM].dim.k + i*inc_matrix_size;
	}

	int *lda = (int*)malloc((size_t)group_count*sizeof(int));
	int *ldb = (int*)malloc((size_t)group_count*sizeof(int));
	int *ldc = (int*)malloc((size_t)group_count*sizeof(int));

	int *An = (int*)malloc((size_t)group_count*sizeof(int));
	int *Bn = (int*)malloc((size_t)group_count*sizeof(int));
	int *Cn = (int*)malloc((size_t)group_count*sizeof(int));

	int *Am = (int*)malloc((size_t)group_count*sizeof(int));
	int *Bm = (int*)malloc((size_t)group_count*sizeof(int));
	int *Cm = (int*)malloc((size_t)group_count*sizeof(int));

	for (int i= 0; i < group_count; i++) {

		if (transa[i] == BblasNoTrans) {
			Am[i] = m[i];
			An[i] = k[i];
		}
		else {
			Am[i] = k[i];
			An[i] = m[i];
		}
		if (transb[i] == BblasNoTrans) {
			Bm[i] = k[i];
			Bn[i] = n[i];
		}
		else {
			Bm[i] = n[i];
			Bn[i] = k[i];
		}
		Cm[i] = m[i];
		Cn[i] = n[i];

		lda[i] = imax(1, Am[i]);
		ldb[i] = imax(1, Bm[i]);
		ldc[i] = imax(1, Cm[i]);
	}
	int test = param[PARAM_TEST].c == 'y';
	float eps = LAPACKE_slamch('E');


#ifdef COMPLEX
	float alpha[group_count];
	float beta[group_count];
	for (int i = 0; i < group_count; i++) {
		alpha[i] =  param[PARAM_ALPHA].z;
		beta[i]  =  param[PARAM_BETA].z;
	}
#else
	float alpha[group_count];
	float beta[group_count];
	for (int i = 0; i < group_count; i++) {
		alpha[i] = creal(param[PARAM_ALPHA].z);
		beta[i]  = creal(param[PARAM_BETA].z);
	}
#endif

	//================================================================
	// Allocate and initialize arrays.
	//================================================================

	int batch_count =0;
	for (int i = 0; i < group_count; i++) {
		batch_count += group_sizes[i];
	}

	float **A = (float**)malloc(
			(size_t)batch_count*sizeof(float*));
	assert(A != NULL);

	float **B = (float**)malloc(
			(size_t)batch_count*sizeof(float*));
	assert(B != NULL);

	float **C = (float**)malloc(
			(size_t)batch_count*sizeof(float*));
	assert(C != NULL);

	float **Cref =NULL;
	if (test) {
		Cref = (float**)malloc(
				(size_t)batch_count*sizeof(float*));
		assert(Cref != NULL);
	}

	int seed[] = {0, 0, 0, 1};
	lapack_int retval;

	int  group_start=0;
	int  group_end =0;
	for (int group_iter= 0; group_iter < group_count; group_iter++) {
		group_start = group_end;
		group_end += group_sizes[group_iter];
		for (int matrix_iter= group_start; matrix_iter < group_end; matrix_iter++) {

			A[matrix_iter] = (float*)malloc(
					(size_t)lda[group_iter]*An[group_iter]*sizeof(float));
			assert(A[matrix_iter] != NULL);

			B[matrix_iter] = (float*)malloc(
					(size_t)ldb[group_iter]*Bn[group_iter]*sizeof(float));
			assert(B[matrix_iter] != NULL);

			C[matrix_iter] = (float*)malloc(
					(size_t)ldc[group_iter]*Cn[group_iter]*sizeof(float));
			assert(C[matrix_iter] != NULL);

			retval = LAPACKE_slarnv(1, seed, (size_t)lda[group_iter]*An[group_iter], A[matrix_iter]);
			assert(retval == 0);

			retval = LAPACKE_slarnv(1, seed, (size_t)ldb[group_iter]*Bn[group_iter], B[matrix_iter]);
			assert(retval == 0);

			retval = LAPACKE_slarnv(1, seed, (size_t)ldc[group_iter]*Cn[group_iter], C[matrix_iter]);
			assert(retval == 0);

			if (test) {
				Cref[matrix_iter] = (float*)malloc(
						(size_t)ldc[group_iter]*Cn[group_iter]*sizeof(float));
				assert(Cref[matrix_iter] != NULL);

				memcpy(Cref[matrix_iter], C[matrix_iter], (size_t)ldc[group_iter]*Cn[group_iter]*sizeof(float));
			}
		}
	}

	//Set info
	int info_size;
	switch (bblas_info_const(param[PARAM_INFO].c)) {
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
	info[0] = bblas_info_const(param[PARAM_INFO].c);
	//================================================================
	// Run and time BBLAS.
	//================================================================
	bblas_time_t start = gettime();

	blas_sgemm_batch(group_count, (const int *)group_sizes,
			BblasColMajor, (const bblas_enum_t *)transa, (const bblas_enum_t *)transb,
			(const int *)m, (const int *)n, (const int *)k,
			(const float *)alpha, (float const *const *)A, (const int *)lda,
							  (float const *const *)B, (const int *)ldb,
			(const float *)beta,                                    C, (const int *)ldc,
			info);

	bblas_time_t stop = gettime();
	bblas_time_t time = stop-start;

	param[PARAM_TIME].d = time;

	float flops = 0;
	for (int group_iter = 0; group_iter < group_count; group_iter++) {
		flops += flops_sgemm(m[group_iter], n[group_iter],
				k[group_iter])*group_sizes[group_iter];
	}
	param[PARAM_MFLOPS].d = flops / time / 1e6;


	//=====================================================================
	// Test Batched API results by comparing to regular mutiple blas calls .
	//=====================================================================
	if (test) {
		float zmone = -1.0;
		float error = 0.0;
		float work[1];
		group_end = 0;
		for (int group_iter= 0; group_iter < group_count; group_iter++) {
			group_start = group_end;
			group_end += group_sizes[group_iter];
			for (int matrix_iter= group_start; matrix_iter < group_end; matrix_iter++) {

				cblas_sgemm(
						CblasColMajor,
						(CBLAS_TRANSPOSE)transa[group_iter], (CBLAS_TRANSPOSE)transb[group_iter],
						m[group_iter], n[group_iter], k[group_iter],
						(alpha[group_iter]), A[matrix_iter], lda[group_iter],
										B[matrix_iter], ldb[group_iter],
						(beta[group_iter]), Cref[matrix_iter], ldc[group_iter]);

				// compute difference C[matrix_iter] - C[matrix_iter]
				cblas_saxpy((size_t)ldc[group_iter]*Cn[group_iter],
						(zmone), Cref[matrix_iter], 1, C[matrix_iter], 1);

				error += LAPACKE_slange_work(
						LAPACK_COL_MAJOR, 'F', Cm[group_iter], Cn[group_iter],
						C[matrix_iter],  ldc[group_iter], work);
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
		free(C[matrix_iter]);

		if (test)
			free(Cref[matrix_iter]);
	}
	free(A);
	free(B);
	free(C);

	if (test)
		free(Cref);

	free(n);
	free(m);
	free(k);

	free(lda);
	free(ldb);
	free(ldc);

	free(An);
	free(Bn);
	free(Cn);

	free(Am);
	free(Bm);
	free(Cm);
}
