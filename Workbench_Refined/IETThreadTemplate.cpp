#include "IETThreadTemplate.h"

IETThreadTemplate::IETThreadTemplate()
{
}

IETThreadTemplate::~IETThreadTemplate()
{
}

void IETThreadTemplate::start()
{
	std::thread(&IETThreadTemplate::run, this).detach();
}

void IETThreadTemplate::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
