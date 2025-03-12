#pragma once

#include <string>
#include "IWorkerAction.h"

class GenericMonitor;
class LevelLoaderMonitor;

class StreamAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, GenericMonitor* monitor, LevelLoaderMonitor* levelLoaderMonitor);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String path;
	GenericMonitor* monitor;
	LevelLoaderMonitor* levelLoaderMonitor;
};

