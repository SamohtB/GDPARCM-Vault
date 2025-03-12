#pragma once

#include <string>
#include "IWorkerAction.h"

class GenericMonitor;

class StreamAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, GenericMonitor* monitor);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String path;
	GenericMonitor* monitor;
};

