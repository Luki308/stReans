#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "kmeans_stream.h"

void find_closest_centroid(){
;
}

void update_centroid(){
;
}

void kmeans_stream_finalizer(SEXP ptr){
    Rprintf("kmeans stream finalizer called to free the C pointer memory\n");
    KMeansStreamModel* model = R_ExternalPtrAddr(ptr);
    if(model == NULL) return;
    free(model->centres);
    free(model->counts);
    free(model);
    R_ClearExternalPtr(ptr);
}

SEXP C_kmeans_stream_new(SEXP k_r, SEXP d_r){
if (!Rf_isInteger(k_r))
        Rf_error("k must be an integer");
    if (!Rf_isInteger(d_r))
        Rf_error("d must be an integer");

    int k = INTEGER(k_r)[0];
    int d = INTEGER(d_r)[0];

    if (k <= 0) Rf_error("k must be positive");
    if (d <= 0) Rf_error("d must be positive");

    KMeansStreamModel *model = malloc(sizeof(KMeansStreamModel));
    if(model == NULL)
        Rf_error("Failed to allocate the model");
    
    model->centres = malloc(k * d * sizeof(double));
    model->counts = malloc(k * sizeof(int));

        if (model->centres == NULL || model->counts == NULL) {
        free(model->centres);
        free(model->counts);
        free(model);
        Rf_error("failed to allocate model arrays");
    }
    model->k = k;
    model->ncols = d;

    // initialise counts & centres to 0
    for(int c=0; c<k; c++){
        model->counts[c] = 0;
        for(int j=0; j<d; j++)
            model->centres[c*d +j] = 0.0;
    }
    model->n_seen = 0;
    
    SEXP ptr = PROTECT(R_MakeExternalPtr(model, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ptr, kmeans_stream_finalizer, TRUE);
    UNPROTECT(1);
    return ptr;
}
// SEXP C_kmeans_stream_update(SEXP ptr, SEXP x){
//     return;
// }
// SEXP C_kmeans_stream_predict(SEXP ptr, SEXP x){
//     return;
// }
