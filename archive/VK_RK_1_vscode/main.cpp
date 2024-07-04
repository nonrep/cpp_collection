#include <iostream>

class Stack {
public:
    Stack(int n);
    ~Stack();
    void Push(char data);
    void Pop();
    void Check();
    bool Result();

private:
    char* buffer;
    int buffersize;
    int size = 0;
    bool flag = true;
};

Stack::Stack(int n) {
    buffersize = n;
    buffer = new char[buffersize];
}

Stack::~Stack() {
    delete[] buffer;
}

void Stack::Push(char data) {
    buffer[size] = data;
    Check();
    ++size;
}

void Stack::Pop() {
    --size;
}

void Stack::Check() {
    if (buffer[size] == '(')
        return;
    if (buffer[size] == ')' && buffer[size - 1] == '('){
        Pop();
        Pop();
    }
}

bool Stack::Result() {
  if (size != 0)
      flag = false;
  return flag;
}

int main(){
    std::string input;
    std::cin >> input;
    Stack stack(input.length());
    for (int i = 0; i < input.length(); i++)
    {
        stack.Push(input[i]);
    }
    
    std::cout<< (stack.Result() ? "YES" : "NO");
}