#' Batch K-Means Clustering
#' 
#' Clusters a numeric matix into k groups.
#' 
#' @param X a numeric matrix where each row is an observation
#' @param k an integer, number of clusters
#' @param max_iter an integer, maximum number of iterations (default = 100)
#' @param tol a numeric, convergance tolerance on centroids shift (default = 1e-6)
#' 
#' @return a list with two components:
#' - 'centers': a matrix of clustering centroids (dim: k x ncol(X))
#' - 'assignments': an integer vector of clustering labels (1-indexed)
#'  
#' @examples
#' X <- matrix(rnorm(100), nrow=50, ncol=2)
#' result <- kmeans_batch(X, k=2L)
#' result$centers
#' result$assignments
#' 
#' @export
kmeans_batch <- function(X, k, max_iter = 100L, tol = 1e-6){
  .Call(C_kmeans_batch, X, as.integer(k), as.integer(max_iter), as.double(tol))
}