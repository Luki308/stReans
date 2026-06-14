#' Create a new stremaing k-means model
#' @export
kmeans_stream_new <- function(k, d){
  ptr <- .Call(C_kmeans_stream_new, k, d)
  list(ptr = ptr, k=k, d=d)
}