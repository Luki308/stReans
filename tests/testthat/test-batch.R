test_that("kmeans_batch returns correct structure", {
  X <- matrix(rnorm(100), nrow = 50, ncol = 2)
  result <- kmeans_batch(X, k = 3L, max_iter = 100L, tol = 1e-6)
  
  expect_type(result, "list")
  expect_named(result, c("centers", "assignments", "iterations"))
  expect_equal(nrow(result$centers), 3L)
  expect_equal(ncol(result$centers), 2L)
  expect_equal(length(result$assignments), 50L)
})

test_that("kmeans_batch assignments are 1-indexed and in range", {
  X <- matrix(rnorm(60), nrow = 30, ncol = 2)
  result <- kmeans_batch(X, k = 3L, max_iter = 100L, tol = 1e-6)
  
  expect_true(all(result$assignments >= 1L))
  expect_true(all(result$assignments <= 3L))
})

test_that("kmeans_batch with k=1 assigns all points to cluster 1", {
  X <- matrix(rnorm(40), nrow = 20, ncol = 2)
  result <- kmeans_batch(X, k = 1L, max_iter = 100L, tol = 1e-6)
  
  expect_true(all(result$assignments == 1L))
})

test_that("kmeans_batch centroid is correct for k=1", {
  X <- matrix(c(1, 2, 3, 4, 5, 6), nrow = 3, byrow = TRUE)
  result <- kmeans_batch(X, k = 1L, max_iter = 100L, tol = 1e-6)
  
  # centroid must be column means
  expect_equal(result$centers[1, 1], mean(X[, 1]), tolerance = 1e-6)
  expect_equal(result$centers[1, 2], mean(X[, 2]), tolerance = 1e-6)
})

test_that("kmeans_batch recovers well-separated clusters", {
  # two clearly separated clusters — should always find them
  set.seed(42)
  cluster1 <- matrix(rnorm(40, mean = 0,  sd = 0.1), nrow = 20, ncol = 2)
  cluster2 <- matrix(rnorm(40, mean = 10, sd = 0.1), nrow = 20, ncol = 2)
  X <- rbind(cluster1, cluster2)
  
  result <- kmeans_batch(X, k = 2L, max_iter = 100L, tol = 1e-6)
  
  # all first 20 should share one label, all last 20 the other
  labels1 <- result$assignments[1:20]
  labels2 <- result$assignments[21:40]
  expect_equal(length(unique(labels1)), 1L)
  expect_equal(length(unique(labels2)), 1L)
  expect_false(labels1[1] == labels2[1])
})

test_that("kmeans_batch works for 1D data", {
  X <- matrix(c(1, 2, 10, 11), nrow = 4, ncol = 1)
  result <- kmeans_batch(X, k = 2L, max_iter = 100L, tol = 1e-6)
  
  expect_equal(nrow(result$centers), 2L)
  expect_equal(ncol(result$centers), 1L)
})

test_that("kmeans_batch input validation catches bad inputs", {
  X <- matrix(rnorm(20), nrow = 10, ncol = 2)
  
  expect_error(kmeans_batch(as.integer(X), k = 2L, max_iter = 10L, tol = 1e-4),
               "numeric matrix")
  expect_error(kmeans_batch(X, k = 0L, max_iter = 10L, tol = 1e-4),
               "between 1")
  expect_error(kmeans_batch(X, k = 11L, max_iter = 10L, tol = 1e-4),
               "between 1")
  expect_error(kmeans_batch(X, k = 2.5, max_iter = 10L, tol = 1e-4),
               "integer")
})

test_that("kmeans_batch with d>n", {
  n <- 100
  d <- 150
  X <- matrix(rnorm(n*d), nrow=n, ncol=d)
  
  k <- 5
  result <- kmeans_batch(X, k = k, max_iter = 100, tol = 1e-6)
  
  # correct structure
  expect_equal(nrow(result$centers), k)
  expect_equal(ncol(result$centers), d)
  expect_equal(length(result$assignments), n)
  
  # assignments in valid range
  expect_true(all(result$assignments >= 1L))
  expect_true(all(result$assignments <= k))
  
  # all clusters are non-empty?
  expect_equal(length(unique(result$assignments)), k)
})