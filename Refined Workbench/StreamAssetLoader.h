#pragma once
#include "IWorkerAction.h"
#include <string>

class IExecutionEvent;
class StreamAssetLoader :    public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String path;
	IExecutionEvent* execEvent;
};

