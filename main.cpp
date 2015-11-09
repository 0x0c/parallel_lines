#include <thread>
#include "parallel_lines.h"

int main(int argc, char const *argv[])
{
	std::cout << "main thread " << std::this_thread::get_id() << std::endl;
	std::thread t = std::thread([] {
		std::cout << "dispatch in thread " << std::this_thread::get_id() << std::endl;
		parallel_lines::scheduler *s = parallel_lines::shared_scheduler();
		s->push([] {
			std::cout << "dispatch in thread " << std::this_thread::get_id() << std::endl;
		});
	});
	t.join();
	parallel_lines::scheduler *s = parallel_lines::shared_scheduler();
	s->update();

	return 0;
}
