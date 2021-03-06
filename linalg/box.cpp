#include "matrix.hpp"

#include <functional>
#include <mutex>
#include <cmath>
#include <unistd.h>

using std::async;

box::box(void) : dim(0), mat(NULL){}

box::box( const int dim) : dim(dim), mat(new double[dim*dim]){}
	//IMPORTANT: NOTE HOW IT IS ONE BLOCK OF MEMORY


void box::display(void) const{
	printf("[");
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			printf("[%.2f]", mat[i * dim + j]); // row = i * dim 

				//(represents x memspaces into mem block.  + j gives the final offset
			if ( j != dim - 1)
				printf(", ");
		}
		printf("]\n");			
		if (i != dim-1)
			printf("[");
	}
	return;
}

box::~box(){
	delete[] mat;
}

void box::load_seq(void){ //used for initializing consistent data for debug
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			mat[i * dim + j] = i * dim + j;
		}
	}
}



double box::dot_single_thread(const box & other )const{
	double sum = 0;
	int lim = dim*dim;

	for (int i = 0; i < lim; ++i)
		sum += ( this->mat[i] + other.mat[i] );
	return sum;
}



std::mutex mtx;

double box::dot_t( const box & other, const int offset,  \
	const int upper_lim) const

{
	double local_sum = 0;	
	for (int i = offset; i < upper_lim; ++i){
	//maybe increment by 16 per mutex lock and release? look up cost of atomics
		mtx.lock(); //thought atomizing access might help? apparently not
		local_sum+=(this->mat[i] + other.mat[i]);
		mtx.unlock();
	}
	return local_sum;
}



/*double box::dot_vectorized( box & other){
	if (this->dim != other.dim)
		return 0;
	typedef double v4si __attribute__ ((vector_size (64)));

	double sum = 0;	
	int remainder = 0;
	if ((part * 4) < (dim*dim))
		remainder = (dim*dim) - (part*4);
	double sum = 0;
	v4si a = this->mat[	

	for (int i = 0; i < dim; ++i){
	}
	return sum;
}


*/

double box::dot( const box & other)const {
	//future will catch a returned value from an aysnchronous thread. Threads
	//are split between 4 cores and wrapped with mutex. 
	if (other.dim != this->dim)
		return 0.0;	//wrap w proper exception handling obv	
	future<double> threads[3];
	int part = (int)round((dim * dim) / 4.0); //partitions set every "part" increment

	int remainder = 0;
	if ((part * 4) < (dim*dim))
		remainder = (dim*dim) - (part*4);
	double sum = 0;

	for (int i = 1; i < 4; ++i){
		if (( i == 4-1) && (remainder)){
			threads[i-1] = async (std::launch::async,[this,&other,i,part,remainder](){
							return this->dot_t(other,part*i, ((i+1)*part +remainder));
						});
		} 
		else {
			threads[i-1] = async (std::launch::async,[this,&other,i,part]() { //this is a lambda function; 
							return this->dot_t(other, part*i, (i+1)*part);  
						});
			}

	}
	for(int i = 0; i < part; ++i){
		mtx.lock();
		sum+=(this->mat[i] + other.mat[i]); //run computation in main thread as well
		mtx.unlock();
	}

	for(int i = 0; i < 3; ++i)
		sum+=threads[i].get(); //this retrieves the value held by the future object
	return sum;
}


void box::cross(const box & other)const{
}
void box::identity(void){
	printf("%d\n",dim);
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			if (i!=j)
				mat[i * dim + j] = 0.0;
			else
				mat[i * dim + j] = 1.0;
		}
	}
	return;
}


void box::identity(const int in_dim){
	if (mat)
		delete[] mat;
	this->dim = in_dim;
	mat = new double[this->dim];
	identity();
}

void box::xf(void){
	for (int i = 0; i < dim; ++i){
		for(int j = 0; j < dim; ++j){
			if (j < i)
				mat[i *dim + j] = dim+j-i;
			else
				mat[i*dim + j] = j-i;
		}
	}
	display();
	printf("\n\n");
}














void box::load(const char * name){
	FILE * f;
	if ((f = fopen(name,"r"))==NULL)
		return;
	double num_buf[4096];
	int num_count = 0;
	int len_per_line = 0;
	int iter = 0;

	char buffer[4096]; 
	char c;
	int cnt = 0;

	double * matrix;

	while((c = fgetc(f))&& !feof(f)){
		if (c != ',' && c!= '\n'){
			buffer[cnt] = c;
			++cnt;
		}
		else if (c!='\n'){
			num_buf[num_count] = atof(buffer);
			++num_count;

			memset(buffer,0,strlen(buffer));
			cnt = 0;
		}
		else{
			if (len_per_line == 0){
				len_per_line = num_count;
				matrix = new double[len_per_line*len_per_line];
				for (int i = 0; i < len_per_line; ++i)
					matrix[i] = num_buf[i];
				memset(num_buf,0.0,sizeof(double)*len_per_line);
				
				}	
			else{
				for (int i = 0; i < len_per_line; ++i)
					matrix[iter*len_per_line + i] = num_buf[i];
			}
			memset(num_buf,0.0,sizeof(double)*len_per_line);
			num_count = 0;
			++iter;
		}
	}
	fclose(f);

	this->dim = len_per_line;
	this->mat = matrix;
	return;
}



void box::set_dim(const int dim){
	this->dim = dim;
	if (mat)
		delete[] mat;
	mat = new double[dim*dim];
}
