#ifndef MD_UTILS_H
#define MD_UTILS_H

int compare_floats(const void *p, const void *q);
float mean(float *arr, int arr_len);
float median(float *arr, int arr_len);
float calc_mad(float *arr, int arr_len);
float dot_product(float *a, float *b, int a_len, int b_len);
int matrix_multiply(const float *a, 
                    const float *b, 
                    int a_rows, 
                    int a_cols, 
                    int b_rows, 
                    int b_cols,
                    float *prod);
float mahalanobis(const float *x, 
                  const float *mu, 
                  const float *inv_cov, 
                  int len);
float calc_mse(const float *x, const float *x_hat, const int len);
float heat_index(float T, float H); // this function will calculate the heat index at the Fareheit Unit, it must be transfer to Celcius when append to dataset 
float celcius_to_fareheit(float C); //this function will transfer Celcius degree to Fareheit degree
float fareheit_to_celcius(float F); //this function will transfer Fareheit degree to Celcius degree
#endif //MD_UTILS_H