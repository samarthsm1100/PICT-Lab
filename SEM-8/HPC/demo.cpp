#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int>&arr){
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int>&arr){
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        #pragma omp parallel for
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void mergeSort(vector<int>&arr, int l, int r){
    if(l<r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr,l,m,r);
    }
}

void merge(vector<int>&arr, int l, int m, int r){
    int n1 = m-l+1;
    int n2 = r-m;

    vector<int> L(n1), R(n2);

    for(int i=0; i<n1; i++)
        L[i] = arr[l+i];
    for(int i=0; i<n2; i++)
        R[i] = arr[m+1+i]

    int i=0, j=0, k=l;

    while(i<n1 && j<n2){
        if(L[i] < R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

int main(){
    const int n = 10000;
    vector<int>arr(n), arr_copy(n);
    for(int i=0; i<n; i++){
        arr[i] = rand()%1000;
        arr_copy[i] = arr[i];
    }

    double start = omp_get_wtime();
    bubbleSort(arr);
    double stop = omp_get_wtime();
    double seq_duration_bubble = stop - start;

    start = omp_get_wtime();
    parallelBubbleSort(arr);
    stop = omp_get_wtime();
    double par_duration_bubble = stop - start;

    start = omp_get_wtime();
    mergeSort(arr, 0, );
    stop = omp_get_wtime();
    double seq_duration_merge = stop - start;

    start = omp_get_wtime();
    bubbleSort(arr);
    stop = omp_get_wtime();
    double par_duration_merge = stop - start;


}