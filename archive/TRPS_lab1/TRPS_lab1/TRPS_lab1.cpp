#include <iostream>
#include "ring_list.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Ring_list list;
	std::cout << "Введите предложение или /q"<<std::endl;
	std::string str;
	while (str != "/q") {
		std::getline(std::cin, str);
		if (str!="/q")
			list.add(str);
	}
	std::cout <<"Все предложения:" << std::endl;
	list.print();
	std::cout << std::endl;
	std::cout << sizeof(list)<<std::endl;

	list.sort();
	std::cout << "Все предложения после сортировки:" << std::endl;
	list.print();

	std::cout << "Напишите предложение, которое необходимо найти:" << std::endl << std::endl;
	std::getline(std::cin, str);
	if (list.find(str))
		std::cout << "Предложение найдено" << std::endl << std::endl;
	else
		std::cout << "Предложение не найдено" << std::endl << std::endl;

	std::cout << "Введите предложение на удаление:" << std::endl << std::endl;
	std::getline(std::cin, str);
	list.erase(str);

	std::cout << "Все предложения:" << std::endl;
	list.print();
	std::cout << std::endl;


}

