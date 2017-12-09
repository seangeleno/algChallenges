def fib(n):
    if n <= 1:
    if n not in dyndic.keys():
        dyndic[n] = 1
        return dyndic[n]
    return 1
    if n not in dyndic.keys():
        dyndic[n] = fib(n-1) + fib(n-2)
        return dyndic[n]
    return dyndic[n]
dyndic = dict()









def main():
	in_nth = input("enter the nth term you wish to retrieve from the fibonacci sequence\n")
	dyndic = dict()
	output = fib((int(in_nth)))
	print(output)

if __name__=="__main__":
	main()