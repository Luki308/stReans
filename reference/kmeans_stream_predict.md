# Predict Cluster Assignment for One Observation

Returns the index of the nearest centroid to `x` without updating the
model.

## Usage

``` r
kmeans_stream_predict(model, x)
```

## Arguments

- model:

  a streaming k-means model created by
  [`kmeans_stream_new`](https://luki308.github.io/stReans/reference/kmeans_stream_new.md)

- x:

  a numeric vector of length `d`

## Value

integer, the cluster assignment for `x` (1-indexed)

## See also

[`kmeans_stream_new`](https://luki308.github.io/stReans/reference/kmeans_stream_new.md),
[`kmeans_stream_update`](https://luki308.github.io/stReans/reference/kmeans_stream_update.md)

## Examples

``` r
model <- kmeans_stream_new(k = 2L, d = 2L)
kmeans_stream_update(model, c(0.0, 0.0))
#> [1] 1
kmeans_stream_update(model, c(5.0, 5.0))
#> [1] 2
kmeans_stream_predict(model, c(0.1, 0.1))
#> [1] 1
```
