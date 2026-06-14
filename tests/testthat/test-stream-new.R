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