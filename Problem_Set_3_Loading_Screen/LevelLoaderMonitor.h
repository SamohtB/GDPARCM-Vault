#pragma once
#include "GenericMonitor.h"
class LevelLoaderMonitor : public GenericMonitor
{
public:
	void tryEnter() override;
	void reportExit() override;
	void increment();

private:
	int assetCount = 0;
};

