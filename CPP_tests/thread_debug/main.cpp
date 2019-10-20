#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex g_mutex;
bool keep_going = false;

void thread_worker(std::string x)
{
    while(keep_going)
    {
        std::lock_guard<std::mutex> lg(g_mutex);
        std::cout << "My id is " << x << std::endl;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    g_mutex.lock();

    std::thread th1(thread_worker, "first thread");
    std::thread th2(thread_worker, "second thread");

    keep_going = true;
    g_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    keep_going = false;

    th1.join();
    th2.join();


    return 0;
}