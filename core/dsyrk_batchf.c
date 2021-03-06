/**
 *
 * @file
 *
 *  BBLAS is a software package provided by:
 *  University of Tennessee, US,
 *  University of Manchester, UK.
 *
 * @generated from core/zsyrk_batchf.c, normal z -> d, Sat Oct 27 15:01:39 2018
 *
 **/

#include "bblas.h"

/***************************************************************************//**
 *
 * @ingroup syrk_batchf
 *
 *  Performs one of the batch symmetric rank k operations
 *
 *    \f[ C[i] = \alpha A[i] \times A[i]^T + \beta C[i], \f]
 *    or
 *    \f[ C[i] = \alpha A[i]^T \times A[i] + \beta C[i], \f]
 *
 *  where alpha and beta are scalars, C[i]-s are n-by-n symmetric
 *  matrices, and A[i]-s are n-by-k matrices in the first case and a k-by-n
 *  matrices in the second case.
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
 *          - BblasNoTrans: \f[ C[i] = \alpha A[i] \times A[i]^T + \beta C[i]; \f]
 *          - BblasTrans:   \f[ C[i] = \alpha A[i]^T \times A[i] + \beta C[i]. \f]
 *
 * @param[in] n
 *          The order of the matrices C[i]. n >= 0.
 *
 * @param[in] k
 *          If trans = BblasNoTrans, number of columns of matrices A[i];
 *          if trans = BblasTrans, number of rows of matrices A[i].
 *
 * @param[in] alpha
 *          The scalar alpha.
 *
 * @param[in] A
 * 	    A is an array of pointers to matrices A[0], A[1] .. A[group_size-1], 
 * 	    where each element A[i] is a pointer to a matrix A[i] of size 
 *          lda-by-ka.
 *          If trans = BblasNoTrans, ka = k;
 *          if trans = BblasTrans,   ka = n.
 *
 * @param[in] lda
 *          The leading dimension of the arrays A[i].
 *          If trans = BblasNoTrans, lda >= max(1, n);
 *          if trans = BblasTrans,   lda >= max(1, k).
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
 * @retval BblasSuccess successful exit
 *
 *******************************************************************************
 *
 * @sa dsyrk_batchf
 * @sa csyrk_batchf
 * @sa dsyrk_batchf
 * @sa ssyrk_batchf
 *
 ******************************************************************************/
void blas_dsyrk_batchf(int group_size, bblas_enum_t layout, bblas_enum_t uplo,
                       bblas_enum_t trans, int n, int k,
                       const double alpha, double const *const *A, int lda,
                       const double beta,  double            ** C, int ldc,
                       int *info)
{
	/* Check input arguments */
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
    int am;
	if (trans == BblasNoTrans) {
		am = n;
	} 
	else {
		am = k;
	}
	if (lda < imax(1, am)) {
		bblas_error("Illegal value of lda");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 6);
		}
		return;
	}
	if (ldc < imax(1, n)) {
		bblas_error("Illegal value of ldc");
		if (info[0] != BblasErrorsReportNone) {
			bblas_set_info(info[0], &info[0], group_size, 7);
		}
		return;
	}
	for (int iter = 0; iter < group_size; iter++) {
		cblas_dsyrk(layout, uplo, trans,
			    n, k,
			    (alpha), A[iter], lda,
			    (beta),  C[iter], ldc);
		// BblasSuccess
		if (info[0] == BblasErrorsReportAll)
			info[iter] = 0;
	}
	// BblasSuccess
	if (info[0] != BblasErrorsReportAll)
		info[0] = 0;
}
