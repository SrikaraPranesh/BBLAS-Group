/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/bblas_z.h, normal z -> d, Sat Oct 27 15:01:38 2018
 **/

#ifndef BBLAS_D_H
#define BBLAS_D_H

#include "core_d.h"

void blas_dgemm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *transa, const bblas_enum_t *transb,
                      const int *m, const int *n, const int *k,
                      const double *alpha, double const *const *A, const int *lda,
                                                      double const* const *B, const int *ldb,
                      const double *beta,  double            ** C, const int *ldc,
                      int *info);

void blas_dsymm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const double *alpha, double const *const *A, const int *lda,
                                                       double const* const *B, const int *ldb,
                       const double *beta,  double            ** C, const int *ldc,
                       int *info);

void blas_dsyr2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k, 
                        const double *alpha, double const *const *A, const int *lda,
                                                        double const* const *B, const int *ldb,
                        const double  *beta,            double            ** C, const int *ldc,
                        int *info);

void blas_dsyrk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k, 
                       const double *alpha, double const *const *A, const int *lda,
                       const double  *beta, double            ** C, const int *ldc,
                       int *info);

void blas_dsymm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const double *alpha, double const *const *A, const int *lda,
                                                       double const* const *B, const int *ldb,
                       const double *beta,  double            ** C, const int *ldc,
                       int *info);

void blas_dsyr2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k,
                        const double *alpha, double const *const *A, const int *lda,
                                                        double const* const *B, const int *ldb,
                        const double  *beta, double            ** C, const int *ldc,
                        int *info);

void blas_dsyrk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k,
		      const double *alpha, double const *const *A, const int *lda, 
		      const double  *beta, double		   ** C, const int *ldc, 
                       int *info);

void blas_dtrmm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const bblas_enum_t *transa, const bblas_enum_t *diag,
                       const int *m, const int *n,
                       const double *alpha, double const *const *A, const int *lda,
                                                                   double **B, int const *ldb,
                       int *info);

void blas_dtrsm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                      const bblas_enum_t *transa, const bblas_enum_t *diag,
                      const int *m, const int *n,
                      const double *alpha, double const *const *A, const int *lda,
                                                      double             **B, const int *ldb,
                      int *info);
#endif /* BBLAS_D_H */
