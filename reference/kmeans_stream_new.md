# Create a New Streaming K-Means Model

Initialises a streaming k-means model. The first `k` observations passed
to
[`kmeans_stream_update()`](https://luki308.github.io/stReans/reference/kmeans_stream_update.md)
will be used as initial centroids (warm-up phase). Clustering begins
properly after `k` observations have been seen.

## Usage

``` r
kmeans_stream_new(k, d, halflife = -1)
```

## Arguments

- k:

  a positive integer, number of clusters

- d:

  a positive integer, number of features (must match observations passed
  to update/predict)

- halflife:

  numeric learning rate. Use `-1` (default) for count-based updates or a
  value in `(0, 1)` for fixed-rate updates (forgetful, recent points
  weighted more heavily)

## Value

a list with components:

- `ptr`:

  external pointer to the C model struct

- `k`:

  number of clusters

- `d`:

  number of features

- `halflife`:

  learning rate mode

## References

MacQueen, J. (1967). Some methods for classification and analysis of \#'
multivariate observations. *Proceedings of the Fifth Berkeley
Symposium*, 1, 281-297.

Sculley, D. (2010). Web-scale k-means clustering. *Proceedings of the
19th International Conference on World Wide Web*, 1177-1178.

## See also

[`kmeans_stream_update`](https://luki308.github.io/stReans/reference/kmeans_stream_update.md),
`kmeans_stream_predict`,
[`kmeans_stream_centers`](https://luki308.github.io/stReans/reference/kmeans_stream_centers.md),
[`kmeans_batch`](https://luki308.github.io/stReans/reference/kmeans_batch.md)

## Examples

``` r
model <- kmeans_stream_new(k = 3L, d = 2L)
model$k
#> [1] 3
model$d
#> [1] 2
```
