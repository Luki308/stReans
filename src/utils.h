#ifndef UTILS_H
#define UTILS_H

double euclidean_distance(const double* a, const double*, size_t n);
void col_to_row_major(const double *src, double *dst, int nrows, int ncols);
void row_to_col_major(const double *src, double *dst, int nrows, int ncols);

SEXP C_euclidean_distance(SEXP a_r, SEXP b_r);
SEXP C_col_to_row_major(SEXP X_r, SEXP nrows_r, SEXP ncols_r);
SEXP C_row_to_col_major(SEXP X_r, SEXP nrows_r, SEXP ncols_r);
#endif