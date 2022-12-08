#pragma once

class ThreadPool {
public:
	ThreadPool(int num_threads_);
	~ThreadPool();

	template<class T, class... Args>
	future<typename std::result_of<T(Args...)>::type> enqueue(T&& t, Args&&... args);

private:
	void WorkerThread();

private:
	vector<std::thread> workers;
	queue<std::function<void()>> tasks;

	size_t num_threads_;
	condition_variable condition;
	mutex m;
	bool stop;
};