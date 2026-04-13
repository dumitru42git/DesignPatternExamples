#pragma once

class Singleton {
public:
	static Singleton& instance();

	void setData(int data);
	int getData() const;

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;

protected:
	Singleton() = default;
	~Singleton() = default;

public:
	int m_data = 0;
};
