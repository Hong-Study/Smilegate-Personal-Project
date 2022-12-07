#pragma once

class ThreadPool {
public:
	ThreadPool(int num_threads_);
	~ThreadPool();

	//result_of �� ���� Ÿ���� �����ִ� �Լ� //�� C++17, 20������ ��� X
	//invoke_result�� ��ü��.
	//���� ���� ����
	//auto enqueue(T&& t, Args&&... args) -> std::future<typename std::result_of<T>::type> {
	template<class T, class... Args>
	future<typename std::result_of<T>::type> enqueue(T&& t, Args&&... args);
	void WorkerThread();

private:
	vector<std::thread> workers;
	queue<std::function<void()>> tasks;

	size_t num_threads_;
	condition_variable condition;
	mutex m;
	bool stop;
};