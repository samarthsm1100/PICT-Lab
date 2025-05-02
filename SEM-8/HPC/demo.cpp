#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void display(vector<int>&vec){
    for(auto v: vec){
        cout << v << " ";
    }
    cout << endl;
}

void bubbleSort(vector<int>&vec){
    int n = vec.size();
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(vec[j]>vec[j+1]){
                swap(vec[j], vec[j+1]);
            }
        }
    }
    display(vec);
}

void parallelBubbleSort(vector<int>&vec){
    int n = vec.size();
    for(int i=0; i<n-1; i++){
        #pragma omp parallel for
        for(int j=0; j<n-i-1; j++){
            if(vec[j]>vec[j+1]){
                swap(vec[j], vec[j+1]);
            }
        }
    }
    display(vec);
}

void merge(vector<int>&vec, int l, int m, int r){
    int n1 = m-l+1;
    int n2 = r-m;

    vector<int> L(n1), R(n2);
    for(int i=0; i<n1; i++){
        L[i] = vec[l+i];
    }
    for(int j=0; j<n2; j++){
        R[j] = vec[m+1+j];
    }

    int i=0, j=0, k=l;
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            vec[k] = L[i];
            i++;
        }
        else{
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        vec[k] = L[i];
        k++;
        i++;
    }
    while(j<n2){
        vec[k] = R[j];
        k++;
        j++;
    }
}

void mergeSort(vector<int>&vec, int l, int r){
    if(l<r){
        int m = l + (r-l)/2;
        mergeSort(vec, l, m);
        mergeSort(vec, m+1, r);
        merge(vec, l, m, r);
    }
}

void parallelMergeSort(vector<int>&vec, int l, int r){
    if(l<r){
        int m = l + (r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(vec, l, m);
            #pragma omp section
            parallelMergeSort(vec, m+1, r);
        }
        merge(vec, l, m, r);
    }
}



int main(){
    omp_set_num_threads(4);

    int n,k;

    cout << "Enter number of elements: ";
    cin >> n;
    int size = n;

    vector<int>arr(n), arr_copy(n);
    cout << "Enter elements";
    for(int i=0; i<n; i++){
        cin>>k;
        arr[i]=k;
        arr_copy[i] = arr[i];
    }

    // Measure sequential Bubble Sort execution time
    double start = omp_get_wtime();
    bubbleSort(arr);
    double stop = omp_get_wtime();
    double seq_duration_bubble = stop - start;
    arr = arr_copy;

    // Measure parallel Bubble Sort execution time
    start = omp_get_wtime();
    parallelBubbleSort(arr);
    stop = omp_get_wtime();
    double par_duration_bubble = stop - start;
    arr = arr_copy;

    // Measure sequential Merge Sort execution time
    start = omp_get_wtime();
    mergeSort(arr, 0, size - 1);
    stop = omp_get_wtime();
    double seq_duration_merge = stop - start;
    display(arr);
    arr = arr_copy;

    // Measure parallel Merge Sort execution time
    start = omp_get_wtime();
    parallelMergeSort(arr, 0, size - 1);
    stop = omp_get_wtime();
    double par_duration_merge = stop - start;
    display(arr);
    arr = arr_copy;

    cout << "Total number of threads: " << omp_get_max_threads() << endl << endl;
    cout << "====================================================" << endl << endl;
    cout << "Sequential Bubble Sort Time: " << seq_duration_bubble * 1e6 << " microseconds" << endl << endl;
    cout << "Parallel Bubble Sort Time: " << par_duration_bubble * 1e6 << " microseconds" << endl << endl;
    cout << "Sequential Merge Sort Time: " << seq_duration_merge * 1e6 << " microseconds" << endl << endl;
    cout << "Parallel Merge Sort Time: " << par_duration_merge * 1e6 << " microseconds" << endl << endl;
    cout << "====================================================" << endl << endl;
    cout << "Speedup for Bubble Sort: " << seq_duration_bubble / par_duration_bubble << endl << endl;
    cout << "Speedup for Merge Sort: " << seq_duration_merge / par_duration_merge << endl << endl;
    cout << "====================================================" << endl << endl;
    cout << "Note: The time is in microseconds." << endl;
    cout << "The time complexity of Bubble Sort is O(n^2) and Merge Sort is O(n log n)." << endl;
    cout << "The parallel time complexity of Bubble Sort is O(n^2/p) and Merge Sort is O(n log n/p)." << endl << endl;

    return 0;

}