#ifndef MATRIX
#define MATRIX

#include <cstdlib>
#include <cstdio>

#include <thread>
#include <mutex>
#include <future>
using std::thread;
using std::mutex;
using std::future;










class virtual_mat{
};

class matrix : public virtual_mat{
private:
	int dimx;
	int dimy;
	double * mat;
public:
	matrix();
	matrix(const int x, const int y);
	matrix(const int dim);

	~matrix();

	void display() const;
	void set_dim(const int, const int);
	void load_seq(void);
	void load(const char*);
	class Proxy{
    public:
        Proxy(double*& m, int d, int row) : dimx(d), row(row), m(m) {  }
        double& operator[](const int index) {
            return m[this->row * dimx + index];
		}
		~Proxy(){
		}
    private:
        int row;
		double * m;
		int dimx;
	};
	
	Proxy operator[](const int& row){
		return Proxy(mat, dimx,row);
	}

};



class box : public virtual_mat{
private:
	int dim;
	double* mat;
public:
	box(void);
	box( const int);
	~box();
	void load(const char * );
	void xf(void);
	void display(void)const;
	void set_dim( const int);
	void load_seq(void);
	double dot_t( const box &, const int, const int) const;
	double dot( const box &)const;
	double dot_single_thread( const box & )const;
	double dot_vectorized( box & );
	void cross(const box &)const;
	void identity(void);
	void identity(const int);
	//friend double dot_t( box&, const box &, const int, const int);
	

	/*nested class for interfacing w double bracket retrieval calls. 
	exits scope and deletes*/
	class Proxy{
    public:
        Proxy(double*& m, int d, int row) : d(d), row(row), m(m) {  }
        double& operator[](const int index) {
            return m[this->row * d + index];
		}
		~Proxy(){
		}
    private:
        int row;
		double * m;
		int d;
    };

	Proxy operator[](const int& row){
		return Proxy(mat, dim,row);
	}
};


class vec : public virtual_mat{
private: 
	int dimx;
	double * mat;
public:
	vec();

	vec(const int);
	~vec();
	void display(void)const;



	void linspace(double, double, const int);
	double& operator[](const int i){
		return mat[i];
	}
};

#endif
