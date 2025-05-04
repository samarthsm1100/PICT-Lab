#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int minimum_sequential(int arr[], int n){
    int minval = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i]<minval) minval = arr[i];
    }
    return minval;
}

int maximum_sequential(int arr[], int n){
    int maxval = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i]>maxval) maxval = arr[i];
    }
    return maxval;
}

int sum_sequential(int arr[], int n){
    int sum = 0;
    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    return sum;
}

double average_sequential(int arr[], int n){
    return (double)sum_sequential(arr,n)/n;
}

int minimum_parallel(int arr[], int n){
    int minval = arr[0];
    #pragma omp parallel for reduction(min: minval)
    for(int i=0; i<n; i++){
        if(arr[i]<minval) minval = arr[i];
    }
    return minval;
}

int maximum_parallel(int arr[], int n){
    int maxval = arr[0];
    #pragma omp parallel for reduction(max: maxval)
    for(int i=0; i<n; i++){
        if(arr[i]>maxval) maxval = arr[i];
    }
    return maxval;
}

int sum_parallel(int arr[], int n){
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    return sum;
}

double average_parallel(int arr[], int n){
    return (double)sum_parallel(arr,n)/n;
}

int main() 
{
    omp_set_num_threads(8);
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;
  int arr[n];
  cout << "Enter the elements: ";
  for(int i = 0; i < n; i++) 
  {
    cin >> arr[i];
  }

  double start = omp_get_wtime();
  cout << "\nThe minimum value (sequential) is: " << minimum_sequential(arr, n) << '\n';
  double stop = omp_get_wtime();
  double duration1 = stop - start;
  cout << "Time taken by sequential minval: " << duration1 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe maximum value (sequential) is: " << maximum_sequential(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration2 = stop - start;
  cout << "Time taken by sequential maxval: " << duration2 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe summation (sequential) is: " << sum_sequential(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration3 = stop - start;
  cout << "Time taken by sequential sum: " << duration3 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe average (sequential) is: " << average_sequential(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration4 = stop - start;
  cout << "Time taken by sequential average: " << duration4 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe minimum value (parallel) is: " << minimum_parallel(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration5 = stop - start;
  cout << "Time taken by parallel minval: " << duration5 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe maximum value (parallel) is: " << maximum_parallel(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration6 = stop - start;
  cout << "Time taken by parallel maxval: " << duration6 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe summation (parallel) is: " << sum_parallel(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration7 = stop - start;
  cout << "Time taken by parallel sum: " << duration7 * 1e6 << " microseconds" << endl;

  start = omp_get_wtime();
  cout << "\nThe average (parallel) is: " << average_parallel(arr, n) << '\n';
  stop = omp_get_wtime();
  double duration8 = stop - start;
  cout << "Time taken by parallel average: " << duration8 * 1e6 << " microseconds" << endl;

  cout << "\n----------------- SPEEDUP --------------------\n";
  cout << "Minval: " << duration1/duration5 << endl;
  cout << "Maxval: " << duration2/duration6 << endl;
  cout << "Summation: " << duration3/duration7 << endl;
  cout << "Average: " << duration4/duration8 << endl;

  return 0;  
}