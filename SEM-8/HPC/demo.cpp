#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(int l, int m, int r, vector<int>& arr) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int l, int r, vector<int>& arr) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m, arr);
        mergeSort(m + 1, r, arr);
        merge(l, m, r, arr);
    }
}

void parallelBubble(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int start = i % 2;
        #pragma omp parallel for shared(arr, n, start)
        for (int j = start; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void parallelMerge(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMerge(arr, l, m);
            #pragma omp section
            parallelMerge(arr, m + 1, r);
        }
        merge(l, m, r, arr);
    }
}

bool isSorted(vector<int>&vec){
    for(int i=1; i<vec.size(); i++){
        if(vec[i]<vec[i-1]){
            return false;
        }
    }
    return true;
}

int main() {
    int n = 10000;
    vector<int> arr(n), arr_copy(n);

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }



    double start = omp_get_wtime();
    bubbleSort(arr);
    double stop = omp_get_wtime();
    double bub = stop - start;
    cout << isSorted(arr);
    arr = arr_copy;

    start = omp_get_wtime();
    mergeSort(0, n - 1, arr);
    stop = omp_get_wtime();
    double merge = stop - start;
    cout << isSorted(arr);
    arr = arr_copy;

    start = omp_get_wtime();
    parallelBubble(arr);
    stop = omp_get_wtime();
    double par_bub = stop - start;
    cout << isSorted(arr);
    arr = arr_copy;

    double par_merge;
    #pragma omp parallel
    {
        #pragma omp single
        {
            start = omp_get_wtime();
            parallelMerge(arr, 0, n - 1);
            stop = omp_get_wtime();
            par_merge = stop - start;
        }
    }
    cout << isSorted(arr);

    cout << endl;

    cout << "Seq bubble: " << bub * 1e6 << endl;
    cout << "Seq merge: " << merge * 1e6 << endl;
    cout << "Par bubble: " << par_bub * 1e6 << endl;
    cout << "Par merge: " << par_merge * 1e6 << endl;

    return 0;
}
