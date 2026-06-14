#' Create a New Streaming K-Means Model
#'
#' Initialises a streaming k-means model. The first \code{k} observations passed
#' to \code{kmeans_stream_update()} will be used as initial centroids (warm-up
#' phase). Clustering begins properly after \code{k} observations have been
#' seen.
#'
#' @param k a positive integer, number of clusters
#' @param d a positive integer, number of features (must match observations
#'   passed to update/predict)
#' @param halflife numeric learning rate. Use \code{-1} (default) for
#'   count-based updates or a value in \code{(0, 1)} for fixed-rate updates
#'   (forgetful, recent points weighted more heavily)
#'
#' @return a list with components:
#' \describe{
#'   \item{`ptr`}{external pointer to the C model struct}
#'   \item{`k`}{number of clusters}
#'   \item{`d`}{number of features}
#'   \item{`halflife`}{learning rate mode}
#' }
#'
#' @seealso \code{\link{kmeans_stream_update}},
#'   \code{\link{kmeans_stream_centers}},
#'   \code{\link{kmeans_batch}}
#'
#' @references MacQueen, J. (1967). Some methods for classification and analysis
#' of #' multivariate observations. \emph{Proceedings of the Fifth Berkeley
#' Symposium}, 1, 281-297.
#'
#' Sculley, D. (2010). Web-scale k-means clustering. \emph{Proceedings of the
#' 19th International Conference on World Wide Web}, 1177-1178.
#'
#' @examples
#' model <- kmeans_stream_new(k = 3L, d = 2L)
#' model$k
#' model$d
#'
#' @export
kmeans_stream_new <- function(k, d, halflife = -1) {
  if (!is.numeric(k) || length(k) != 1 || k != as.integer(k) || k <= 0)
    stop("k must be a positive integer")
  if (!is.numeric(d) || length(d) != 1 || d != as.integer(d) || d <= 0)
    stop("d must be a positive integer")
  if (!is.numeric(halflife) || length(halflife) != 1)
    stop("halflife must be a single numeric value")
  if (halflife != -1 && (halflife <= 0 || halflife >= 1))
    stop("halflife must be -1 (count-based) or a value in (0, 1)")
  
  ptr <- .Call(C_kmeans_stream_new,
               as.integer(k),
               as.integer(d),
               as.double(halflife))
  list(ptr = ptr, k = k, d = d, halflife = halflife)
}

#' Update a Streaming K-Means Model with One Observation
#'
#' Processes a single observation, updating the nearest centroid in place.
#' During the warm-up phase (first \code{k} observations), each point is
#' used directly as an initial centroid.
#'
#' @param model a streaming k-means model created by
#'   \code{\link{kmeans_stream_new}}
#' @param x a numeric vector of length \code{d}
#'
#' @return integer, the cluster assignment for \code{x} (1-indexed)
#'
#' @seealso \code{\link{kmeans_stream_new}}
#'
#' @examples
#' model <- kmeans_stream_new(k = 2L, d = 2L)
#' assignment <- kmeans_stream_update(model, c(1.0, 2.0))
#' assignment
#'
#' @export
kmeans_stream_update <- function(model, x) {
  if (is.null(model$ptr))
    stop("'model' must be a non-null pointer to the kmeans_stream model")
  if (!is.numeric(x) || length(x) != model$d)
    stop("'x' must be a numeric vector of length d = ", model$d)
  
  .Call(C_kmeans_stream_update, model$ptr, as.double(x))
}

#' Extract Current Centroids from a Streaming K-Means Model
#'
#' Returns the current centroid positions as a matrix. During the
#' warm-up phase, only the centroids initialised so far contain
#' meaningful values.
#'
#' @param model a streaming k-means model created by
#'   \code{\link{kmeans_stream_new}}
#'
#' @return a \code{k x d} numeric matrix of current centroid positions,
#'   one centroid per row
#'
#' @seealso \code{\link{kmeans_stream_new}}, \code{\link{kmeans_stream_update}}
#'
#' @examples
#' model <- kmeans_stream_new(k = 2L, d = 2L)
#' kmeans_stream_update(model, c(1.0, 2.0))
#' kmeans_stream_update(model, c(4.0, 5.0))
#' kmeans_stream_centers(model)
#'
#' @export
kmeans_stream_centers <- function(model) {
  if (!is.list(model) || is.null(model$ptr))
    stop("model must be a kmeans_stream model created by kmeans_stream_new()")
  
  .Call(C_kmeans_stream_centers, model$ptr)
}