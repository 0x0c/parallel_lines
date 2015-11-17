#include "parallel_lines.h"

namespace parallel_lines
{
	void scheduler::update() {
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

	void scheduler::push(std::function<void()> func) {
		std::unique_lock<std::mutex> lock(this->mutex);
		this->functions.push_back(func);
	}

	parallel_lines::scheduler* scheduler::shared_scheduler() {
		static parallel_lines::scheduler shared_instance;
		return &shared_instance;
	}
}