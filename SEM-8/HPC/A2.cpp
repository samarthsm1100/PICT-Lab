#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int> &arr, int l, int m, int r) 
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int> &arr, int l, int r) 
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n; ++i)
    {
        int start = i % 2;
        #pragma omp parallel for default(none) shared(arr, n, start)
        for (int j = start; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);
            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main()
{
    omp_set_num_threads(4); 
    const int size = 10000;
    vector<int> arr(size), arr_copy(size);

    for (int i = 0; i < size; ++i) 
    {
        arr[i] = rand() % 1000;
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
    arr = arr_copy;

    // Measure parallel Merge Sort execution time
    double par_duration_merge
    #pragma omp parallel
    {
        #pragma omp single
        {
            start = omp_get_wtime();
            parallelMergeSort(arr, 0, size - 1);
            stop = omp_get_wtime();
            par_duration_merge = stop - start;
        }
    }
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
