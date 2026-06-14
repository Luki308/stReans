#ifndef KMEANS_STREAM_H
#define KMEANS_STREAM_H
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

typedef struct{
    double* centres;// k * d array of centroids
    int* counts;    // for each centroid keep counter 
    int ncols;      // number of features
    int k;          // number of clusters
    int n_seen;     // total points seen so far (needed by warmup)
    double halflife;// -1.0 = count-based, >0 = fixed learnign rate 

} KMeansStreamModel;

SEXP C_kmeans_stream_new(SEXP k_r, SEXP d_r, SEXP halflife);
SEXP C_kmeans_stream_update(SEXP ptr_r, SEXP x_r);
SEXP C_kmeans_stream_predict(SEXP ptr_r, SEXP x_r);
SEXP C_kmeans_stream_centers(SEXP ptr);

#endif