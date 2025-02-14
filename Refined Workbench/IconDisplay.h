#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include <mutex>

class Icon;

class IconDisplay : public AGameObject, public IExecutionEvent
{
public:
	IconDisplay();
	~IconDisplay();
	void processInput(const std::optional<sf::Event> event) override;
	void update(sf::Time delta_time) override;

	void onFinishedExecution() override;

private:
	typedef std::vector<Icon*> IconList;
	typedef std::mutex Mutex;
	IconList m_icon_list;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const StreamingType m_streaming_type = SINGLE_STREAM;

	const float STREAMING_LOAD_DELAY = 25.f;
	float m_ticks = 0.0f;
	bool m_started_streaming = false;

	int m_column_grid = 0; 
	int m_row_grid = 0;
	int m_num_displayed = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	Mutex guard;
	void spawnObject();
};


