/*
1. Написать функцию, которая вычисляет сумму списка аргументов произвольной длины с разными типами элементов списка.
15:00 01.09.2017
*/
#include <iostream>
#include <cstdarg>
#include <map>
#include <functional>
using namespace std;

namespace Task1
{
	double sum(double s)
	{
		return s;
	}

	template<typename ... Args>
	double sum(double s, Args... args)
	{
		return sum(args...) + s;
	}
}

template<typename ... Args>
void executeTask(int number,Args... args)
{
	switch(number)
	{
	case 1:
		cout << "Task1 : " << Task1::sum(args...) << endl;
		break;
	default:
		cout << "Invalid task number , try again" << endl;
		break;
	}
}

int main()
{
	//executeTask(1, 2, 4, 5);


	system("pause");
	return 0;
}