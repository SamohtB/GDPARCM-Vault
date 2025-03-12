#include "ThreadPool.h"
#include "PoolWorkerThread.h"
#include "ThreadPoolMonitor.h"

ThreadPool::ThreadPool(String name, int worker_count) : m_name(name), m_worker_count(worker_count)
{
	for (int i = 0; i < m_worker_count; i++)
	{
		this->m_inactive_threads.push(new PoolWorkerThread(i, this));
	}

	this->monitor = new ThreadPoolMonitor(m_worker_count);
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();

	for (auto& thread : m_active_threads)
	{
		delete thread.second;
	}

	this->m_active_threads.clear();

	while (!this->m_inactive_threads.empty())
	{
		delete this->m_inactive_threads.front();
		this->m_inactive_threads.pop();
	}

	delete this->monitor;
}

void ThreadPool::startScheduler()
{
	this->m_is_running = true;
	this->start();
}

void ThreadPool::stopScheduler()	
{
	this->m_is_running = false;
	this->monitor->notifyComplete();
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->m_pending_actions.push(action);
}

void ThreadPool::run()
{
	while (this->m_is_running)
	{
		if (m_pending_actions.empty()) continue;

		this->monitor->tryEnter();

		PoolWorkerThread* worker_thread = this->m_inactive_threads.front();
		this->m_inactive_threads.pop();
		this->m_active_threads[worker_thread->getThreadID()] = worker_thread;

		worker_thread->assignTask(this->m_pending_actions.front());
		worker_thread->start();
		this->m_pending_actions.pop();
	}
}

void ThreadPool::onFinishedTask(int threadID)
{
	std::lock_guard<std::mutex> lock(this->workerMutex);

	if (this->m_active_threads[threadID] != nullptr)
	{
		auto worker = this->m_active_threads[threadID];
		this->m_active_threads.erase(threadID);
		this->m_inactive_threads.push(worker);
	}

	this->monitor->reportExit();
}
