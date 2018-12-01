/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/bblas_z.h, normal z -> s, Sat Oct 27 15:01:38 2018
 **/

#ifndef BBLAS_S_H
#define BBLAS_S_H

#include "core_s.h"

void blas_sgemm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *transa, const bblas_enum_t *transb,
                      const int *m, const int *n, const int *k,
                      const float *alpha, float const *const *A, const int *lda,
                                                      float const* const *B, const int *ldb,
                      const float *beta,  float            ** C, const int *ldc,
                      int *info);

void blas_ssymm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const float *alpha, float const *const *A, const int *lda,
                                                       float const* const *B, const int *ldb,
                       const float *beta,  float            ** C, const int *ldc,
                       int *info);

void blas_ssyr2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k, 
                        const float *alpha, float const *const *A, const int *lda,
                                                        float const* const *B, const int *ldb,
                        const float  *beta,            float            ** C, const int *ldc,
                        int *info);

void blas_ssyrk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k, 
                       const float *alpha, float const *const *A, const int *lda,
                       const float  *beta, float            ** C, const int *ldc,
                       int *info);

void blas_ssymm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const float *alpha, float const *const *A, const int *lda,
                                                       float const* const *B, const int *ldb,
                       const float *beta,  float            ** C, const int *ldc,
                       int *info);

void blas_ssyr2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k,
                        const float *alpha, float const *const *A, const int *lda,
                                                        float const* const *B, const int *ldb,
                        const float  *beta, float            ** C, const int *ldc,
                        int *info);

void blas_ssyrk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k,
		      const float *alpha, float const *const *A, const int *lda, 
		      const float  *beta, float		   ** C, const int *ldc, 
                       int *info);

void blas_strmm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const bblas_enum_t *transa, const bblas_enum_t *diag,
                       const int *m, const int *n,
                       const float *alpha, float const *const *A, const int *lda,
                                                                   float **B, int const *ldb,
                       int *info);

void blas_strsm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                      const bblas_enum_t *transa, const bblas_enum_t *diag,
                      const int *m, const int *n,
                      const float *alpha, float const *const *A, const int *lda,
                                                      float             **B, const int *ldb,
                      int *info);
#endif /* BBLAS_S_H */
