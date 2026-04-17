#include "singleton.h"

#include <print>

int main() {
	std::println("---Singleton Example---");
	int value = 6;

	auto& instance = Singleton::instance();
	instance.setData(value);
	std::println("m_data set to {}", value);

	{
		auto& instance = Singleton::instance();
		std::println("m_data is {}", instance.getData());
	}

	//Singleton s;

	return 0;
}
