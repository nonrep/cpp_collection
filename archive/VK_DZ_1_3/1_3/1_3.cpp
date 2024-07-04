/*
1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток OK. 
Иначе записать FAIL
*/
#include <iostream>

std::string func(unsigned int number) {
    //в counter будут записываться биты с единицами со сдвигом влево
    int counter = 0;
    do {
        if (number & 0b1) {
            counter = counter << 0b1;
            counter = counter | 0b1;
            if (counter == 0b11)
                return "FAIL";
        }
        number = number >> 1;
    } while (number > 0);

    return (counter == 0b1) ? "OK" : "FAIL";
}


int main()
{
    unsigned int number;
    std::cin >> number;
    std::cout << func(number);
   
}
