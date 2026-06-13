#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <math.h>
#include <stddef.h>
#include "distances.h"

double euclidean_distance(double* a, double* b, size_t n){
    double sum = 0.0;
    for(size_t i=0; i<n; i++){
        sum += pow(a[i]-b[i],2);
    }
    sum = sqrt(sum);
    return sum;
}

void col_to_row_major(const double *src, double *dst, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            dst[i * ncols + j] = src[i + j * nrows];
}

void row_to_col_major(const double *src, double *dst, int nrows, int ncols) {
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            dst[i + j * nrows] = src[i * ncols + j];
}

SEXP C_euclidean_distance(SEXP a_r, SEXP b_r){
    if(!Rf_isReal(a_r) || !Rf_isReal(b_r))
        Rf_error("a and b must be numeric vectors!");
    if(XLENGTH(a_r) != XLENGTH(b_r))
        Rf_error("a and b must have the same length");
    int n = (int) XLENGTH(a_r);;
    double result = euclidean_distance(REAL(a_r), REAL(b_r), n);
    return Rf_ScalarReal(result);
}