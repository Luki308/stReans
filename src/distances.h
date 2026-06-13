#ifndef DISTANCES_H
#define DISTANCES_H

double euclidean_distance(double* a, double* b, size_t n);
void col_to_row_major(const double *src, double *dst, int nrows, int ncols);
void row_to_col_major(const double *src, double *dst, int nrows, int ncols);

SEXP C_euclidean_distance(SEXP a_r, SEXP b_r);
#endif