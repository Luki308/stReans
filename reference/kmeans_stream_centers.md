# Extract Current Centroids from a Streaming K-Means Model

Returns the current centroid positions as a matrix. During the warm-up
phase, only the centroids initialised so far contain meaningful values.

## Usage

``` r
kmeans_stream_centers(model)
```

## Arguments

- model:

  a streaming k-means model created by
  [`kmeans_stream_new`](https://luki308.github.io/stReans/reference/kmeans_stream_new.md)

## Value

a `k x d` numeric matrix of current centroid positions, one centroid per
row

## See also

[`kmeans_stream_new`](https://luki308.github.io/stReans/reference/kmeans_stream_new.md),
[`kmeans_stream_update`](https://luki308.github.io/stReans/reference/kmeans_stream_update.md)

## Examples

``` r
model <- kmeans_stream_new(k = 2L, d = 2L)
kmeans_stream_update(model, c(1.0, 2.0))
#> [1] 1
kmeans_stream_update(model, c(4.0, 5.0))
#> [1] 2
kmeans_stream_centers(model)
#>      [,1] [,2]
#> [1,]    1    2
#> [2,]    4    5
```
