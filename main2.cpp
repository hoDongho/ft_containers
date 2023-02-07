#include <iostream>
#include <vector>
#include "utils.hpp"

int main()
{
	std::vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	std::vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(50);

	std::vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);

	if (ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()))
		std::cout << "v1 < v2" << std::endl;
	else
		std::cout << "v1 >= v2" << std::endl;

	if (ft::lexicographical_compare(v1.begin(), v1.end(), v3.begin(), v3.end()))
		std::cout << "v1 < v3" << std::endl;
	else
		std::cout << "v1 >= v3" << std::endl;

	return (0);
}
