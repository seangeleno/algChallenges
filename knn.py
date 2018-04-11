import numpy as np
import matplotlib.pyplot as plt

def knn(upper_bounds=100, num_plots=100,num_klusters=5):
	points = [(np.random.randint(0,upper_bounds), np.random.randint(0,upper_bounds)) for i in range(num_plots)]
	klusters = [(np.random.randint(0,upper_bounds), np.random.randint(0,upper_bounds)) for i in range(num_klusters)]
	categorization = {}
	for i in range(num_klusters):
		categorization[i]=[]		
	for i in range(num_plots):
		lowest = upper_bounds*5
		lowest_idx = num_klusters+1
		for j in range(num_klusters):
			sum_ = ((klusters[j][0] - points[i][0])**2 + (klusters[j][1] - points[i][1])**2)
			sum_=np.sqrt(sum_)
			if sum_ < lowest:
				lowest_idx = j
				lowest = sum_
		categorization[lowest_idx].append(i)

	
	color_dict = {0 : 'lightcoral',1:'darkorange',2:'aqua',
		3:'palegreen',4:'khaki', 5:'b',6:'powderblue',7:'indigo',
		8:'teal',9:'maroon',10:'gold'}


	for i in range(11,num_klusters):
		if i % 3 == 0:
			color_dict[i] = ( i/num_klusters*.3333, i/num_klusters, i/num_klusters)
		elif i % 3 == 1:
			color_dict[i] = ( i/num_klusters, i/num_klusters*.3333, i/num_klusters)
		else:	
			color_dict[i] = ( i/num_klusters, i/num_klusters, i/num_klusters*.3333)
	for i in range(num_klusters):
		for el in categorization[i]:
			plt.scatter(points[el][0],points[el][1], color=color_dict[i])
	for i in range(num_klusters):
		plt.scatter(klusters[i][0],klusters[i][1], color=color_dict[i],s=100)
	
	plt.show()




def main():
	upper_bounds = int(input("enter upper bounds\t"))
	num_plots = int(input("enter the number of points!\t"))
	num_klusters = int(input("enter the number of klusters\t"))
	knn(upper_bounds=upper_bounds, num_plots=num_plots, num_klusters=num_klusters)

if __name__ == "__main__":
	main()
			
