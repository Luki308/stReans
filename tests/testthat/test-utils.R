test_that("euclidean_distance between identical points is zero", {
  expect_equal(.euclidean_distance(c(1, 2, 3), c(1, 2, 3)), 0.0)
})

test_that("euclidean_distance is correct for known values", {
  # 3-4-5 right triangle
  expect_equal(.euclidean_distance(c(0, 0), c(3, 4)), 5.0)
})

test_that("euclidean_distance is symmetric", {
  a <- c(1.5, 2.7, 3.1)
  b <- c(4.2, 0.3, 1.8)
  expect_equal(.euclidean_distance(a, b), .euclidean_distance(b, a))
})

test_that("euclidean_distance is non-negative", {
  expect_gte(.euclidean_distance(c(1, 2), c(3, 4)), 0.0)
})

test_that("euclidean_distance errors on length mismatch", {
  expect_error(.euclidean_distance(c(1, 2), c(1, 2, 3)))
})

test_that("col_to_row_major round-trips correctly", {
  X <- matrix(c(1, 2, 3, 4, 5, 6), nrow = 2, ncol = 3)
  # convert to row-major flat vector then back to col-major
  flat_row <- .col_to_row_major(X)
  restored <- .row_to_col_major(flat_row, nrow(X), ncol(X))
  # restored should match original column-major layout
  expect_equal(restored, as.double(X))
})

test_that("col_to_row_major produces correct element order", {
  # matrix: row 1 = (1,2), row 2 = (3,4)
  # col-major storage: 1,3,2,4
  # row-major storage: 1,2,3,4
  X <- matrix(c(1, 3, 2, 4), nrow = 2, ncol = 2)  # col-major: rows are (1,2),(3,4)
  flat <- .col_to_row_major(X)
  expect_equal(flat, c(1, 2, 3, 4))
})

test_that("row_to_col_major produces correct element order", {
  # row-major: 1,2,3,4 → col-major: 1,3,2,4
  flat <- c(1, 2, 3, 4)
  result <- .row_to_col_major(flat, 2L, 2L)
  expect_equal(result, c(1, 3, 2, 4))
})