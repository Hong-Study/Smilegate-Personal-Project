#pragma once

class ThreadPool {
public:
	ThreadPool(int num_threads_);
	~ThreadPool();

	//result_of 는 리턴 타입을 정해주는 함수 //단 C++17, 20에서는 사용 X
	//invoke_result로 대체됨.
	//후위 전달 형태
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