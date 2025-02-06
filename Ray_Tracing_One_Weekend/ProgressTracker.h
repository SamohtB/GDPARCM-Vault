#pragma once
#include <iostream>
#include <mutex>
#include <atomic>

class ProgressTracker
{
public:
	static ProgressTracker* getInstance();
	static void initialize(int total_scanlines);
	static void destroy();

	void update();
	void complete();
	
private:
	ProgressTracker() = default;
	ProgressTracker(ProgressTracker const&) {}
	ProgressTracker& operator=(ProgressTracker const&) {}

	static ProgressTracker* sharedInstance;

	int m_total_rows = 0;
	std::atomic<int> m_completed_rows;
	std::mutex m_mutex;
};

