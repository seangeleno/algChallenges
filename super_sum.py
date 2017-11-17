import argparse

def main( arg_number, arg_iterations ):
    num = int( arg_number ) # const
    iterations = int( arg_iterations )  #these typecasts allow for a "const" style use. Only once is it done, as opposed to 
    #the beginning of every loop
    string_num = str(num)  #same with this type casting operation.  Slight restructuring increases python runtime performace
    #significantly and substantially
    #print("string num ", string_num, "\niterations ", iterations)
    i = 1
    concat_to_pass_in = string_num
    while i < iterations:
        concat_to_pass_in += string_num
        i+=1
        

    num = int(concat_to_pass_in)
    print(sum_super_digit(num,0))




def sum_super_digit( in_int_num, count ):
    if( len(str(in_int_num)) == 1):
            return in_int_num
    
    concat_sum = str(in_int_num) # "const"
    output = 0
    len_str__in_int_num = len(str(in_int_num))  #I also like to include types in the name.  Easier to know properties this way
    for i in range(0,len_str__in_int_num):    
        output+=int(concat_sum[i])
    return sum_super_digit( output, count+1 )
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser() 
    parser.add_argument("arg_number", type = int, help = "this argument is the number that will be concatenated with itself, and then summed together")
    parser.add_argument("arg_iterations", type = int, help="this argument determines how many times the integer will be concatenated with itself")
    args = parser.parse_args()
    arg_number = args.arg_number
    arg_iterations = args.arg_iterations
    main( arg_number, arg_iterations )



