#include <iostream>

template<class T>
class IsLessDefault {
public:
    bool operator()(const T& l, const T& r) {
        return (l < r); 
    }
};

// медиана трех
template<class T, class IsLess = IsLessDefault<T>>
int Median(T* arr, int n) {
    int mid = n >> 1;
    if (IsLess()(arr[0],arr[mid])) {
        if (IsLess()(arr[mid],arr[n - 1]))
            return mid;
        else if (IsLess()(arr[0], arr[n - 1]))
            return n - 1;
        else
            return 0;
    } else {
        if (IsLess()(arr[n - 1], arr[mid]))
            return mid;
        else if (IsLess()(arr[n - 1], arr[0]))
            return n - 1;
        else
            return 0;
    }
}

template<class T, class IsLess = IsLessDefault<T>>
int Partition(T* arr, int n) {
    if (n - 1 <= 0) {
        return 0;
    }    
    
    int pivot_index = Median(arr, n);
    std::swap(arr[pivot_index], arr[0]);
    int pivot = arr[0];
    int i = n - 1;
    int j = i;
    while (j > 0) {
        if (IsLess()(pivot, arr[j])) {
            std::swap(arr[i], arr[j]);
            i--;
        }
        j--;
    }
    std::swap(arr[i], arr[0]);
    return i;
}

template<class T, class IsLess = IsLessDefault<T>>
int FindKStat(T* arr, int n, int k) {

    int first = 0;
    int last = n - 1;
    while (last > first) {
        int pivotPos = Partition(arr + first, last - first + 1) + first;
        if (pivotPos == k) {
            return arr[k];
        } else if (k < pivotPos) {
            last = pivotPos - 1;
        } else {
            first = pivotPos + 1;
        }
    }
    return arr[first];
}

int main() {
    int n;
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout<<FindKStat(arr, n, 0.1 * n)<<std::endl;
    std::cout<<FindKStat(arr, n, 0.5 * n)<<std::endl;
    std::cout<<FindKStat(arr, n, 0.9 * n)<<std::endl;

    delete[] arr;
}