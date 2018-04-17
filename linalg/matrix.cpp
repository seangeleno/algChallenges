#include "matrix.hpp"
#include <functional>
#include <mutex>
#include <math.h>
#include <unistd.h>

using std::async;

mat_cont::mat_cont(void) : dim(0), mat(NULL){}

mat_cont::mat_cont( const int dim) : dim(dim), mat(new double[dim*dim]){}
	//IMPORTANT: NOTE HOW IT IS ONE BLOCK OF MEMORY


void mat_cont::display(void) const{
	printf("[");
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			printf("[%lf]", mat[i * dim + j]); // row = i * dim 
				//(represents x memspaces into mem block.  + j gives the final offset
			if ( j != dim - 1)
				printf(", ");
		}
		printf("]\n");			
		if (i != dim-1)
			printf("[");
	}
}



mat_cont::~mat_cont(){
	delete[] mat;
}

void mat_cont::load_seq(void){ //used for initializing consistent data for debug
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			mat[i * dim + j] = i * dim + j;
		}
	}
}
double mat_cont::dot_r( mat_cont & other ){
	double sum = 0;
	int lim = dim*dim;
	for (int i = 0; i < lim; ++i)
		sum += ( this->mat[i] + other.mat[i] );
	return sum;
}



std::mutex mtx;

double mat_cont::dot_t( const mat_cont & other, const int offset,  \
	const int upper_lim) const

{
	double local_sum = 0;	
	for (int i = offset; i < upper_lim+offset; ++i){
	//maybe increment by 16 per mutex lock and release? look up cost of atomics
		mtx.lock(); //thought atomizing access might help? apparently not
		local_sum+=(this->mat[i] + other.mat[i]);
		mtx.unlock();
	}
	return local_sum;
}

double mat_cont::dot( const mat_cont & other)const {
	//future will catch a returned value from an aysnchronous thread. Threads
	//are split between 4 cores and wrapped with mutex. 
	if (other.dim != this->dim)
		return 0.0;	//wrap w proper exception handling obv	
	future<double> threads[3];
	int part = (int)round((dim * dim) / 4.0); //partitions set every "part" increment
	
	double sum = 0;

	for (int i = 1; i < 4; ++i){
		threads[i-1] = async (std::launch::async,[this,&other,i,part]() { //this is a lambda function; 
							return this->dot_t(other, part*i, (i+1)*part);  //used for funny lil situations like this
						});
	}

	for(int i = 0; i < part; ++i){
		mtx.lock();
		sum+=(this->mat[i] + other.mat[i]); //run computation in main thread as well
		mtx.unlock();
	}


	for(int i = 1; i < 3; ++i)
		sum+=threads[i].get(); //this retrieves the value held by the future object
	return sum;
}





void mat_cont::set_dim(const int dim){
	this->dim = dim;
	if (mat)
		delete[] mat;
	mat = new double[dim*dim];
}
