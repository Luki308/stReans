# Internal C functions that are used in kmeans algorithm.
# Ported to R so that they can be unit-tested.
# Their description is in src/utils.c

#' @noRd
.euclidean_distance <- function(a, b) {
  .Call(C_euclidean_distance, as.double(a), as.double(b))
}

#' @noRd
.col_to_row_major <- function(X) {
  .Call(C_col_to_row_major,
        as.double(X),
        nrow(X),
        ncol(X))
}

#' @noRd
.row_to_col_major <- function(X_flat, nrows, ncols) {
  .Call(C_row_to_col_major,
        as.double(X_flat),
        as.integer(nrows),
        as.integer(ncols))
}