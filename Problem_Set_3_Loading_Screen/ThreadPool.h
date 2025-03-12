#pragma once
#include <queue>
#include <unordered_map>
#include <mutex>
#include "IETThread.h"
#include "IFinishedTask.h"

class PoolWorkerThread;
class IWorkerAction;
class IFinishedTask;
class ThreadPoolMonitor;

class ThreadPool : public IETThread, public IFinishedTask
{
private:
	using String = std::string;
	using ThreadList = std::queue<PoolWorkerThread*>;
	using ActiveThreadMap = std::unordered_map<int, PoolWorkerThread*>;
	using ActionList = std::queue<IWorkerAction*>;

public:
	ThreadPool(String name, int worker_count);
	~ThreadPool();

	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);

private:
	void run() override;
	void onFinishedTask(int threadID) override;

	String m_name;
	bool m_is_running = false;
	int m_worker_count = 0;

	ActiveThreadMap m_active_threads;
	ThreadList m_inactive_threads;
	ActionList m_pending_actions;

	ThreadPoolMonitor* monitor = nullptr;
	std::mutex workerMutex;
	
};

