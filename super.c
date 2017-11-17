#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*May be refactored with <stdint.h> primative definitions*/
int super_sum(int * arr, int size){ 
    if ( size == 1)
        return arr[0];
    
    long long int local_sum = 0; 
    for ( int i = 0; i < size; i++)
        local_sum +=  arr[i];

    int thru_size = log10(local_sum) + 1;
    int * thru_arr = (int*)malloc((thru_size)*sizeof(int));

    
    
    for ( int i = thru_size - 1; i >= 0; i--){
        thru_arr[i] = local_sum%10; //purposefully avoiding atoi for algorithmic fun!
        local_sum /= 10;
    }
  
    int return_item = super_sum( thru_arr, thru_size );
    free( thru_arr );
    return return_item;
}



int main() {
    int num_concat, times_to_concat;
    char * str_con, * original_num;
    char buffer[10000];
    scanf("%[^\n]s",buffer);
    
    scanf("%d",&times_to_concat);
    
    str_con = (char*)malloc((strlen(buffer)*times_to_concat + 1)*sizeof(char)); //array len of stringified number
    original_num = (char*)malloc((strlen(buffer) + 1)*sizeof(char)); //maintain original number
    strcpy(original_num, buffer); 
    
    for( int i = 0; i < times_to_concat; i++) //concatenation loop
        strcat(str_con, original_num);  
    
    int length = strlen(str_con);
    int * in_nums = (int*)malloc((length) * sizeof(int)); 

    for (int i = 0; i < length ; i++)
            in_nums[ i ] = (int) str_con[i] -48; 
    

    int output = super_sum( in_nums, length );
    free(str_con);
    free(original_num);
    free( in_nums );
    
    printf("%d",output);
    
    return 0;
}
