/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from include/core_z.h, normal z -> s, Sat Oct 27 15:01:38 2018
 *
 **/
#ifndef ICL_CORE_S_H
#define ICL_CORE_S_H

#include "bblas_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define REAL
/******************************************************************************/
void blas_sgemm_batchf (int group_size, 
                        bblas_enum_t layout, bblas_enum_t transa, bblas_enum_t transb,
                        int m,  int n, int k,
                        float alpha, float const *const *A, int lda,
                                                 float const* const *B, int ldb,
                        float beta,  float            ** C, int ldc,
                        int *info);

void blas_ssymm_batchf(int group_size,
                       bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                       int m, int n,
                       float alpha, float const *const *A, int lda,
                                                float const* const *B, int ldb,
                       float beta,  float            ** C, int ldc,
                       int *info);

void blas_ssymm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        int m,  int n,
                        float alpha, float const *const *A, int lda,
                                                 float const* const *B, int ldb,
                        float beta,  float            ** C, int ldc,
                        int *info);

void blas_ssyr2k_batchf( int group_size,
                         bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                         int n, int k, 
                         float alpha, float const *const *A, int lda,
                                                  float const* const *B, int ldb,
                         float  beta, float            ** C, int ldc,
                         int *info);

void blas_ssyrk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
			int n, int k,
			const float alpha, float const *const *A, int lda,
			const float beta,  float            ** C, int ldc,
			int *info);

void blas_ssyr2k_batchf(int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k, 
                        float alpha, float const *const *A, int lda,
                                                 float const* const *B, int ldb,
                        const float  beta,      float            ** C, int ldc,
                        int *info);

void blas_ssyrk_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t uplo, bblas_enum_t trans,
                        int n, int k,
                        const float alpha, float const *const *A, int lda,
                        const float  beta, float            ** C, int ldc,
                        int *info);

void blas_strmm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        float alpha, float const *const *A, int lda,
                                                             float **B, int ldb,
                        int *info);
    
void blas_strsm_batchf( int group_size,
                        bblas_enum_t layout, bblas_enum_t side, bblas_enum_t uplo,
                        bblas_enum_t transa, bblas_enum_t diag,
                        int m, int n,
                        float alpha, float const *const *A, int lda,
                                                             float **B, int ldb,
                        int *info);

#undef REAL
#ifdef __cplusplus
}  // extern "C"
#endif    
#endif // CORE_S_H 
