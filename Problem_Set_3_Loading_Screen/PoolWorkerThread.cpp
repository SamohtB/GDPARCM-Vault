#include "PoolWorkerThread.h"
#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finished_task) : m_id(id), m_finished_task(finished_task) {}

PoolWorkerThread::~PoolWorkerThread() {}

int PoolWorkerThread::getThreadID()
{
	return this->m_id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->m_action = action;
}

void PoolWorkerThread::run()
{
	this->m_action->onStartTask();
	this->m_finished_task->onFinishedTask(this->m_id);
}
