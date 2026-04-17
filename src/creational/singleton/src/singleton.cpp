#include "singleton.h"

Singleton& Singleton::instance() {
	static Singleton singleton;
	return singleton;
}

void Singleton::setData(int data) {
	m_data = data;
}

int Singleton::getData() const {
	return m_data;
}
