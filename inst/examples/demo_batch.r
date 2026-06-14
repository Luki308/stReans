library(stReans)
set.seed(42)
cluster1 <- matrix(rnorm(40, mean = 0,  sd = 0.5), nrow = 20, ncol = 2)
cluster2 <- matrix(rnorm(40, mean = 5,  sd = 0.5), nrow = 20, ncol = 2)
cluster3 <- matrix(rnorm(40, mean = 10, sd = 0.5), nrow = 20, ncol = 2)
X <- rbind(cluster1, cluster2, cluster3)
X <- X[sample(nrow(X)),] # for better intial centers

result <- kmeans_batch(X, k = 3L, max_iter = 100L, tol = 1e-6)

plot(X[, 1], X[, 2],
     col = result$assignments,
     pch = 16, cex = 1.5,
     xlab = "X1", ylab = "X2",
     main = "K-Means Batch Clustering")

points(result$centers[, 1], result$centers[, 2],
       col = 1:3, pch = 4, cex = 3, lwd = 3)

legend("topleft",
       legend = paste("Cluster", 1:3),
       col = 1:3, pch = 16)