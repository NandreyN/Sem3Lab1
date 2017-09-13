/*
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
	template<typename T>
	T sum(T t)
	{
		return t;
	}

	template<typename T, typename ... Args>
	auto sum(T s, Args... args)
	{
		return [](auto a, auto b) {return a + b; } (s, sum(args...));
	}

	template<typename ... T>
	double sumNew(T ...t)
	{
		double s = 0.;
		auto f = [&t..., &s](){int dummy[] = { ((void)(s += t,0),0)... }; };
		f();
		return s;
	}
}

namespace Task2
{
	template<typename F>
	auto min(F d)
	{
		return d;
	}

	template<typename F, typename ...T>
	auto min(F d, T...t)
	{
		return [](auto a, auto b) {return a < b ? a : b; }(d, min(t...));
	}


	template<typename ... T>
	auto minNew(T...t)
	{
		auto data = { static_cast<double>(t)... };
		return *std::min_element(data.begin(), data.end());
	}
}

namespace Task3
{
	tuple<int, double> _tup;

	template<typename ... T>
	void sumTypes(double a, T ... tail)
	{
		std::get<1>(_tup) += a;
		sumTypes(tail...);
	}


	template<typename ... T>
	void sumTypes(int a, T ... tail)
	{
		std::get<0>(_tup) += a;
		sumTypes(tail...);
	}

	void sumTypes()
	{}


	template<typename U, typename ... T>
	tuple<int, double> getTup(U u, T ...t)
	{
		// call overloaded functions
		sumTypes(t...);
		return _tup;
	}
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
		return [&separator,&t...]()
		{
			std::ostringstream oss;
			int a[] = { ((void)(oss << t << separator), 0) ... };
			return oss.str();
		}();
	}
}


int main()
{
	//cout << Task1::sum(1, 2, 3, 4, 5.8) << endl << Task1::sumNew(1, 2, 3, 4, 5.8) << endl;
	//cout << Task2::min(4, 55, 6, 7, 1.22, -2.69) << endl << Task2::minNew(4, 55, 6, 7, 1.22, -2.69) << endl;
	//tuple<int, double> tp = Task3::getTup(2, 7, 2.5, 1, 0.22, 88, 0.1);
	//cout <<"INt : " << std::get<0>(tp)<< " Double : " << std::get<1>(tp)<< endl;
	//executeTask(3, 7.1, 8, 4.2, 1, 4.8);
	//executeTask(4, 1, 2, 1, 4);
	cout << Task5::ToString(" ", "One", 2, "three", 4.4) << endl;
	//cout << Task6::find(3,20.55,5,"dasdasd",8, "oiipuiuoi") << endl;

	return 0;
}