#include <iostream>
#include <cassert>

// структура для хранения номера массива
template<class T>
struct Pair {
    T data;
    int arrayNumber;

    Pair() : data(), arrayNumber() {}
    Pair(T data, int arrayNumber) : data(data), arrayNumber(arrayNumber) {}
};

// внешняя функция для базовых типов данных
template<class T>
class IsLessDefault {
public:
    bool operator()(const Pair<T>& l, const Pair<T>& r) { return (l.data < r.data); }
};

// реализация кучи
template<class T, class IsLess = IsLessDefault<T>>
class Heap {
public:
    Heap(int size);
    Heap(const Heap& other);
    Heap& operator=(const Heap& other);
    ~Heap();

    void SiftUp(int i);
    void SiftDown(int i);
    void Insert(Pair<T> pair);
    Pair<T> ExtractMax();
    void print() {
        for (int i = 0; i < size; i++)
            std::cout << buffer[i].data << " ";
    }

private:
    int size = 0;
    int bufferSize;
    Pair<T>* buffer;
};

template<class T, class IsLess>
Heap<T, IsLess>::Heap(int size) {
    bufferSize = size;
    buffer = new Pair<T>[bufferSize];
}

template<class T, class IsLess>
Heap<T, IsLess>::Heap(const Heap& other) {
    bufferSize = other.bufferSize;
    size = other.size;
    buffer = new T[bufferSize];
    for (int i = 0; i < size; i++)
        buffer[i] = other.buffer[i];
}

template<class T, class IsLess>
Heap<T, IsLess>& Heap<T, IsLess>::operator=(const Heap& other) {
    if (this == &other)
        return *this;

    delete[] buffer;
    bufferSize = other.bufferSize;
    size = other.size;
    buffer = new T[bufferSize];
    for (int i = 0; i < size; i++)
        buffer[i] = other.buffer[i]; \

        return *this;
}

template<class T, class IsLess>
Heap<T, IsLess>::~Heap() { delete[] buffer; }

template<class T, class IsLess>
void Heap<T, IsLess>::SiftUp(int i) {
    int parent = (i - 1) / 2;
    if (i <= 0 || !IsLess()(buffer[parent], buffer[i]))
        return;

    std::swap(buffer[i], buffer[parent]);
    SiftUp(parent);
}

template<class T, class IsLess>
void Heap<T, IsLess>::SiftDown(int i) {
    int right = 2 * i + 1;
    int left = 2 * i + 2;
    int largest = i;
    if (right < size && IsLess()(buffer[largest], buffer[right]))
        largest = right;
    if (left < size && IsLess()(buffer[largest], buffer[left]))
        largest = left;

    if (largest != i) {
        std::swap(buffer[i], buffer[largest]);
        SiftDown(largest);
    }
}

template<class T, class IsLess>
void Heap<T, IsLess>::Insert(Pair<T> pair) {
    assert(size < bufferSize);
    buffer[size] = pair;
    SiftUp(size);
    ++size;
}

template<class T, class IsLess>
Pair<T> Heap<T, IsLess>::ExtractMax() {
    assert(size > 0);
    Pair<T> result = buffer[0];
    std::swap(buffer[0], buffer[size - 1]);
    --size;
    if (size > 0)
        SiftDown(0);

    return result;
}

template<class T, class IsLess = IsLessDefault<T>>
T* heapSort(const T* const* const& arrays, T* sizes, const int& k, int numberOfElements) {
    Heap<T> heap(k);
    T* sortedArray = new T[numberOfElements];

    // вставка в кучу максимальных элементов с каждого массива
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            Pair<T> temp(arrays[i][sizes[i] - 1], i);
            heap.Insert(temp);
            --sizes[i];
        }
    }

    // Вставка и извелечение по одному элементу с концов массивов
    // Условие numberOfElements > k нужно, чтобы все элементы были записаны в кучу  
    // При выходе из цикла, в куче останется k элементов, которые будут записаны в sortedArray отдельно
    while (numberOfElements > 0) {
        Pair<T> temp = heap.ExtractMax();
        sortedArray[numberOfElements - 1] = temp.data;
        int whichArray = temp.arrayNumber;
        if (sizes[whichArray] > 0) {
        temp.data = arrays[whichArray][sizes[whichArray] - 1];
        heap.Insert(temp);
        --sizes[whichArray];
        }
        --numberOfElements;
    }

    return sortedArray;
}

int main() {
    int k;
    std::cin >> k;

    // для хранения общего количество элементов
    int numberOfElements = 0;

    // массив из указателей на массивы, которые подаются на вход
    int** arrays = new int* [k];

    // массив для хранения размеров массивов
    int* sizes = new int[k];

    //заполнение массива arrays входными данными
    for (int i = 0; i < k; i++) {
        std::cin >> sizes[i];
        numberOfElements += sizes[i];
        arrays[i] = new int[sizes[i]];
        for (int j = 0; j < sizes[i]; j++)
            std::cin >> arrays[i][j];
    }

    // вывод отсортированного массива
    int* sortedArray = heapSort(arrays, sizes, k, numberOfElements);
    for (int i = 0; i < numberOfElements; i++)
        std::cout << sortedArray[i] << " ";

    // освобождение памяти
    for (int i = 0; i < k; i++)
        delete[] arrays[i];

    delete[] sortedArray;
    delete[] arrays;
    delete[] sizes;
}