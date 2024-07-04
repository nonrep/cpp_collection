#include <iostream>
#include <string>

class DynamicArray {
public:
    DynamicArray(int n);

    std::string operator[](int i);
    void Resize();
    void Push_back(std::string data);
    int Search(std::string data);
    void Sort();
    void Erase(std::string data);
    
private:
    void QuickSort(int low, int high);
    int Partition(int low, int high);

    int size = 0;
    int buffersize = 4;
    std::string* buffer;
    int c = 0;
};

DynamicArray::DynamicArray(int n) {
    buffersize = n;
    buffer = new std::string[buffersize];
}

std::string DynamicArray::operator[](int i) {
    return buffer[i];
}

void DynamicArray::Resize() {
    std::string* newBuffer = new std::string[buffersize << 1];
    for (int i = 0; i < size; i++) {
        newBuffer[i] = buffer[i];
    }
    buffersize = buffersize << 1;
    delete[] buffer;
    buffer = newBuffer;
}

void DynamicArray::Push_back(std::string data) {
    if (size == buffersize)
        Resize();
    buffer[size] = data;
    ++size;

}

int DynamicArray::Search(std::string data) {
    int first = 0;
    int last = size - 1;
    while (first < last) {
        int middle = (last - first) / 2;
        if (data > buffer[middle]) {
            first = middle + 1;
        } else {
            last = middle;
        }
    }
    return (data != buffer[first] || first == size) ? -1 : first;
}

void DynamicArray::Sort() {
    if (size > 1)
        ++c;
        std::cout<<c<<std::endl;
        QuickSort(0, size - 1);
}

void DynamicArray::QuickSort(int first, int last) {
    if (first < last) {
        ++c;
        std::cout<<c<<std::endl;
        int pivotIndex = Partition(first, last);
        QuickSort(first, pivotIndex - 1);
        QuickSort(pivotIndex + 1, last);
    }
}

int DynamicArray::Partition(int first, int last) {
    std::string pivot = buffer[last];
    int i = (first - 1);
    for (int j = first; j <= last - 1; j++) {
        if (buffer[j] <= pivot) {
            ++c;
            std::cout<<c<<std::endl;
            i++;
            std::swap(buffer[i], buffer[j]);
        }
    }
    std::swap(buffer[i + 1], buffer[last]);
    return (i + 1);
}

void DynamicArray::Erase(std::string data) {
    int dataIndex = Search(data);
    if (dataIndex == -1)
        return;
    for (int i = dataIndex; i < size - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    --size;
}

int main()
{
    /*
    int n = 100;

    DynamicArray arr(n);
    for (int i = 0; i < n - 1; i++)
    {
        std::string str = std::to_string(i) + "asmkl";
        arr.Push_back(str);
    }
    arr.Sort();

    */
        std::string* ptr;
        std::cout << sizeof(ptr);
}
