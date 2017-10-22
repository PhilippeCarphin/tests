#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
/*
 * This demonstrates usage of the C++ thread, mutex and lock_guard objects.
 */

// Global variable modified by the threads
int max = 0;

// Mutex used to protect and synchronize
std::mutex global_access;

/*******************************************************************************
 * Callback function that will be the thread.
*******************************************************************************/
void thread_callback()
{

	/*
	 * With this mutex, the value we get at the end is 33554431
	 * and without locking the mutex, I got 15, 7 and 13 depending on what the
	 * scheduler does..
	 */
#if 0
	std::lock_guard<std::mutex> lock(global_access);
#endif
	int thread_val = max;
	thread_val = 2 * max + 1;

	for(int j = std::rand() % 2000000; j; j--)
		;

	max = thread_val;

	std::cout << __FUNCTION__ << " max = " << max << std::endl;

}

/*******************************************************************************
 * We will create N_THREADS threads and wait for them to finish
*******************************************************************************/
const int N_THREADS = 25;
int main(void)
{
	std::srand(3);
	std::unique_ptr<std::thread> my_threads[N_THREADS];
	for( int i = 0; i < N_THREADS; i++){
		my_threads[i] = std::unique_ptr<std::thread>(new std::thread(thread_callback));
	}


	for( int i = 0; i < N_THREADS; i++){
		my_threads[i]->join();
	}

	std::cout << __FUNCTION__ << "END : max = " << max << std::endl;
}
		

