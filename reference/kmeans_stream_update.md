# Update a Streaming K-Means Model with One Observation

Processes a single observation, updating the nearest centroid in place.
During the warm-up phase (first `k` observations), each point is used
directly as an initial centroid.

## Usage

``` r
kmeans_stream_update(model, x)
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

[`kmeans_stream_new`](https://luki308.github.io/stReans/reference/kmeans_stream_new.md)

## Examples

``` r
model <- kmeans_stream_new(k = 2L, d = 2L)
assignment <- kmeans_stream_update(model, c(1.0, 2.0))
assignment
#> [1] 1
```
