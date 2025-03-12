#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finished_task);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

	int m_id = 0;
	IWorkerAction* m_action = nullptr;
	IFinishedTask* m_finished_task = nullptr;
};

