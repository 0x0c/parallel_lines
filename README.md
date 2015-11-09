# parallel_lines
Fuck'n simple dispatcher.

## Usage
```
// get shared instance
parallel_lines::scheduler *s = parallel_lines::shared_scheduler();

// push function
s->push([] {
  std::cout << "dispatch in thread " << std::this_thread::get_id() << std::endl;
});

// then call update()
s->update();
```
See more at `main.cpp`.
