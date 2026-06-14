#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include "utils.h"
#include "kmeans_stream.h"

/* forward declarations of your .Call functions — add more as you write them */
SEXP C_kmeans_batch(SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallMethods[] = {
    {"C_kmeans_batch", (DL_FUNC) &C_kmeans_batch, 4},
    {"C_euclidean_distance",(DL_FUNC) &C_euclidean_distance,  2},
    {"C_col_to_row_major",  (DL_FUNC) &C_col_to_row_major,    3},
    {"C_row_to_col_major",  (DL_FUNC) &C_row_to_col_major,    3},
    {"C_kmeans_stream_new", (DL_FUNC) &C_kmeans_stream_new,   3},
    {"C_kmeans_stream_update", (DL_FUNC) &C_kmeans_stream_update,   2},
    {"C_kmeans_stream_centers", (DL_FUNC) &C_kmeans_stream_centers,   1},
    {"C_kmeans_stream_predict", (DL_FUNC) &C_kmeans_stream_predict, 2},
    {NULL, NULL, 0}  /* sentinel — required */
};

void R_init_stReans(void *dll) {
    R_registerRoutines(dll, NULL, CallMethods, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}