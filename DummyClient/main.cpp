#include "pch.h"
#include <iostream>
#include <vector>
#include <thread>
#include "ClientNetwork.h"

using namespace std;
ClientNetwork _socket[100];

void ThreadRun(int i) {
    string s = "https://naver.com" + i;
    while (true) {
        _socket[i].Send(s, 0);
        _socket[i].Recv();
        cout << _socket[i].getNormalString() << endl;
    }
}

int main() {
    std::vector<thread> threads;
    for (int i = 0; i < 100; i++) {
        _socket[i].SetBind(L"127.0.0.1", 5005);
        _socket[i].Connect();
        threads.emplace_back(ThreadRun, i);
    }
    for (int i = 0; i < threads.size(); i++)
        threads[i].join();
}