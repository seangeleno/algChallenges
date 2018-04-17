#include <cstdlib>
#include <cstdio>

#include <thread>
#include <mutex>
#include <future>
using std::thread;
using std::mutex;
using std::future;











class mat_cont{
private:
	int dim;
	double* mat;
public:
	mat_cont(void);
	mat_cont( const int);




	~mat_cont();
	void display(void)const;
	void set_dim( const int);
	void load_seq(void);
	double dot_t( mat_cont &, const int, const int);
	double dot( mat_cont &);
	double dot_r( mat_cont & );
	//friend double dot_t( mat_cont&, const mat_cont &, const int, const int);
	

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



