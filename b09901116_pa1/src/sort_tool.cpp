// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************
// alg22f125 & VuecMuc7
#include "sort_tool.h"
#include<iostream>
#include<cmath>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++){
        int key = data[i];
        int j = i - 1; 
        while(j>=0 && data[j]>key){
            data[j+1] = data[j];
            j=j-1;
        }
        data[j+1] = key; 
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, (data.size()-1));
}

// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low<high){
        int mid = Partition(data,low,high);
        QuickSortSubVector(data,low,mid-1);
        QuickSortSubVector(data, mid+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[high];
    int i = low-1;
    for (int j = low; j<high; j++){
        if (data[j]<=pivot){
            i++;
            int temp = data[j];
            data[j] = data[i];
            data[i] = temp;
        }
    }
    int temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low<high){
        int mid = floor((low + high)/2);
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}
// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low+1;
    int n2 = high - middle2+1; 
    int Left[n1];
    int Right[n2];
    for (int i = 0; i<n1; i++){
        Left[i] = data[low+i];
    }
    for (int j = 0; j < n2 ; j++){
        Right[j] = data[middle2 + j];
    }
    int i = 0;
    int j = 0;
    int final_index = low;
    //Left[n1] = NULL;
    //Right[n2] = NULL;
    while (i<n1 && j<n2){   
        if (Left[i]<=Right[j]){
            data[final_index] = Left[i];
            i++;
        }
        else{
            data[final_index] = Right[j];
            j++;
        }
        final_index++;
    }
    while(i<n1){
        data[final_index] = Left[i];
        final_index++;
        i++;
    }
    while(j<n2){
        data[final_index] = Right[j];
        final_index++;
        j++;
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]

    for (int i = data.size() - 1; i >= 0; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2*root +1;
    int right = 2*root + 2;
    int largest = root; 

    if (left < heapSize && data[left]> data[largest]){
        largest = left; 
    }
    if (right < heapSize && data[right]>data[largest]){
        largest = right;
    }
    if (largest != root){
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = floor(heapSize/2); i >= 0; i--){
        MaxHeapify(data, i);
    }
}
