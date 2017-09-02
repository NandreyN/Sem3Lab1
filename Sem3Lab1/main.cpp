﻿/*
1. Написать функцию, которая вычисляет сумму списка аргументов произвольной длины с разными типами элементов списка.
15:00 01.09.2017
*/
/*
2. Написать функцию, которая вычисляет минимальное значение списка
аргументов произвольной длины с разными типами элементов списка.*/

/*
3. Написать функцию, которая вычисляет кортеж tuple<int,double> от списка
аргументов произвольной длины с разными типами элементов списка.
В первое поле кортежа суммируются значения типа int, а во второе – значения типа double.*/

/*
4. Написать функцию наподобие функции из задачи 1), только операция над элементами списка
задается функциональным объектом. */

/*
Написать функцию ToString, которая список своих разнотипных аргументов преобразует в
строковой значение (типа std::string). */

/*
6. По заданному типу и кортежу типа tuple<…> найти первый элемент, тип которого совпадает с
заданным*/

/*
7. По заданному типу и кортежу типа tuple<…> вернуть кортеж типа tuple<…>, поля которого –
все поля из исходного кортежа, тип которых совпадает с заданным.
*/

#include <stdio.h>
#include <iostream>
#include <cstdarg>
#include <map>
#include <functional>
#include <algorithm>
#include <initializer_list>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>

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

	template<typename ... T>
	double sumNew(T ...t)
	{
		double s = 0.;
		int dummy[] = { ((void)(s += t,0),0)... };
		return s;
	}
}

namespace Task2
{
	double min(double d1, double d2)
	{
		return d1 < d2 ? d1 : d2;
	}

	template<typename ...T>
	double min(double d1, double d2, T...t)
	{
		double m = d1 < d2 ? d1 : d2;
		return min(m, t...);
	}


	template<typename ... T>
	double minNew(T...t)
	{
		auto data = { static_cast<double>(t)... };
		return *std::min_element(data.begin(), data.end());
	}
}

namespace Task3
{
	tuple<int, double> _tup;
	template<typename ... T>

	tuple<int, double> getTup(T ...t)
	{
		// call overloaded functions
		sum(t...);
		return _tup;
	}

	template<typename ... T>
	void sum(double a, T ... tail)
	{
		std::get<1>(_tup) += a;
		sum(tail...);
	}


	template<typename ... T>
	void sum(int a, T ... tail)
	{
		std::get<0>(_tup) += a;
		sum(tail...);
	}

	void sum()
	{}
}

namespace Task4
{
	//typedef double(*FuncObj)(double, double);

	struct Multiplicator
	{
		double operator()(double a, double b)
		{
			return a * b;
		}
		double neutral = 1;
	};

	struct Sub
	{
		double operator()(double a, double b)
		{
			return a - b;
		}
		double neutral = 0;
	};

	struct Sum
	{
		double operator()(double a, double b)
		{
			return a + b;
		}
		double neutral = 0;
	};

	template<typename FuncObj, typename ...T>
	double operation(FuncObj f, double a, T...t)
	{
		return f(a, operation(f, t...));
	}

	template<typename FuncObj, typename ...T>
	double operation(FuncObj f)
	{
		return f(f.neutral, f.neutral);
	}
}

namespace Task5
{
	template< typename ... T >
	std::string ToString(const string& separator, const T& ... t)
	{
		std::ostringstream oss;
		int a[] = { ((void)(oss << t << separator), 1) ... };
		return oss.str();
	}
}

namespace Task6
{
	template<typename S, typename ...T>
	S find(T...t)
	{
		return std::get<S>(std::make_tuple(t...));
	}
}

namespace Task7
{
	template<typename S, typename ... T>
	void f(const tuple<T...> &a)
	{
		
	}
}

template<typename ... Args>
void executeTask(int number, Args... args)
{
	tuple<int, double> t;

	switch (number)
	{
	case 1:
		cout << "Task1 : " << Task1::sum(args...) << endl;
		cout << "Task1 new : " << Task1::sumNew(args...) << endl;
		break;

	case 2:
		if (sizeof...(args) > 0)
		{
			cout << "Task2 : " << Task2::min(args...) << endl;
			cout << "Task2 new : " << Task2::minNew(args...) << endl;
		}
		else
			cout << "Task2 : invalid param list length" << endl;
		break;

	case 3:
		t = Task3::getTup(args...);
		cout << "Task3 , int : " << std::get<0>(t) << ", double : " << std::get<1>(t) << endl;
		break;
	case 4:
		cout << "Task4 , mul: " << Task4::operation(Task4::Multiplicator{}, args...) << endl;
		cout << "Task4 , sub: " << Task4::operation(Task4::Sub{}, args...) << endl;
		cout << "Task4 , add: " << Task4::operation(Task4::Sum{}, args...) << endl;
		break;

	default:
		cout << "Invalid task number , try again" << endl;
		break;
	}
}

int main()
{
	//executeTask(1, 2, 4, 5,6.6);
	//executeTask(2, 7, 2.5, 1, 0.22, 88,0.1);
	//executeTask(3, 7.1, 8, 4.2, 1, 4.8);
	//executeTask(4, 1, 2, 1, 4);
	//cout << Task5::ToString(" ", "One", 2,"three",4.4) << endl;
	//cout << Task6::find<double>(2, 3, 4.222, 'f', "ddsada") << endl;
	Task7::f<int>(make_tuple(1, 2.2, 'c'));
	return 0;
}