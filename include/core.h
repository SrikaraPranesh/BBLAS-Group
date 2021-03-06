/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 **/
#ifndef CORE_BBLAS_H
#define CORE_BBLAS_H

#include <stdio.h>

#include "bblas_error.h"

#ifdef __cplusplus
extern "C" {
#endif

static const char *lapack_constants[] = {
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",

    "", "", "", "", "", "", "", "", "", "",
    "",
    "NoTrans",                              ///< 111: BblasNoTrans
    "Trans",                                ///< 112: BblasTrans
    "ConjTrans",                            ///< 113: BblasConjTrans

    "", "", "", "", "", "", "",
    "Upper",                                ///< 121: BblasUpper
    "Lower",                                ///< 122: BblasLower
    "General",                              ///< 123: BblasGeneral

    "", "", "", "", "", "", "",
    "NonUnit",                              ///< 131: BblasNonUnit
    "Unit",                                 ///< 132: BblasUnit

    "", "", "", "", "", "", "", "",
    "Left",                                 ///< 141: BblasLeft
    "Right",                                ///< 142: BblasRight

    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "",
    "One",                                  ///< 171: BblasOneNorm
    "",                                     ///< 172: BblasRealOneNorm
    "Two",                                  ///< 173: BblasTwoNorm
    "Frobenius",                            ///< 174: BblasFrobeniusNorm
    "Infinity",                             ///< 175: BblasInfNorm
    "",                                     ///< 176: BblasRealInfNorm
    "Maximum",                              ///< 177: BblasMaxNorm
    "",                                     ///< 178: BblasRealMaxNorm

    "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "",
    "Forward",                             ///< 391: BblasForward
    "Backward",                            ///< 392: BblasBackward
    "", "", "", "", "", "", "", "",
    "Columnwise",                          ///< 401: BblasColumnwise
    "Rowwise"                              ///< 402: BblasRowwise
};

/***************************************************************************//**
 * @retval LAPACK character constant corresponding to BBLAS constant
 * @ingroup bblas_const
 ******************************************************************************/
static inline char lapack_const(int bblas_const) {
    return lapack_constants[bblas_const][0];
}

#if defined(HAVE_MKL) || defined(BBLAS_WITH_MKL)
    #define MKL_Complex16 double _Complex
    #define MKL_Complex8  float _Complex

    #include <mkl_cblas.h>
    #include <mkl_lapacke.h>

    // MKL LAPACKE doesn't provide LAPACK_GLOBAL macro, so define it here.
    // MKL provides all 3 name manglings (foo, foo_, FOO); pick foo_.
    #ifndef LAPACK_GLOBAL
    #define LAPACK_GLOBAL(lcname,UCNAME)  lcname##_
    #endif
#elif defined(HAVE_ESSL) || defined(PLASMA_WITH_ESSL)
    // GCC + ESSL(BLAS) + LAPACKE/CBLAS from LAPACK
    #include <cblas.h>
    #include <lapacke.h>

    #ifndef LAPACK_GLOBAL
    #define LAPACK_GLOBAL(lcname,UCNAME) lcname##_
    #endif
#else
    #include <cblas.h>
    #include <lapacke.h>

    // Original  cblas.h does: enum CBLAS_ORDER {...};
    // Intel mkl_cblas.h does: typedef enum {...} CBLAS_ORDER;
    // LAPACK    cblas.h does: typedef enum {...} CBLAS_ORDER;
    // OpenBLAS  cblas.h does: typedef enum CBLAS_ORDER {...} CBLAS_ORDER;
    // We use (CBLAS_ORDER), so add these typedefs for original cblas.h
    #ifdef CBLAS_ADD_TYPEDEF
    typedef enum CBLAS_ORDER CBLAS_ORDER;
    typedef enum CBLAS_TRANSPOSE CBLAS_TRANSPOSE;
    typedef enum CBLAS_UPLO CBLAS_UPLO;
    typedef enum CBLAS_DIAG CBLAS_DIAG;
    typedef enum CBLAS_SIDE CBLAS_SIDE;
    #endif
#endif

#ifndef lapack_int
#define lapack_int int
#endif

    
#ifdef __cplusplus
}  // extern "C"
#endif

#include "core_s.h"
#include "core_d.h"
#include "core_c.h"
#include "core_z.h"


#endif // ICL_CORE_BLAS_H
