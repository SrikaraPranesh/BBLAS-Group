/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/core_z.h, normal z -> c, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef ICL_CORE_C_H
#define ICL_CORE_C_H

#include "bblas_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COMPLEX
/******************************************************************************/
void blas_cgemm_batchf (int group_size, 
                        bblas_enum_t layout, bblas_enum_t transa, bblas_enum_t transb,
                        int m,  int n, int k,
                        bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                 bblas_complex32_t const* const *B, int ldb,
                        bblas_complex32_t beta,  bblas_complex32_t            ** C, int ldc,
                        int *info);

void blas_chemm_batchf(int group_size,
                       bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                       int m, int n,
                       bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                bblas_complex32_t const* const *B, int ldb,
                       bblas_complex32_t beta,  bblas_complex32_t            ** C, int ldc,
                       int *info);

void blas_csymm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        int m,  int n,
                        bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                 bblas_complex32_t const* const *B, int ldb,
                        bblas_complex32_t beta,  bblas_complex32_t            ** C, int ldc,
                        int *info);

void blas_csyr2k_batchf( int group_size,
                         bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                         int n, int k, 
                         bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                  bblas_complex32_t const* const *B, int ldb,
                         bblas_complex32_t  beta, bblas_complex32_t            ** C, int ldc,
                         int *info);

void blas_csyrk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
			int n, int k,
			const bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
			const bblas_complex32_t beta,  bblas_complex32_t            ** C, int ldc,
			int *info);

void blas_cher2k_batchf(int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k, 
                        bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                 bblas_complex32_t const* const *B, int ldb,
                        const float  beta,      bblas_complex32_t            ** C, int ldc,
                        int *info);

void blas_cherk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k,
                        const float alpha, bblas_complex32_t const *const *A, int lda,
                        const float  beta, bblas_complex32_t            ** C, int ldc,
                        int *info);

void blas_ctrmm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                             bblas_complex32_t **B, int ldb,
                        int *info);
    
void blas_ctrsm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        bblas_complex32_t alpha, bblas_complex32_t const *const *A, int lda,
                                                             bblas_complex32_t **B, int ldb,
                        int *info);

#undef COMPLEX
#ifdef __cplusplus
}  // extern "C"
#endif    
#endif // CORE_C_H 
