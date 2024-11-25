#include <stdlib.h>
#include <cmath>
#include "utils.h"

// CAlculate the mean value of a group
float mean(float *arr, int arr_len){
  float res = 0;
  for(int i = 0; i<arr_len; i++){
    res = res + arr[i];
  }
  res = res / arr_len;
  return res;
}
// Compare two float numbers (function required by qsort)
int compare_floats(const void *p, const void *q) {

  float x = *(const float *)p;
  float y = *(const float *)q;

  // Avoid using x - y, as it can cause undefined behavior
  if (x < y) {
    return -1;
  } else if (x > y) {
    return 1;
  }

  return 0;
}

// Find median in a group of numbers
// WARNING: sorts array in place
float median(float *arr, int arr_len) {
    
  float median;

  // Use stdlib's qsort to sort array in place
  qsort(arr, arr_len, sizeof(float), compare_floats);
  
  // If even number of elements take average of two middle elements
  if (arr_len % 2 == 0) {
    median = (arr[(arr_len - 1) / 2] + arr[arr_len / 2]) / 2.0;
  } else {
    median = arr[arr_len / 2];
  }
  
  return median;
}

// Calculate Median Absolute Deviation (MAD) of array
// WARNING: manipulates array in place
float calc_mad(float *arr, int arr_len) {

  // Get the median of the array
  float med = median(arr, arr_len);

  // Calculate absolute deviation from the median for each element
  for (int i = 0; i < arr_len; i++) {
    arr[i] = fabs(arr[i] - med);
  }

  // Find the median of the deviations
  return median(arr, arr_len);
}

// Calculate the dot product between two vectors
float dot_product(float *a, float *b, int len) {
  float sum = 0;
  for (int i = 0; i < len; i++) {
    sum += a[i] * b[i];
  }

  return sum;
}

// Perform matrix multiplication between two 2D arrays
int matrix_multiply(const float *a, 
                    const float *b,
                    int a_rows, 
                    int a_cols, 
                    int b_rows, 
                    int b_cols,
                    float *prod) {

  float sum;

  // Check to make sure we can multiply the matrices
  if (a_cols != b_rows) {
    return 0;
  }

  // Calculate the dot product for each element in return matrix
  for (int i = 0; i < a_rows; i++) {
    for (int j = 0; j < b_cols; j++) {
      sum = 0;
      for (int k = 0; k < a_cols; k++) {
        sum += a[(i * a_cols) + k] * b[(k * b_cols) + j];
      }
      prod[(i * b_cols) + j] = sum;
    }
  }

  return 1;
}

// Calculate the Mahalanobis distance based on mean and inverse covariance
float mahalanobis(const float *x, 
                  const float *mu, 
                  const float *inv_cov, 
                  int len) {

  float x_minus_mu[1][len];
  float x_minus_mu_t[len][1];
  float left_term[1][len];
  float mahal[1][1];

  // Subtract each element in X from the mean
  for (int i = 0; i < len; i++) {
    x_minus_mu[0][i] = x[i] - mu[i];
  }

  // Compute product of prev term and inverse covariance
  matrix_multiply(*x_minus_mu, inv_cov, 1, len, len, len, *left_term);

  // Transpose matrix
  for (int i = 0; i < len; i++) {
    x_minus_mu_t[i][0] = x_minus_mu[0][i];
  }

  // Matrix multiply prev term and difference
  matrix_multiply(*left_term, *x_minus_mu_t, 1, len, len, 1, *mahal);

  return mahal[0][0];
}

// Calculate the mean squared error between two arrays
float calc_mse(const float *x, const float *x_hat, const int len) {
  
  float mse = 0;

  // Square difference between each set of elements
  for (int i = 0; i < len; i++) {
    mse += ((x[i] - x_hat[i])*(x[i] - x_hat[i]));
  }

  return mse / len;
}

float heat_index(float T_C, float H){
    float HI = 0;
    //Convert Celsius to Fahrenheit for the heat index formula
    float T = 0;
    T = celcius_to_fareheit(T_C);
    // Coefficients for the heat index formula
    float c1 =  -42.379;
    float c2 = 2.04901523;
    float c3 = 10.14333127;
    float c4 = -0.22475541;
    float c5 = -0.00683783;
    float c6 = -0.05481717;
    float c7 = 0.00122874;
    float c8 = 0.00085282;
    float c9 = -0.00000199;
    
    //Calculate heat index using the formula
    
    if (T<80){//if temperature is less than 80F
        HI = 0.5 * (T + 61.0 + ((T-68.0)*1.2) + (H*0.094));
    }
    else{
        float adjustment = 0;
        if (H <=13 && T<112 && T>80){
            adjustment = ((13-H)/4)*sqrt((17-fabs(T-95))/17);
        }
        else if (H >= 85 && T<87 && T>80){
            adjustment = ((H-85)/10) * ((87-T)/5); 
        } 
        //Calculate heat index using the formula
        HI = (c1 + (c2 * T) + (c3 * H) + (c4 * T * H) +
            (c5 * pow(T,2)) + (c6 * pow(H,2)) + (c7 * pow(T,2) * H) +
            (c8 * T * pow(H,2)) + (c9 * pow(T,2) * pow(H,2))) - adjustment;
        }
    return HI;
}

float celcius_to_fareheit(float C){
    return (C*1.8)+32;
}
float fareheit_to_celcius(float F){
    return (F-32)/1.8;
}