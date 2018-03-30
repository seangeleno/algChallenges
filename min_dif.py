import argparse

def preproc(str1,str2):	
	print(str1, str2)
	if len(str1) == len(str2):
		out = ret_sum(str1,str2)
	elif len(str1) < len(str2):
		str1a = ((len(str2)-len(str1)) * " ") + str1
		str1b = str1 + ((len(str2)-len(str1)) * " ")
		out1 = ret_sum(str1a, str2)
		out2 = ret_sum(str1b, str1)
		if out1 < out2: out = out1
		else: out = out2
	elif len (str2) < len(str1):
		str2a = ((len(str1)-len(str2)) * " ") + str2
		str2b = str2+ (" "*(len(str1)-len(str2))) 
		out1 = ret_sum(str1,str2a)
		out2 = ret_sum(str1,str2b)
		if out1 < out2:
			out = out1
		else: out = out2
	return out
def ret_sum(str1,str2):
	sum_ = 0.0
	for m in zip(str1,str2):
		if ord(m[0])!=ord(m[1]):
			if m[0] == " ":
				sum_+=ord(m[1])
			elif m[1] == " ":
				sum_+=ord(m[0])
			else:
				sum_+=(ord(m[0])+ord(m[1]))
	return sum_
def main():
	str1 = input("enter string one\n")
	str2 = input("enter string 2\n")
	print(preproc(str1,str2))

def sol2(str1,str2):
	min1 = 0
	min2 = 0
	diff = list()
	str1l = list(str1)
	str2l = list(str2)
	for i in range(str1l):
		if str1l[i] != str2l[i]:
			a = ""
			b = ""
			while 
if __name__ == "__main__":
	main()