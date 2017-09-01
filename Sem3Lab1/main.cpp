/*
1. Написать функцию, которая вычисляет сумму списка аргументов произвольной длины с разными типами элементов списка.
15:00 01.09.2017
*/
/*
2. Написать функцию, которая вычисляет минимальное значение списка
аргументов произвольной длины с разными типами элементов списка.*/

#include <iostream>
#include <cstdarg>
#include <map>
#include <functional>
#include <algorithm>
#include <initializer_list>
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

namespace Task2
{
	double min(double d1, double d2)
	{
		return d1 < d2 ? d1 : d2;
	}

	template<typename ...T>
	double min(double d1,double d2, T...t)
	{
		double m = d1 < d2 ? d1 : d2;
		return min(m, t...);
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

	case 2:
		if (sizeof...(args) > 0)
		{
			cout << "Task2 : " << Task2::min(args...) << endl;	
		}
		else
			cout << "Task2 : invalid param list length" << endl;
		break;

	default:
		cout << "Invalid task number , try again" << endl;
		break;
	}
}

int main()
{
	//executeTask(1, 2, 4, 5);
	executeTask(2, 7, 2.5, 1, 0.22, 88,0.1);

	system("pause");
	return 0;
}