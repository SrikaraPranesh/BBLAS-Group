/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/core_z.h, normal z -> d, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef ICL_CORE_D_H
#define ICL_CORE_D_H

#include "bblas_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define REAL
/******************************************************************************/
void blas_dgemm_batchf (int group_size, 
                        bblas_enum_t layout, bblas_enum_t transa, bblas_enum_t transb,
                        int m,  int n, int k,
                        double alpha, double const *const *A, int lda,
                                                 double const* const *B, int ldb,
                        double beta,  double            ** C, int ldc,
                        int *info);

void blas_dsymm_batchf(int group_size,
                       bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                       int m, int n,
                       double alpha, double const *const *A, int lda,
                                                double const* const *B, int ldb,
                       double beta,  double            ** C, int ldc,
                       int *info);

void blas_dsymm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        int m,  int n,
                        double alpha, double const *const *A, int lda,
                                                 double const* const *B, int ldb,
                        double beta,  double            ** C, int ldc,
                        int *info);

void blas_dsyr2k_batchf( int group_size,
                         bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                         int n, int k, 
                         double alpha, double const *const *A, int lda,
                                                  double const* const *B, int ldb,
                         double  beta, double            ** C, int ldc,
                         int *info);

void blas_dsyrk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
			int n, int k,
			const double alpha, double const *const *A, int lda,
			const double beta,  double            ** C, int ldc,
			int *info);

void blas_dsyr2k_batchf(int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k, 
                        double alpha, double const *const *A, int lda,
                                                 double const* const *B, int ldb,
                        const double  beta,      double            ** C, int ldc,
                        int *info);

void blas_dsyrk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k,
                        const double alpha, double const *const *A, int lda,
                        const double  beta, double            ** C, int ldc,
                        int *info);

void blas_dtrmm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        double alpha, double const *const *A, int lda,
                                                             double **B, int ldb,
                        int *info);
    
void blas_dtrsm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        double alpha, double const *const *A, int lda,
                                                             double **B, int ldb,
                        int *info);

#undef REAL
#ifdef __cplusplus
}  // extern "C"
#endif    
#endif // CORE_D_H 
