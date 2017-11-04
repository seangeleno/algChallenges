#include "challenge.h"
#include "challenge_wrappers.h"
int main(int argc, char ** argv){
	printf("input the seed first\n"); 
	int ret_val = main_script();
	if (!ret_val){
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
