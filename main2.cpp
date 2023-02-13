#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include "iterator.hpp"

int main()
{
	std::vector<int> v1;
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << " " << std::numeric_limits<ptrdiff_t>::max() << std::endl;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	try {
		v1.reserve(5);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	for (std::vector<int>::iterator i = v1.begin(); i != v1.end(); i++)
	{
		std::cout << *i << "\n";
	}
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << std::endl;

	std::vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(50);

	std::vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);

	if (ft::equal(v1.begin(), v1.end(), v2.begin()))
		std::cout << "v1 == v2" << std::endl;
	else
		std::cout << "v1 != v2" << std::endl;

	if (ft::equal(v1.begin(), v1.end(), v3.begin()))
		std::cout << "v1 == v3" << std::endl;
	else
		std::cout << "v1 != v3" << std::endl;

	if (std::equal(v1.begin(), v1.end(), v2.begin()))
		std::cout << "v1 == v2" << std::endl;
	else
		std::cout << "v1 != v2" << std::endl;

	if (std::equal(v1.begin(), v1.end(), v3.begin()))
		std::cout << "v1 == v3" << std::endl;
	else
		std::cout << "v1 != v3" << std::endl;

	return (0);
}
