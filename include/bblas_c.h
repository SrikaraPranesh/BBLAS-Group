/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/bblas_z.h, normal z -> c, Sat Oct 27 15:01:38 2018
 **/

#ifndef BBLAS_C_H
#define BBLAS_C_H

#include "core_c.h"

void blas_cgemm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *transa, const bblas_enum_t *transb,
                      const int *m, const int *n, const int *k,
                      const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                      bblas_complex32_t const* const *B, const int *ldb,
                      const bblas_complex32_t *beta,  bblas_complex32_t            ** C, const int *ldc,
                      int *info);

void blas_chemm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                       bblas_complex32_t const* const *B, const int *ldb,
                       const bblas_complex32_t *beta,  bblas_complex32_t            ** C, const int *ldc,
                       int *info);

void blas_cher2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k, 
                        const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                        bblas_complex32_t const* const *B, const int *ldb,
                        const float  *beta,            bblas_complex32_t            ** C, const int *ldc,
                        int *info);

void blas_cherk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k, 
                       const float *alpha, bblas_complex32_t const *const *A, const int *lda,
                       const float  *beta, bblas_complex32_t            ** C, const int *ldc,
                       int *info);

void blas_csymm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const int *m, const int *n, 
                       const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                       bblas_complex32_t const* const *B, const int *ldb,
                       const bblas_complex32_t *beta,  bblas_complex32_t            ** C, const int *ldc,
                       int *info);

void blas_csyr2k_batch( int group_count, const int *group_sizes,
                        bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                        const int *n, const int *k,
                        const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                        bblas_complex32_t const* const *B, const int *ldb,
                        const bblas_complex32_t  *beta, bblas_complex32_t            ** C, const int *ldc,
                        int *info);

void blas_csyrk_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *uplo, const bblas_enum_t *trans,
                       const int *n, const int *k,
		      const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda, 
		      const bblas_complex32_t  *beta, bblas_complex32_t		   ** C, const int *ldc, 
                       int *info);

void blas_ctrmm_batch( int group_count, const int *group_sizes,
                       bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                       const bblas_enum_t *transa, const bblas_enum_t *diag,
                       const int *m, const int *n,
                       const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                                   bblas_complex32_t **B, int const *ldb,
                       int *info);

void blas_ctrsm_batch(int group_count, const int *group_sizes,
                      bblas_enum_t layout, const bblas_enum_t *side, const bblas_enum_t *uplo,
                      const bblas_enum_t *transa, const bblas_enum_t *diag,
                      const int *m, const int *n,
                      const bblas_complex32_t *alpha, bblas_complex32_t const *const *A, const int *lda,
                                                      bblas_complex32_t             **B, const int *ldb,
                      int *info);
#endif /* BBLAS_C_H */
