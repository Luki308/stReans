#include <math.h>
#include "distances.h"

double euclidean_distance(double* a, double* b, size_t n){
    double sum = 0.0;
    for(size_t i=0; i<n; i++){
        sum += pow(a[i]-b[i],2);
    }
    sum = sqrt(sum);
    return sum;
}