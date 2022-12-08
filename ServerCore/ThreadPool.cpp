#include "pch.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_threads_) : num_threads_(num_threads_), stop(false) {
	workers.reserve(num_threads_);
	for (int i = 0; i < num_threads_; i++) {
		workers.emplace_back([this]() { this->WorkerThread(); });
	}
}

ThreadPool::~ThreadPool() {
	while (!tasks.empty())
		tasks.pop();
	stop = true;
	condition.notify_all();
	for (int i = 0; i < num_threads_; i++)
		workers[i].join();
}

void ThreadPool::WorkerThread()
{
	while (true) {
		std::unique_lock<std::mutex> lk(this->m);
		this->condition.wait(lk, [this]() {return  this->stop || !this->tasks.empty(); });
		if (this->stop && this->tasks.empty())
			return;

		function<void()> task = std::move(tasks.front());
		tasks.pop();
		lk.unlock();
		task();
	}
}

template<class T, class ...Args>
inline future<typename std::result_of<T(Args...)>::type> ThreadPool::enqueue(T&& t, Args && ...args)
{
	if (stop) {
		throw std::runtime_error("ThreadPool ��� ������");
	}

	using return_type = typename std::result_of<T(Args...)>::type;

	auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<T>(t), std::forward<Args>(args)...));
	std::future<return_type> task_result = task->get_future();
	{
		std::lock_guard<std::mutex> lock(m);
		tasks.push([task]() { (*task)(); });
	}
	condition.notify_one();

	return task_result;
}