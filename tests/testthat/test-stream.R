test_that("kmeans_stream_new returns correct structure", {
  model <- kmeans_stream_new(k = 3L, d = 2L)
  
  expect_type(model, "list")
  expect_named(model, c("ptr", "k", "d", "halflife"))
  expect_equal(model$k, 3L)
  expect_equal(model$d, 2L)
  expect_equal(model$halflife, -1)
})

test_that("kmeans_stream_new returns external pointer", {
  model <- kmeans_stream_new(k = 2L, d = 3L)
  expect_true(is.list(model))
  expect_true(!is.null(model$ptr))
  expect_equal(typeof(model$ptr), "externalptr")
})

test_that("kmeans_stream_new accepts halflife parameter", {
  model <- kmeans_stream_new(k = 2L, d = 2L, halflife = 0.1)
  expect_equal(model$halflife, 0.1)
})

# ------------Tests for stream_update------------------------
test_that("kmeans_stream_update returns integer assignment", {
  model <- kmeans_stream_new(k = 2L, d = 2L)
  result <- kmeans_stream_update(model, c(1.0, 2.0))
  expect_type(result, "integer")
  expect_length(result, 1L)
})

test_that("kmeans_stream_update warm-up phase assigns sequentially", {
  model <- kmeans_stream_new(k = 3L, d = 2L)
  
  # first k points go to slots 1, 2, 3 during warm-up
  expect_equal(kmeans_stream_update(model, c(1.0, 2.0)), 1L)
  expect_equal(kmeans_stream_update(model, c(5.0, 6.0)), 2L)
  expect_equal(kmeans_stream_update(model, c(9.0, 10.0)), 3L)
})

test_that("kmeans_stream_update assignments are in valid range", {
  k <- 3L
  model <- kmeans_stream_new(k = k, d = 2L)
  
  set.seed(42)
  X <- matrix(rnorm(100), nrow = 50, ncol = 2)
  assignments <- integer(nrow(X))
  for (i in seq_len(nrow(X)))
    assignments[i] <- kmeans_stream_update(model, X[i, ])
  
  expect_true(all(assignments >= 1L))
  expect_true(all(assignments <= k))
})