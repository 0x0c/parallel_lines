#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>

namespace parallel_lines
{
class scheduler
{
private:
	std::mutex mutex;
	std::vector<std::function<void()>> functions;
	std::condition_variable cond;

public:
	scheduler(){};
	~scheduler(){};
	void update()
	{
		if (!this->functions.empty()) {
			std::unique_lock<std::mutex> lock(this->mutex);
			for (int i = 0; i < this->functions.size(); ++i) {
				this->functions[i]();
			}
			this->functions.clear();
			lock.unlock();
			this->cond.notify_one();
		}
	}
	void push(std::function<void()> func)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		this->functions.push_back(func);
	}

	static parallel_lines::scheduler *shared_scheduler()
	{
		static parallel_lines::scheduler shared_instance;
		return &shared_instance;
	}
};
}