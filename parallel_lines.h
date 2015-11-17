#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace parallel_lines
{
	class scheduler
	{
	private:
		std::mutex mutex;
		std::vector<std::function<void()>> functions;
		std::condition_variable	cond;
	public:
		scheduler() {};
		~scheduler() {};
		void update();
		void push(std::function<void()> func);

		static parallel_lines::scheduler* shared_scheduler();
	};
}