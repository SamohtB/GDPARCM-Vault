#include "ProgressTracker.h"

ProgressTracker* ProgressTracker::sharedInstance = nullptr;

ProgressTracker* ProgressTracker::getInstance()
{
    return sharedInstance;
}

void ProgressTracker::initialize(int total_scanlines)
{
    try
    {
        sharedInstance = new ProgressTracker();
    }
    catch (...)
    {
        std::cerr << "Progress Tracker not created successfully" << std::endl;
    }

    sharedInstance->m_total_rows = total_scanlines;
}

void ProgressTracker::destroy()
{
    delete sharedInstance;
}

void ProgressTracker::update()
{
    m_completed_rows.fetch_add(1);

    std::lock_guard<std::mutex> lock(m_mutex);
    float progress = (static_cast<float>(m_completed_rows.load()) / m_total_rows) * 100.0f;
    std::cout << "\rRendering Progress: " << progress << "%   " << std::flush;
}

void ProgressTracker::complete()
{
    std::cout << "\nRendering Complete!" << std::endl;
}
