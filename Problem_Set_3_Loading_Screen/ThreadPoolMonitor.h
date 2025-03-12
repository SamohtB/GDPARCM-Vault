#pragma once
#include "GenericMonitor.h"
class ThreadPoolMonitor : public GenericMonitor
{
public:
	ThreadPoolMonitor(int workerCount);

	void tryEnter() override;
	void reportExit() override;

private:
	int readyCount = 0;
};

