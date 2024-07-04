/*
Реализовать дек с динамическим зацикленным буфером (на основе динамического массива)
*/
#include <iostream>
#include <cassert>

class Deque {
public:
    Deque();

    //правило трех
    ~Deque();
    Deque(const Deque& other);
    Deque& operator=(const Deque& other);

    void Resize();
    void Push_front(int data);
    void Push_back(int data);
    int Pop_front();
    int Pop_back();
    
private:
    int head = 0;
    int tail = 0;
    int size = 0;
    int buffersize = 4;
    int* buffer;
};

Deque::Deque() {
    buffer = new int[buffersize];
}

Deque::~Deque() {
    delete[] buffer;
}

Deque::Deque(const Deque& other) {
    buffersize = other.buffersize;
    buffer = new int[buffersize];
    size = other.size;
    head = 0;
    tail = size - 1;
    for (int i = head, j = 0; j < size; i++, j++) {
        buffer[j] = other.buffer[i % other.buffersize];
    }
}

Deque& Deque::operator=(const Deque& other) {
    if (this != &other) {
        delete[] buffer;
        buffersize = other.buffersize;
        size = other.size;
        head = 0;
        tail = size - 1;
        buffer = new int[buffersize];
        for (int i = head, j = 0; j < size; i++, j++) {
            buffer[j] = other.buffer[i % other.buffersize];
        }
    }
    return *this;
}

void Deque::Resize() {
    int* newBuffer = new int[buffersize << 1];
    for (int i = head, j = 0; j < size; i++, j++) {
        newBuffer[j] = buffer[i % buffersize];
    }
    head = 0;
    tail = size - 1;
    buffersize = buffersize << 1;
    delete[] buffer;
    buffer = newBuffer;
}

void Deque::Push_front(int data) {
    if (size == buffersize)
        Resize();
    
    if (size == 0) {
        buffer[0] = data;
    } else {
        head = (buffersize - 1 + head) % buffersize;
        buffer[head] = data;
    }
    ++size;
}

void Deque::Push_back(int data) {
    if (size == buffersize)
        Resize();

    if (size == 0) {
        buffer[0] = data;
    }
    else {
        tail = (buffersize + 1 + tail) % buffersize;
        buffer[tail] = data;
    }
    ++size;

}

int Deque::Pop_front() {
    if (size == 0)
        return -1;
    int returnData = buffer[head];
    buffer[head] = -1;
    if (size == 1)
        head = tail = 0;
    else
        head = (size == 1) ? 0 : (head + 1) % buffersize;
    --size;
    return returnData;
}

int Deque::Pop_back() {
    if (size == 0)
        return -1;
    int returnData = buffer[tail];
    buffer[tail] = -1;
    if (size == 1) 
        tail = head = 0;
    else
        tail = (buffersize + tail - 1) % buffersize;
    --size;
    return returnData;
}

int main()
{
    Deque deque;
    int n;
    bool result = true;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int command, data;
        std::cin >> command >> data;
        switch (command) {
            case 1:
                deque.Push_front(data);
                break;
            case 2:
                if (deque.Pop_front() != data)
                    result = false;
                break;
            case 3:
                deque.Push_back(data);
                break;
            case 4:
                if (deque.Pop_back() != data)
                    result = false;
                break;
            default:
                assert(false);
        }
    }
    std::cout << (result ? "YES" : "NO");
}
