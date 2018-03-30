#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using std::thread;
using std::mutex;
#define SIZE 500
mutex mtx;
void foo( int bar){




	for (int i = 1; i < SIZE; i+=bar ){	
		mtx.lock();	
		printf("thread bar : %d %d\n",bar,i);
		mtx.unlock();
	}
	return ;
}

void array_work(int base, int lim, int * array){
	for (int i = base; i < lim; ++i)
		array[i] = 5*array[i];
	return;
}


int main()
{	
	auto num_threads = std::thread::hardware_concurrency();
	thread** threads = new thread*[num_threads-1];
	for (int i = 0; i < num_threads-1; ++i){
		mtx.lock();
		threads[i] = new thread(foo, i+1);
		mtx.unlock();
	}

	for (int i = 0; i < num_threads-1; ++i){
		threads[i]->join();
		delete threads[i];
	}

	int LIM = 50;	
	srand(1);
	int* todo = new int[num_threads*125];
	int todo_size = num_threads*125;
	for (int i = 0; i < todo_size; ++i)
		todo[i] = rand()%LIM;
	
	for (int i = 0; i < todo_size; ++i){
		if (i % 20 == 0) printf("\n");
		printf("%d  ", todo[i]); 
	}	
	
	for (int i = 0; i < num_threads-1; ++i)
		threads[i] = new thread(array_work, i*125, i*125+125, todo);
	
	for (int i =0; i < num_threads-1; ++i){
		threads[i]->join();
		delete threads[i];
	}
	delete[] threads;

	for (int i = 0; i < todo_size; ++i){
		if (i % 20 == 0) printf("\n");
		printf("%d  ", todo[i]); 
	}	



	delete[] todo;


	return EXIT_SUCCESS;
}
