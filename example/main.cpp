#include <thread>
#include "parallel_lines.h"

int main(int argc, char const *argv[])
{
	std::cout << "main thread " << std::this_thread::get_id() << std::endl;
	std::thread t = std::thread([] {
		std::cout << "dispatch0 in thread " << std::this_thread::get_id() << std::endl;
		parallel_lines::scheduler *s = parallel_lines::scheduler::shared_scheduler();
		s->push([] {
			std::cout << "dispatch1 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch2 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch3 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch4 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch5 in thread " << std::this_thread::get_id() << std::endl;
		});
	});
	std::thread t2 = std::thread([] {
		std::cout << "dispatch0 in thread " << std::this_thread::get_id() << std::endl;
		parallel_lines::scheduler *s = parallel_lines::scheduler::shared_scheduler();
		s->push([] {
			std::cout << "dispatch1 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch2 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch3 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch4 in thread " << std::this_thread::get_id() << std::endl;
		});
		s->push([] {
			std::cout << "dispatch5 in thread " << std::this_thread::get_id() << std::endl;
		});
	});
	parallel_lines::scheduler *s = parallel_lines::scheduler::shared_scheduler();
	t.join();
	t2.join();
	s->update();
	
	return 0;
}
