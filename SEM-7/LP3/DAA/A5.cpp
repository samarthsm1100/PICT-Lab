#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], int s, int e){

    int pivot = arr[s];

    int count = 0;
    for(int i=s+1; i<=e; i++){
        if(arr[i] < pivot) count++;
    }

    int pivotIndex = s+ count;
    swap(arr[s], arr[pivotIndex]);

    int i = s, j = e;
    while(i<pivotIndex && j>pivotIndex){
        while(arr[i]<pivot){
            i++;
        }
        while(arr[j]>pivot){
            j--;
        }
        if(i<pivotIndex && j>pivotIndex){
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quicksort(int arr[], int s, int e){
    if(s >= e) return;
    int p = partition(arr, s, e);
    quicksort(arr, s, p-1);
    quicksort(arr, p+1, e);
}

void quicksortRandom(int arr[], int s, int e){
    if(s >= e) return;
    int random = rand() % (e-s) + s;
    cout << "Random: " << random << endl;
    swap(arr[random], arr[s]);
    int p = partition(arr, s, e);
    quicksortRandom(arr, s, p-1);
    quicksortRandom(arr, p+1, e);
}

int main(){
    int arr[] = {10, 12, 15, 20, 1, 4, 17, 16, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    quicksortRandom(arr, 0, n-1);

    for(auto x: arr){
        cout << x << " ";
    } cout << endl;
    return 0;
}