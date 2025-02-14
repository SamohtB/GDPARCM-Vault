#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int worker_count) : m_name(name), m_worker_count(worker_count)
{
	for (int i = 0; i < m_worker_count; i++)
	{
		this->m_inactive_threads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();
	this->m_active_threads.clear();

	while (this->m_inactive_threads.empty() == false)
	{
		this->m_inactive_threads.pop();
	}
}

void ThreadPool::startScheduler()
{
	this->m_is_running = true;
	this->start();
}

void ThreadPool::stopScheduler()	
{
	this->m_is_running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->m_pending_actions.push(action);
}

void ThreadPool::run()
{
	while (this->m_is_running)
	{
		if (this->m_pending_actions.empty() == false)
		{
			if (this->m_inactive_threads.empty() == false)
			{
				PoolWorkerThread* worker_thread = this->m_inactive_threads.front();
				this->m_inactive_threads.pop();
				this->m_active_threads[worker_thread->getThreadID()] = worker_thread;

				worker_thread->assignTask(this->m_pending_actions.front());
				worker_thread->start();
				this->m_pending_actions.pop();

				std::cout << this->m_pending_actions.size() << " pending actions" << std::endl;
			}
		}
	}
}

void ThreadPool::onFinishedTask(int threadID)
{
	if (this->m_active_threads[threadID] != nullptr)
	{
		delete this->m_active_threads[threadID];
		this->m_active_threads.erase(threadID);

		this->m_inactive_threads.push(new PoolWorkerThread(threadID, this));
	}
}
