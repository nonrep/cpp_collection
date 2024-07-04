#include <iostream>

int binarySearch(const int* arr, int n){
    int first = 0;
    int last = n - 1;
    while (first != last){
        int middle = (last + first) / 2;
        if (arr[first] >= arr[last])
            first = middle + 1;
        else
            last = middle;
    }
    return last;
}

int main(){
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    
    std::cout<<binarySearch(arr, n);
}