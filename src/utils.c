#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <math.h>
#include <stddef.h>
#include "utils.h"

/* Computes euclidean distance between two vectors of the same size */
double euclidean_distance(const double* a, const double* b, size_t n){
    double sum = 0.0;
    for(size_t i=0; i<n; i++){
        sum += pow(a[i]-b[i],2);
    }
    sum = sqrt(sum);
    return sum;
}

/* Changes COLUMN major order to ROW major in flat vector representation of a matrix */
void col_to_row_major(const double *src, double *dst, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            dst[i * ncols + j] = src[i + j * nrows];
}

/* Changes ROW major order to COLUMN major in flat vector representation of a matrix */
void row_to_col_major(const double *src, double *dst, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            dst[i + j * nrows] = src[i * ncols + j];
}

/* R-callable wrapper for euclidean_distance */
SEXP C_euclidean_distance(SEXP a_r, SEXP b_r) {
    if (!Rf_isReal(a_r) || !Rf_isReal(b_r))
        Rf_error("a and b must be numeric vectors");
    if (XLENGTH(a_r) != XLENGTH(b_r))
        Rf_error("a and b must have the same length");

    int n = (int) XLENGTH(a_r);
    double result = euclidean_distance(REAL(a_r), REAL(b_r), n);
    return Rf_ScalarReal(result);
}

/* R-callable wrapper for col_to_row_major
 * returns a flat double vector of the reordered elements */
SEXP C_col_to_row_major(SEXP X_r, SEXP nrows_r, SEXP ncols_r) {
    if (!Rf_isReal(X_r))
        Rf_error("X must be a numeric vector");

    int nrows = INTEGER(nrows_r)[0];
    int ncols = INTEGER(ncols_r)[0];
    SEXP result = PROTECT(Rf_allocVector(REALSXP, nrows * ncols));
    col_to_row_major(REAL(X_r), REAL(result), nrows, ncols);
    UNPROTECT(1);
    return result;
}

/* R-callable wrapper for row_to_col_major */
SEXP C_row_to_col_major(SEXP X_r, SEXP nrows_r, SEXP ncols_r) {
    if (!Rf_isReal(X_r))
        Rf_error("X must be a numeric vector");

    int nrows = INTEGER(nrows_r)[0];
    int ncols = INTEGER(ncols_r)[0];
    SEXP result = PROTECT(Rf_allocVector(REALSXP, nrows * ncols));
    row_to_col_major(REAL(X_r), REAL(result), nrows, ncols);
    UNPROTECT(1);
    return result;
}