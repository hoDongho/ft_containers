#include <iostream>
#include <vector>
#include <algorithm>
#include "ft.hpp"

template <typename T>
void	printSize(std::vector<T>& v1, ft::vector<T>& ft1)
{
	std::cout << "-----Print Size-----" << std::endl;
	std::cout << "std: " << v1.capacity() << " " << v1.size() << " " << v1.max_size() << std::endl;
	std::cout << "ft: " << ft1.capacity() << " " << ft1.size() << " " << ft1.max_size() << std::endl << std::endl;
}

template <typename T>
void	printElements(std::vector<T>& v1, ft::vector<T>& ft1)
{
	std::cout << "-----Print Elements-----" << std::endl;
	// std::cout << "std: ";
	// for (std::vector<int>::iterator i = v1.begin(); i != v1.end(); i++)
	// {
	// 	std::cout << *(i) << " ";
	// }

	// std::cout << std::endl;

	// std::cout << "ft: ";
	// for (ft::vector<int>::iterator i = ft1.begin(); i != ft1.end(); i++)
	// {
	// 	std::cout << *(i) << " ";
	// }

	std::cout << "std: ";
	for (std::vector<int>::size_type i = 0; i != v1.size(); ++i)
	{
		std::cout << v1[i] << " ";
	}

	std::cout << std::endl;

	std::cout << "ft: ";
	for (ft::vector<int>::size_type i = 0; i != ft1.size(); ++i)
	{
		std::cout << v1[i] << " ";
	}

	std::cout << std::endl << std::endl;
}

template <typename T>
void	printElements(std::vector<T>& v1, ft::vector<T>& ft1, int)
{
	std::cout << "-----Reverse Print Elements-----" << std::endl;
	for (std::vector<int>::reverse_iterator i = v1.rbegin(); i != v1.rend(); i++)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;

	for (ft::vector<int>::reverse_iterator i = ft1.rbegin(); i != ft1.rend(); i++)
	{
		std::cout << *(i) << " ";
	}

	std::cout << std::endl << std::endl;
}

int main()
{
	std::vector<int> v1;
	ft::vector<int> ft1;

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/          Basic          /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	v1.push_back(42);
	ft1.push_back(42);

	v1.push_back(23);
	ft1.push_back(23);

	v1.push_back(52);
	ft1.push_back(52);

	printElements(v1, ft1);
	printElements(v1, ft1, 0);
	printSize(v1, ft1);

	std::cout << "\n/  size, val constructor  /\n" << std::endl;

	std::vector<int> v2(5, 42);
	ft::vector<int> ft2(5, 42);

	printElements(v2, ft2);

	std::cout << "\n/  iterator constructor  /\n" << std::endl;

	std::vector<int> v3(v1.begin(), v1.end());
	ft::vector<int> ft3(v1.begin(), v1.end());

	printElements(v3, ft3);

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/         Resize          /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	v1.resize(2);
	ft1.resize(2);

	printElements(v1, ft1);
	printSize(v1, ft1);

	v1.resize(10);
	ft1.resize(10);

	printElements(v1, ft1);
	printSize(v1, ft1);

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/         Reserve         /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	v1.reserve(2);
	ft1.reserve(2);

	printElements(v1, ft1);
	printSize(v1, ft1);

	v1.reserve(15);
	ft1.reserve(15);

	printElements(v1, ft1);
	printSize(v1, ft1);

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/        operator[]       /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	std::cout << v1[0] << std::endl;
	std::cout << ft1[0] << std::endl;

	std::cout << v1[123] << std::endl;
	std::cout << ft1[123] << std::endl;

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/            at           /" << std::endl
				<<	"/                         /" << std::endl << std::endl;
	try
	{
		std::cout << v1.at(0) << std::endl;
		std::cout << v1.at(123) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		std::cout << ft1.at(0) << std::endl;
		std::cout << ft1.at(123) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/           front         /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	std::cout << v1.front() << std::endl;
	std::cout << ft1.front() << std::endl;

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/           back          /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	std::cout << v1.back() << std::endl;
	std::cout << ft1.back() << std::endl;

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/          assign         /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	std::vector<int> v4(4, 10);

	v1.assign(v4.begin(), v4.end());
	ft1.assign(v4.begin(), v4.end());

	printElements(v1, ft1);

	v1.assign(3, 5);
	ft1.assign(3, 5);

	printElements(v1, ft1);

	std::cout	<<	std::endl
				<<	"/                         /" << std::endl
				<<	"/         pop_back        /" << std::endl
				<<	"/                         /" << std::endl << std::endl;

	printElements(v1, ft1);

	for(std::vector<int>::size_type i = v1.size(); i > 1; i--)
		v1.pop_back();
	for(ft::vector<int>::size_type i = ft1.size(); i > 1; i--)
		ft1.pop_back();

	printElements(v1, ft1);

	system("leaks --quiet a.out");

	return (0);
}
	// std::cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << std::endl;

	// try {
	// 	v1.reserve(5);
	// }
	// catch (std::exception& e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
