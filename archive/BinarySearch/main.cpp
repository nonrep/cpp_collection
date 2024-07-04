#include <iostream>

int binarySearch(const int* arr, int n, int elem){
    int first = 0;
    int last = n - 1;
    while (first < last){
        int middle = (last + first) / 2;
        if (arr[middle] < elem)
            first = middle + 1;
        else
            last = middle;
    }
    return first;
}

int main(){
    std::cout<<"start\n";
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    std::cout<<"answer "<<arr[binarySearch(arr,13,5)];
}