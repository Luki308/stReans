set.seed(42)
cluster1 <- matrix(rnorm(40, mean = 0,  sd = 0.5), nrow = 20)
cluster2 <- matrix(rnorm(40, mean = 5,  sd = 0.5), nrow = 20)
cluster3 <- matrix(rnorm(40, mean = 10, sd = 0.5), nrow = 20)
X <- rbind(cluster1, cluster2, cluster3)

# shuffle so clusters arrive interleaved
set.seed(1)
X <- X[sample(nrow(X)), ]

model <- kmeans_stream_new(k = 3, d = 2)
assignments <- integer(nrow(X))

for (i in seq_len(nrow(X))) {
  assignments[i] <- kmeans_stream_update(model, X[i, ])
}

centers <- kmeans_stream_centers(model)

plot(X[, 1], X[, 2],
     col  = assignments,
     pch  = 16, cex  = 1.5,
     xlab = "X1", ylab = "X2",
     main = "Streaming K-Means (shuffled arrival order)")

points(centers[, 1], centers[, 2],
       col = 1:3, pch = 4, cex = 3, lwd = 3)

legend("topleft",
       legend = paste("Cluster", 1:3),
       col    = 1:3, pch = 16)
