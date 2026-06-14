# stReans

An R package implementing **batch** and **streaming** k-means clustering
with core computations written in C via the R native API.

## Overview

`stReans` provides two complementary approaches to k-means clustering:

- **[`kmeans_batch()`](https://luki308.github.io/stReans/reference/kmeans_batch.md)** -
  Lloyd’s algorithm for datasets that fit in memory, with convergence
  detection based on centroid shift
- **`kmeans_stream()`** - incremental online k-means for data streams,
  processing one observation at a time without storing the full dataset
  *(coming soon)*

## Installation

The package is not on CRAN. Install directly from GitHub:

``` r

# install.packages("devtools")
devtools::install_github("Luki308/stReans")
```

## Usage

### Batch K-Means

``` r

library(stReans)

# generate three well-separated clusters
set.seed(42)
cluster1 <- matrix(rnorm(40, mean = 0,  sd = 0.5), nrow = 20)
cluster2 <- matrix(rnorm(40, mean = 5,  sd = 0.5), nrow = 20)
cluster3 <- matrix(rnorm(40, mean = 10, sd = 0.5), nrow = 20)
X <- rbind(cluster1, cluster2, cluster3)

# run batch k-means
result <- kmeans_batch(X, k = 3L, max_iter = 100L, tol = 1e-6)

result$centers      # cluster centroids
result$assignments  # cluster label per observation
result$iterations   # how many iterations ran
```

### Visualising Results

``` r

plot(X[, 1], X[, 2],
     col  = result$assignments,
     pch  = 16,
     cex  = 1.5,
     xlab = "X1",
     ylab = "X2",
     main = "Batch K-Means Clustering")

points(result$centers[, 1], result$centers[, 2],
       col = 1:3, pch = 4, cex = 3, lwd = 3)

legend("topright",
       legend = paste("Cluster", 1:3),
       col    = 1:3,
       pch    = 16)
```

## Implementation Details

### C Backend

- `src/distances.c` - Euclidean distance, column-major ↔︎ row-major
  matrix conversion utilities
- `src/kmeans_batch.c` - Lloyd’s algorithm
- `src/kmeans_stream.c` - incremental online k-means *(in progress)*
- `src/init.c` - native routine registration via `R_registerRoutines`

## Development

``` r
# install dependencies
install.packages(c("devtools", "testthat", "roxygen2", "pkgdown"))

# clone and build
git clone https://github.com/Luki308/stReans.git
cd stReans

# in R
devtools::install()
devtools::test()
devtools::check()
```

## Testing

Unit tests are written with [testthat](https://testthat.r-lib.org/) and
run automatically via GitHub Actions on Linux, macOS, and Windows:

- `tests/testthat/test-batch.R` - correctness, edge cases, input
  validation
- `tests/testthat/test-utils.R` - distance and layout conversion
  utilities

## License

MIT © Łukasz Lepianka
