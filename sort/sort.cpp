#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
using  namespace  std;
using namespace chrono;
void InsertSort(vector<int>& arr){
    int i,j;
    for(i = 1;i<arr.size();i++){
        int num = arr[i];
        for(j = i-1;j>=0&& arr[j]>num;j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = num;
    }
}
void ShellSort(vector<int>& arr){
    int i,j;
    int gap = arr.size()/2;
    while(gap>0){
        for(i = gap;i<arr.size();i++){
            int num = arr[i];
            for(j = i-gap;j>=0 && arr[j]>num;j -= gap){
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = num;
        }
        gap /= 2;
    }
}
void BubbleSort(vector<int>& arr){
    for(int i = 0;i<arr.size();i++){
        int flag = 0;
        for(int j = 0;j<arr.size()-i-1;j++){
            if(arr[j+1]< arr[j]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = 1;
            }
        }
        if(flag == 0){
            break;
        }
    }
}
void QuickSort(vector<int>& arr,int left,int right){
    if(left>= right){
        return;
    }
    int i = left;
    int j = right;
    int num =  arr[left];
    while(i < j){
        while(i < j && arr[j]>= num){
            j--;
        }
        while(i < j && arr[i] <= num){
            i++;
        }
        if(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    arr[left] = arr[i];
    arr[i] = num;
    QuickSort(arr,i+1,right);
    QuickSort(arr,left,i-1); 

}
void SelectSort(vector<int>& arr){
    for(int i = 0;i<arr.size();i++){
        int minnum_index = i;
        for(int j = i+1;j<arr.size();j++){
            if(arr[j]<arr[minnum_index]){
                minnum_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minnum_index];
        arr[minnum_index] = temp;
    }
}
void OneAdjust(vector<int>& arr,int root, int len){
    int i = root;
    int j = 2*i+1;
    int num = arr[root];
    while(j < len){
        if(j+1 < len && arr[j+1]> arr[j]){
            j++;
        }
        if(arr[j] > num){
            arr[i] = arr[j];
            i = j;
            j = 2*i +1;
        }
        else{
            break;
        }
    }
    arr[i] = num;
}
void CreateHeap(vector<int>& arr){
    int root = arr.size()/2 -1;
    for(;root>=0;root--){
        OneAdjust(arr,root,arr.size());
    }
}
void HeapSort(vector<int>& arr){
    CreateHeap(arr);
    for(int i = 0;i<arr.size()-1;i++){
        int temp = arr[0];
        arr[0] = arr[arr.size()-1-i];
        arr[arr.size()-1-i] = temp;
        OneAdjust(arr,0,arr.size()-i-1);
    }
}
void Merge(vector<int>& arr,int left,int right){
    int i = left;
    int middle = (left+right)/2;
    int j = middle+1;
    vector<int> temp(right-left+1);
    int temp_index = 0;
    while(i <= middle && j<= right){
        if(arr[i]<=arr[j]){
            temp[temp_index] = arr[i];
            temp_index++;
            i++;
        }
        else{
            temp[temp_index] = arr[j];
            temp_index++;
            j++;
        }
    }
    while(i<=middle){
        temp[temp_index] = arr[i];
        temp_index++;
        i++;
    }
    while(j<=right){
        temp[temp_index] = arr[j];
        temp_index++;
        j++;
    }
    for(int i = 0;i<temp.size();i++){
        arr[left+i] = temp[i];
    }
}
void MergeSort(vector<int>& arr,int left,int right){
    if(left<right){
        int middle = (left+right) / 2;
        MergeSort(arr,left,middle);
        MergeSort(arr,middle+1,right);
        Merge(arr,left,right);
    }
}
int GetDigit(int num,int place){
    int k = 0;
    while(k<place){
        num /= 10;
        k++;
    }
    return num % 10;
}
int GetMaxWidth(vector<int>& arr){
    int maxWidth = 0;
    for(int i = 0;i<arr.size();i++){
        int countWidth = 0;
        int num = arr[i];
        while(num>0){
            num /= 10;
            countWidth++;
        }
        maxWidth = max(maxWidth,countWidth);
    }
    return maxWidth;
}
void RadixSort(vector<int>& arr){
    int maxWidth = GetMaxWidth(arr);
    vector<vector<int>> buckets(10);
    for(int i = 0;i<maxWidth;i++){
        for(int j = 0;j<arr.size();j++){
            buckets[GetDigit(arr[j],i)].push_back(arr[j]);
        }
        int index = 0;
        for(int j = 0;j<10;j++){
            for(int m = 0;m<buckets[j].size();m++){
                arr[index] = buckets[j][m];
                index++;
            }
            buckets[j].clear();
        }
    }
}
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    srand(static_cast<unsigned int>(time(nullptr)));
    generate(arr.begin(), arr.end(), rand);
    return arr;
}
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}
int main() {
    const int arraySize = 50000;
    vector<int> randomArray = generateRandomArray(arraySize);

    // 插入排序测试
    vector<int> insertSortedArray = randomArray;
    auto insertStart = high_resolution_clock::now();
    InsertSort(insertSortedArray);
    auto insertStop = high_resolution_clock::now();
    cout << "Insert Sort: " << (isSorted(insertSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Insert Sort Time: " << duration_cast<milliseconds>(insertStop - insertStart).count() << " ms" << endl;

    //希尔排序测试
    vector<int> shellSortedArray = randomArray;
    auto shellStart = high_resolution_clock::now();
    ShellSort(shellSortedArray);
    auto shellStop = high_resolution_clock::now();
    cout << "Shell Sort: " << (isSorted(shellSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Shell Sort Time: " << duration_cast<milliseconds>(shellStop - shellStart).count() << " ms" << endl;

    // 冒泡排序测试
    vector<int> bubbleSortedArray = randomArray;
    auto bubbleStart = high_resolution_clock::now();
    BubbleSort(bubbleSortedArray);
    auto bubbleStop = high_resolution_clock::now();
    cout << "Bubble Sort: " << (isSorted(bubbleSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Bubble Sort Time: " << duration_cast<milliseconds>(bubbleStop - bubbleStart).count() << " ms" << endl;

    // 快速排序测试
    vector<int> quickSortedArray = randomArray;
    auto quickStart = high_resolution_clock::now();
    QuickSort(quickSortedArray, 0, arraySize - 1);
    auto quickStop = high_resolution_clock::now();
    cout << "Quick Sort: " << (isSorted(quickSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Quick Sort Time: " << duration_cast<milliseconds>(quickStop - quickStart).count() << " ms" << endl;

    //选择排序测试
    vector<int> selectSortedArray = randomArray;
    auto selectStart = high_resolution_clock::now();
    SelectSort(selectSortedArray);
    auto selectStop = high_resolution_clock::now();
    cout << "Select Sort: " << (isSorted(selectSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Select Sort Time: " << duration_cast<milliseconds>(selectStop - selectStart).count() << " ms" << endl;
    
    //堆排序测试
    vector<int> heapSortedArray = randomArray;
    auto heapStart = high_resolution_clock::now();
    HeapSort(heapSortedArray);
    auto heapStop = high_resolution_clock::now();
    cout << "Heap Sort: " << (isSorted(heapSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Heap Sort Time: " << duration_cast<milliseconds>(heapStop - heapStart).count() << " ms" << endl;

    //归并排序测试
    vector<int> mergeSortedArray = randomArray;
    auto mergeStart = high_resolution_clock::now();
    MergeSort(mergeSortedArray, 0, arraySize - 1);
    auto mergeStop = high_resolution_clock::now();
    cout << "Merge Sort: " << (isSorted(mergeSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Merge Sort Time: " << duration_cast<milliseconds>(mergeStop - mergeStart).count() << " ms" << endl;

    //基数排序测试
    vector<int> radixSortedArray = randomArray;
    auto radixStart = high_resolution_clock::now();
    RadixSort(radixSortedArray);
    auto radixStop = high_resolution_clock::now();
    cout << "Radix Sort: " << (isSorted(radixSortedArray) ? "Passed" : "Failed") << endl;
    cout << "Radix Sort Time: " << duration_cast<milliseconds>(radixStop - radixStart).count() << " ms" << endl;

    return 0;
}