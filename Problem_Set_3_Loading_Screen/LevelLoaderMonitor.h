#pragma once
#include "GenericMonitor.h"
class LevelLoaderMonitor : public GenericMonitor
{
public:
	void tryEnter() override;
	void reportExit() override;
	void increment();

	float getProgress();

private:
	int assetCount = 0;
	int completedCount = 0;
};

