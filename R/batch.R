#' Batch K-Means Clustering
#' 
#' Clusters a numeric matix into k groups.
#' 
#' @param X a numeric matrix where each row is an observation
#' @param k a positive integer, number of clusters
#' @param max_iter a positive integer, maximum number of iterations (default = 100)
#' @param tol a positive numeric, convergance tolerance on centroids shift (default = 1e-6)
#' 
#' @return a list with two components:
#' - 'centers': a matrix of clustering centroids (dim: k x ncol(X))
#' - 'assignments': an integer vector of clustering labels (1-indexed)
#' - 'iterations': an integer of the number of completed iterations
#'  
#' @examples
#' # simple 2D example with three well-separated clusters
#' set.seed(42)
#' cluster1 <- matrix(rnorm(40, mean = 0,  sd = 0.5), nrow = 20)
#' cluster2 <- matrix(rnorm(40, mean = 5,  sd = 0.5), nrow = 20)
#' cluster3 <- matrix(rnorm(40, mean = 10, sd = 0.5), nrow = 20)
#' X <- rbind(cluster1, cluster2, cluster3)
#' X <- X[sample(nrow(X)),] # for better initial centers
#' result <- kmeans_batch(X, k = 3L, max_iter = 100L, tol = 1e-6)
#' result$centers
#' result$assignments
#' result$iterations
#'
#' # plot the result
#' plot(X[, 1], X[, 2],
#'      col = result$assignments,
#'      pch = 16, cex = 1.5,
#'      xlab = "X1", ylab = "X2",
#'      main = "Batch K-Means")
#' points(result$centers[, 1], result$centers[, 2],
#'        col = 1:3, pch = 4, cex = 3, lwd = 3)
#' 
#' @export
kmeans_batch <- function(X, k, max_iter = 100L, tol = 1e-6){
  if (!is.numeric(k) || length(k) != 1)
    stop("k must be a single integer")
  if (k != as.integer(k))
    stop("k must be an integer (no decimal part)")
  .Call(C_kmeans_batch, X, as.integer(k), as.integer(max_iter), as.double(tol))
}