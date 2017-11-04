import argparse

def main( arg_number, arg_iterations ):
    num = int( arg_number )
    iterations = int( arg_iterations )
    string_num = str(num)
    #print("string num ", string_num, "\niterations ", iterations)
    i = 1
    concat_to_pass_in = string_num
    while i < iterations:
        concat_to_pass_in += string_num
        i+=1
        

    num = int(concat_to_pass_in)
    def sum_super_digit( in_int_num, count ):
        if( len(str(in_int_num)) == 1):
            return in_int_num
    
        concat_sum = str(in_int_num)
        output = 0
        for i in range(0,len(str(in_int_num))):    
            output+=int(concat_sum[i])
        return sum_super_digit( output, count+1 )
    print(sum_super_digit(num,0))
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser() 
    parser.add_argument("arg_number", type = int, help = "this argument is the number that will be concatenated with itself, and then summed together")
    parser.add_argument("arg_iterations", type = int, help="this argument determines how many times the integer will be concatenated with itself")
    args = parser.parse_args()
    arg_number = args.arg_number
    arg_iterations = args.arg_iterations
    main( arg_number, arg_iterations )



