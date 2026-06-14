#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <float.h>

#include "utils.h"
#include "kmeans_stream.h"

void kmeans_stream_finalizer(SEXP ptr){
    Rprintf("kmeans stream finalizer called to free the C pointer memory\n");
    KMeansStreamModel* model = R_ExternalPtrAddr(ptr);
    if(model == NULL) return;
    free(model->centres);
    free(model->counts);
    free(model);
    R_ClearExternalPtr(ptr);
}

SEXP C_kmeans_stream_new(SEXP k_r, SEXP d_r, SEXP halflife_r){
    if (!Rf_isInteger(k_r))
        Rf_error("k must be an integer");
    if (!Rf_isInteger(d_r))
        Rf_error("d must be an integer");
    if (!Rf_isReal(halflife_r))
        Rf_error("halflife must be numeric");
    
    int k = INTEGER(k_r)[0];
    int d = INTEGER(d_r)[0];
    double halflife = REAL(halflife_r)[0];

    if (k <= 0) Rf_error("k must be positive");
    if (d <= 0) Rf_error("d must be positive");
    if (halflife != -1.0 && (halflife <= 0.0 || halflife >= 1.0))
        Rf_error("halflife must be between 0 and 1, or -1 for count-based");

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
    model->halflife = halflife;

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

static KMeansStreamModel* get_model(SEXP ptr){
    KMeansStreamModel* model = (KMeansStreamModel*) R_ExternalPtrAddr(ptr);
    if(model == NULL)
        Rf_error("Model pointer is NULL!");
    return model;
}

static int find_closest_centroid(const KMeansStreamModel* model, const double* x){
    double min_dist = DBL_MAX;
    int best = 0;
    for(int c=0; c<model->k; c++){
        double dist = euclidean_distance(&model->centres[c*model->ncols], x, model->ncols);
        if(dist < min_dist){
            min_dist = dist;
            best = c;
        }
    }
    return best;
}

SEXP C_kmeans_stream_update(SEXP ptr, SEXP x_r){
    KMeansStreamModel* model = get_model(ptr);
    
    if (!Rf_isReal(x_r))
        Rf_error("x must be a numeric vector");
    if ((int) XLENGTH(x_r) != model->ncols)
        Rf_error("x must have length d = %d", model->ncols);
    double* x = REAL(x_r);

    model->n_seen++;
    if(model->n_seen <= model->k){
        int slot = model->n_seen-1;
        for(int j=0; j<model->ncols; j++)
            model->centres[slot*model->ncols + j] = x[j];
        model->counts[slot] = 1;
        return Rf_ScalarInteger(slot + 1); //indexing from 1
    }
    
    // find closest centroid
    int closest_c = find_closest_centroid(model, x);
    model->counts[closest_c]++;

    // update centroid
    double eta = (model->halflife < 0.0) ? 1.0/model->counts[closest_c] : model->halflife;

    for(int j=0; j<model->ncols; j++)
    model->centres[closest_c*model->ncols + j] += eta*(x[j] - model->centres[closest_c*model->ncols + j]);

    // return assignment
    return Rf_ScalarInteger(closest_c + 1); // 1-indexing
}
// SEXP C_kmeans_stream_predict(SEXP ptr, SEXP x){
//     return;
// }
