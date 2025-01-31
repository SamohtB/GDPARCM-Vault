#pragma once
#include <iostream>
#include <thread>

class IETThreadTemplate
{
public:
	IETThreadTemplate();
	~IETThreadTemplate();

	void start();
	static void sleep(int ms);

protected:
	virtual void run() = 0;
};

