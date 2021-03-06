/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from core/zsyr2k_batchf.c, normal z -> s, Sat Oct 27 15:01:39 2018
 *
 **/

#include "bblas.h"

/***************************************************************************//**
 *
 * @ingroup syr2k_batchf 
 *
 *  Performs one of the batch symmetric rank 2k operations
 *
 *    \f[ C[i] = \alpha A[i] \times B[i]^T + \alpha B[i] \times A[i]^T + \beta C[i], \f]
 *    or
 *    \f[ C[i] = \alpha A[i]^T \times B[i] + \alpha B[i]^T \times A[i] + \beta C[i], \f]
 *
 *  where alpha and beta are scalars,
 *  C[i]-s are n-by-n symmetric matrix, and A[i]-s and B[i]-s are n-by-k matrices
 *  in the first case and k-by-n matrices in the second case.
 *
 *******************************************************************************
 *
 * @param[in] group_size
 * 	    The number of matrices to operate on
 *
 * @param[in] layout
 * 	    Specifies if the matrix is stored in row major or column major
 * 	    format:
 * 	    - BblasRowMajor: Row major format
 * 	    - BblasColMajor: Column major format
 *
 * @param[in] uplo
 *          - BblasUpper: Upper triangle of C[i]-s are stored;
 *          - BblasLower: Lower triangle of C[i]-s are stored.
 *
 * @param[in] trans
 *          - BblasNoTrans:
 *            \f[ C[i] = \alpha A[i] \times B[i]^T + \alpha B[i] \times A[i]^T + \beta C[i]; \f]
 *          - BblasTrans:
 *            \f[ C[i] = \alpha A[i]^T \times B[i] + \alpha B[i]^T \times A[i] + \beta C[i]. \f]
 *
 * @param[in] n
 *          The order of the matrices C[i]. n >= zero.
 *
 * @param[in] k
 *          If trans = BblasNoTrans, number of columns of the A[i] and B[i] matrices;
 *          if trans = BblasTrans, number of rows of the A[i] and B[i] matrices.
 *
 * @param[in] alpha
 *          The scalar alpha.
 *
 * @param[in] A
 * 	    A is an array of pointers to matrices A[0], A[1] .. A[group_size-1], 
 * 	    where each element A[i] is a pointer to a matrix A[i] of size 
 *          lda-by-ka.
 *    	    If trans = BblasNoTrans,   ka = k;
 *          if trans = BblasTrans, ka = n.
 *
 * @param[in] lda
 *          The leading dimension of the arrays A[i].
 *          If trans = BblasNoTrans, lda >= max(1, n);
 *          if trans = BblasTrans,   lda >= max(1, k).
 *
 * @param[in] B
 * 		B is an array of pointers to matrices B[0], B[1] .. B[group_size-1], 
 * 		where each element B[i] is a pointer to a matrix B[i] of size 
 *          	ldb-by-kb.
 *          	If trans = BblasNoTrans,   kb = k;
 *          	if trans = BblasTrans, kb = n.
 *
 * @param[in] ldb
 *          The leading dimension of the arrays B[i].
 *          If trans = BblasNoTrans, ldb >= max(1, n);
 *          if trans = BblasTrans,   ldb >= max(1, k).
 *
 * @param[in] beta
 *          The scalar beta.
 *
 * @param[in,out] C
 * 		C is an array of pointers to matrices C[0], C[1] .. C[group_size-1], 
 * 		where each element C[i] is a pointer to a matrix C[i] of size 
 *          	ldc-by-n.
 *          	On exit, the uplo part of the matrix is overwritten
 *          	by the uplo part of the updated matrix.
 *
 * @param[in] ldc
 *          The leading dimension of the arrays C[i]. ldc >= max(1, n).
 *
 * @param[in,out] info
 * 		Array of int for error handling. On entry info[0] should have one of the 
 * 		following values
 *			- BblasErrorsReportAll    :  All errors will be specified on output.
 *						     Length of the array should be atleast
 *						     \sum_{i=0}^{group_count-1}group_sizes[i]+1.
 *			- BblasErrorsReportGroup  :  Single error from each group will be 
 *						     reported. Length of the array should 
 *						     be atleast group_count+1.
 *			- BblasErrorsReportAny    :  Occurence of an error will be indicated
 *						     by a single integer value, and length 
 *						     of the array should be atleast 1.
 *			- BblasErrorsReportNone   :  No error will be reported on output, and
 *						     length of the array should be atleast 1.
 ******************************************************************************
 *
 * @retval  BblasSuccess successful exit
 *
 *******************************************************************************
 *
 * @sa ssyr2k_batchf
 * @sa csyr2k_batchf
 * @sa dsyr2k_batchf
 * @sa ssyr2k_batchf
 *
 ******************************************************************************/
void blas_ssyr2k_batchf(int group_size, bblas_enum_t layout, bblas_enum_t uplo,
                        bblas_enum_t trans, int n, int k, 
                        float alpha, float const *const *A, int lda,
                                                 float const* const *B, int ldb,
                        float  beta, float            ** C, int ldc,
                        int *info)
{
	// Check input arguments 
	if ((layout != BblasRowMajor) &&
        (layout != BblasColMajor)) {
		bblas_error("Illegal value of layout");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 1);
		}
		return;
	}
	if ((uplo != BblasUpper) && (uplo != BblasLower)) {
		bblas_error("Illegal value of uplo");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 2);
		}
		return;
	}
	if ((trans != BblasNoTrans) &&
        (trans != BblasTrans) && (trans != BblasConjTrans)) {
		bblas_error("Illegal value of trans");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 3);
		}
		return;
	}
	if (n < 0) {
		bblas_error("Illegal value of n");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 4);
		}
		return;
	}
	if (k < 0) {
		bblas_error("Illegal value of k");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 5);
		}
		return;
	}
    int am, bm;
    if (trans == BblasNoTrans) {
        am = n;
        bm = n;
    }
    else {
        am = k;
        bm = k;
    }
    if (lda < imax(1, am)) {
		bblas_error("Illegal value of lda");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 6);
		}
		return;
	}
	if (ldb < imax(1, bm)) {
		bblas_error("Illegal value of ldb");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 7);
		}
		return;
	}
	if (ldc < imax(1, n)) {
		bblas_error("Illegal value of ldc");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 8);
		}
		return;
	}
	for (int iter = 0; iter < group_size; iter++) {
		cblas_ssyr2k(layout, uplo, trans,
				n, k,
				(alpha), A[iter], lda,
						    B[iter], ldb,
				 (beta), C[iter], ldc);
		// BblasSuccess
		if (info[0] == BblasErrorsReportAll)
			info[iter] = 0;
	}
	// BblasSuccess
	if (info[0] != BblasErrorsReportAll)
		info[0] = 0;
}

