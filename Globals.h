#pragma once
class Globals
{
public:

	inline static uint64_t timeSinceEpochMillisec() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	inline static uint64_t last_update = 0;
	inline static uint64_t next_update_delta = 0;
};

