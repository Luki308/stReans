#' @export
kmeans_batch <- function(X, k, max_iter = 100L, tol = 1e-6){
  .Call(C_kmeans_batch, X, as.integer(k), as.integer(max_iter), as.double(tol))
}