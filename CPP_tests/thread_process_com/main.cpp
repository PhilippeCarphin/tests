#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <chrono>

std::mutex g_display_mutex;
std::mutex g_wait_mutex;

int g_variable_int;

void thread_safe_print(std::string msg){
    // The creation of this object will acquire the mutex
    // This is RAII
    std::lock_guard<std::mutex> lock(g_display_mutex);
    std::cout << msg << std::endl;
    // destruction of the object =lock= will release the mutex
}

fonction_a(){
    std::cout << g_variable_int << std::endl;
}

fonction_b(){
    std::cout << g_variable_int << std::endl;
}

void thread_worker(){

    while(true) {
        g_wait_mutex.lock();

        std::thread::id this_id = std::this_thread::get_id();

        std::ostringstream oss("This thread has id ");
        oss << this_id << " And g_variable_int = " << g_variable_int;

        thread_safe_print(oss.str());
    }
}

int main() {

    // Print thread id of main thread
    std::thread::id main_id = std::this_thread::get_id();
    std::ostringstream oss("Main thread ID thread has id ");
    oss << main_id << " And g_variable_int = " << g_variable_int;
    thread_safe_print(oss.str());

    // Set global variable to 0
    g_variable_int = 0;

    // Create thread using C++ threads
    std::thread my_thread(thread_worker);


    // This thread just waits until we tell it to go, it will go once and wait again
    g_wait_mutex.unlock();

    // Give the thread time to do it's thing befor we change g_variable_int
    std::chrono::duration<int, std::milli> pause_time(100);
    std::this_thread::sleep_for(pause_time);

    // Change g_variable int and tell the thread to go
    g_variable_int = 1;
    g_wait_mutex.unlock();

    // EXERCICE: Comment dire au thread d'arrêter?
    // Il faut modifier le programme pour utiliser un des moyens de communication pour qu'on puisse faire quelque chose comme
    // thread_keeps_going = false;


    // Wait for threads to finish lest we get errors at the end of the program
    my_thread.join();


    return 0;
}