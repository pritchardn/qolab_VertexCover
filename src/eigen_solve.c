/**
 * @author Nicholas Pritchard
 * @date 22/03/2019
 */

#include <stdio.h>
#include "mkl.h"
#include "globals.h"

/**
 * @brief Finds the largest eigenvalue of a sparse double matrix A
 * @param A The matrix in quetion
 * @return Double, the largest eigenvalue found
 * @warning Check for Intel MKL fftw 64bit support, this is the bottleneck forcing 32-bit execution
 */
double max_eigen_find(sparse_matrix_t A) {
    MKL_INT rows;
    MKL_INT cols;
    MKL_INT *rows_start;
    MKL_INT *rows_end;
    MKL_INT *col_indx;
    double result;
    double *values;
    sparse_status_t status;
    sparse_index_base_t index_base;

    status = mkl_sparse_d_export_csr(A, &index_base, &rows, &cols, &rows_start, &rows_end, &col_indx, &values);
    mkl_error_parse(status, stderr);

    // mkl_sparse_d_ev input parameters
    char which = 'L';       /* Which eigenvalues to calculate.  'L' - largest (algebraic) eigenvalues,
 *                                                              'S' - smallest (algebraic) eigenvalues */
    MKL_INT pm[128];        // Used to pass various parameters to Extended Eigensolver Extensions routines.
    MKL_INT k0 = 1;         // Desired number of max/min eigenvalues

    /* mkl_sparse_d_ev output parameters */
    MKL_INT k;              // Number of eigenvalues found (might be less than k0).
    double *E = mkl_calloc((size_t) rows, sizeof(double), DEF_ALIGNMENT);   // Eigenvalues
    double *X = mkl_calloc((size_t) rows, sizeof(double), DEF_ALIGNMENT);   // Eigenvectors
    double *res = mkl_calloc((size_t) rows, sizeof(double), DEF_ALIGNMENT); // Residual
    check_alloc(E);
    check_alloc(X);
    check_alloc(res);

    /* Local variables */
    MKL_INT info;                   // Errors */
    MKL_INT compute_vectors = 0;    // Flag to compute eigenvecors
    MKL_INT tol = 7;                // Tolerance

    /* Sparse BLAS IE variables */
    struct matrix_descr descr;               // Structure specifying sparse matrix properties
    descr.type = SPARSE_MATRIX_TYPE_GENERAL; // Full matrix is stored

    mkl_sparse_ee_init(pm);

    pm[1] = tol; // Set tolerance
    pm[6] = compute_vectors;

    info = mkl_sparse_d_ev(&which, pm, A, descr, k0, &k, E, X, res);
    mkl_error_parse(info, stderr);

    result = E[k0 - 1]; //Collect the largest Eigenvalue

    mkl_free(E);
    mkl_free(X);
    mkl_free(res);

    return result;
}
