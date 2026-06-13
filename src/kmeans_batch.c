#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <math.h>
#include <float.h>
#include "utils.h"
#include <stdlib.h>
#include <stddef.h>

SEXP C_kmeans_batch(SEXP X_r, SEXP k_r, SEXP max_iter_r, SEXP tol_r){
    if(!Rf_isReal(X_r) || !Rf_isMatrix(X_r))
        Rf_error("X should be a numeric matrix!");
    if(!Rf_isInteger(k_r))
        Rf_error("k must be an integer!");
    
    int nrows = Rf_nrows(X_r);
    int ncols = Rf_ncols(X_r);
    double *X = (double *) R_alloc(nrows * ncols, sizeof(double));
    col_to_row_major(REAL(X_r), X, nrows, ncols); // for easier computation in C
    int k = INTEGER(k_r)[0];
    int max_iter = INTEGER(max_iter_r)[0];
    double tol = REAL(tol_r)[0];

    if(k <= 0 || k > nrows)
        Rf_error("k must be between 1 and nrow(X)");

    //initialisation (as first k rows)
    double* centers = (double*)R_alloc(k*ncols,sizeof(double));
    size_t* counts = (size_t*)R_alloc(k, sizeof(size_t));
    for(size_t c = 0; c < k; c++){
        for(size_t j = 0; j < ncols; j++)
            centers[c*ncols + j] = X[c*ncols + j];
    }
    //loop
    double shift = DBL_MAX;
    double* new_centers = (double*) R_alloc(k*ncols, sizeof(double));
    size_t* assign = (size_t*)R_alloc(nrows, sizeof(size_t));

    int iter = 0;
    while(iter < max_iter && shift > tol){
        //assign to nearest cluster
        for(size_t i=0; i<nrows; i++){
            double min_dist = DBL_MAX;
            size_t best = 0;
            for(size_t c=0; c<k; c++){
                double dist_to_c = euclidean_distance(&X[i*ncols], &centers[c*ncols], ncols);
                if(dist_to_c < min_dist) {
                    min_dist = dist_to_c;
                    best = c;
                }
            }
            assign[i] = best;
        }
    
        //update centers
        for (size_t c = 0; c < k; c++) {
            counts[c] = 0;
            for (size_t j = 0; j < ncols; j++)
                new_centers[c * ncols + j] = 0.0;
        }
            //create sums of coords
        for(size_t i=0; i<nrows; i++){
            size_t c = assign[i];
            counts[c]++;
            for(size_t j=0; j<ncols; j++)
                new_centers[c*ncols+j] += X[i*ncols+j];
        }
            //div by count
        for(size_t c=0; c<k; c++)
            if (counts[c]>0)
                for(size_t j=0; j<ncols; j++)
                    new_centers[c*ncols+j] /= counts[c];
        
        //check shift covergence
        shift = 0.0;
        for(size_t c=0; c<k; c++){
            double d_shift = euclidean_distance(&centers[c*ncols], &new_centers[c*ncols], ncols);
            if(d_shift > shift) shift = d_shift;
        }
        
        //change centers to new ones
        double* temp = centers;
        centers = new_centers;
        new_centers = temp;

        //(TODO - delete)
        // Debug 
        Rprintf("iter %d: shift = %.4f\n", iter+1, shift);
            for (int c = 0; c < k; c++) {
        Rprintf("  center %d: (", c + 1);
        for (int j = 0; j < ncols; j++) {
            Rprintf("%.4f", centers[c * ncols + j]);
            if (j < ncols - 1) Rprintf(", ");
        }
        Rprintf(")\n");
        }
        //increment iter
        iter++;
    }
    
    //results list
    int return_values = 3;
    SEXP result = PROTECT(Rf_allocVector(VECSXP, return_values));
    SEXP names = PROTECT(Rf_allocVector(STRSXP, return_values));
    SEXP r_centers = PROTECT(Rf_allocMatrix(REALSXP, k, ncols));
    SEXP r_assign = PROTECT(Rf_allocVector(INTSXP, nrows));
    SEXP r_iter = PROTECT(Rf_ScalarInteger(iter));

    row_to_col_major(centers, REAL(r_centers), k, ncols); // to match R representation
    for(size_t i=0; i<nrows; i++)
        INTEGER(r_assign)[i] = assign[i] + 1; //R indexes from 1
    
    SET_VECTOR_ELT(result, 0, r_centers);
    SET_VECTOR_ELT(result, 1, r_assign);
    SET_VECTOR_ELT(result, 2, r_iter);

    SET_STRING_ELT(names, 0, Rf_mkChar("centers"));
    SET_STRING_ELT(names, 1, Rf_mkChar("assignments"));
    SET_STRING_ELT(names, 2, Rf_mkChar("iterations"));
    Rf_setAttrib(result, R_NamesSymbol, names);
    UNPROTECT(5);

    return result;
}