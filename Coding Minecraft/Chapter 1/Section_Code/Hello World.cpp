#include <iostream>
#include "Hello World.h"

int Hello_World::pow(int x, int n) 
{
	int result = x;
	for (int i = 0; i < n; i++) 
	{
		result *= x;
	}

	if (n == 0) 
	{
		return 1;
	}
	else if (n < 0) 
	{
		return -1;
	}
	return result;
}

void Hello_World::private_method() 
{
	std::cout << "I am a private method on Hello_World" << std::endl;
}

int main()
{
	Hello_World* my_class = new Hello_World();
	std::cout << my_class->pow(5, 3) << std::endl;
	std::cout << my_class->pow(5, 0) << std::endl;
	std::cout << my_class->pow(5, -1) << std::endl;

	std::cout << "Hello world!" << std::endl;
	system("pause");
	return 0;
}