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
}

namespace Task3
{
	template<class U, class T>
	struct equal
	{
		const static bool value = false;
	};

	template<class U>
	struct equal<U, U>
	{
		const static bool value = true;
	};

	template<class ... T>
	auto getTuple(const T& ... args)
	{
		tuple<int, double> tuple;
		auto f = [&tuple](auto arg)
		{
			bool isInteger = (equal<decltype(arg), int>::value) ? true : false;
			if (isInteger)
			{
				std::get<int>(tuple) += arg;
				return;
			}
			bool isDouble = (equal<decltype(arg), double>::value) ? true : false;
			if (isDouble)
				std::get<double>(tuple) += arg;
		};
		int dummy[] = {(f(args),0)...};
		return tuple;
	}
}


namespace Task4
{
	template< typename ... T >
	std::string ToString(const string& separator, const T& ... t)
	{
		return[&separator, &t...]()
		{
			std::ostringstream oss;
			int dummy[] = { ((void)(oss << t << separator), 0) ... };
			string result = oss.str();
			return result.substr(0, result.size() - separator.size());
		}();
	}
}

template<class ... T>
void callTask(int num, const T & ... t)
{
	tuple<int, double> tup;
	switch(num)
	{
	case 1:
		cout << "Task1, Sum. Parameters : (" << Task4::ToString(" ", t...) <<  " ), result is : " << Task1::sum(t...) << endl;
		break;
	case 2:
		cout << "Task2, Minimum. Parameters : (" << Task4::ToString(" ", t...) << " ), result is : " << Task2::min(t...) << endl;
		break;
	case 3:
		tup = Task3::getTuple(t...);
		cout << "Task3, Tuple. Parameters : (" << Task4::ToString(" ", t...) << " ), result is : Int = "<<std::get<int>(tup)<<", Double = " <<
			std::get<double>(tup) << endl;
		break;
	case 4:
		cout << "Task4, ToString. Parameters : (" << Task4::ToString(";", t...) << " ), result as string : " << Task4::ToString("!!", t...) << endl;
		break;
	}
}

int main()
{
	callTask(4, 2, 3, 4, 5, 0.8);
	return 0;
}