#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>

namespace parallel_lines
{
	class scheduler
	{
	private:
		std::mutex mutex;
		std::vector<std::function<void()>> functions;
	public:
		scheduler() {};
		~scheduler() {};
		void update() {
			if (!this->functions.empty()) {
				this->mutex.lock();
				for (int i = 0; i < this->functions.size(); ++i) {
					this->functions[i]();
				}
				this->functions.clear();
				this->mutex.unlock();
			}
		}

		void push(std::function<void()> func) {
			this->mutex.lock();
			this->functions.push_back(func);
			this->mutex.unlock();
		}
	};

	static parallel_lines::scheduler *shared_instance = nullptr;

	static parallel_lines::scheduler* shared_scheduler() {
		if (shared_instance == nullptr) {
			shared_instance = new parallel_lines::scheduler();
		}
		return shared_instance;
	}
}
