#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <math.h>
#include <float.h>
#include "distances.h"
#include <stdlib.h>
#include <stddef.h>

SEXP k_means_batch(SEXP X_r, SEXP k_r, SEXP max_iter_r, SEXP tol_r){
    if(!Rf_isReal(X_r) || !Rf_isMatrix(k_r))
        Rf_error("X should be a numeric matrix!");
    if(!Rf_isInteger(k_r))
        Rf_error("k must be an integer!");
    
    const double* X = REAL(X_r);
    int nrows = Rf_nrows(X_r);
    int ncols = Rf_ncols(X_r);
    int k = INTEGER(k_r)[0];
    int max_iter = INTEGER(max_iter_r)[0];
    double tol = REAL(tol_r)[0];

    if(k <= 0 || k > nrows)
        Rf_error("k must be between 1 and nrow(X)");

    //initialisation (as first k rows)
    double* centers = (double*) malloc(sizeof(double)*k*ncols);
    for(size_t c = 0; c < k; c++)
        for(size_t j = 0; j < ncols; j++)
            centers[c + nrows*j] = X[c + nrows*j];
    
    //loop

    return NULL;
}