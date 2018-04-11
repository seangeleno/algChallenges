import numpy as np
import matplotlib.pyplot as plt

def knn(upper_bounds=100, num_plots=100,num_klusters=5,in_data=False,function="Euc"):
	dim = 2
	np.random.seed(1)
	if not in_data:
		points = [(np.random.randint(0,upper_bounds), np.random.randint(0,upper_bounds)) for i in range(num_plots)]
	else:
		points = []
		with open(input("enter the file\t"),"rb") as f:
			
			lines = f.read().split("\n")
			for line in line:
				points.append(list(map(float, lines.split(","))))
		dim = int(input("num_dimensions\t"))

	
	klusters = []
	for i in range(num_klusters):
		kluster_coor = []
		for j in range(dim):
			kluster_coor.append(np.random.randint(0,upper_bounds))
		klusters.append(kluster_coor)


	categorization = {}
	data_list = []

	for i in range(num_klusters):
		categorization[i]=[]		

	if function == "Euc":
		for i in range(num_plots):
			local_dist = []
			lowest = upper_bounds*5
			lowest_idx = num_klusters+1
		
			for j in range(num_klusters):
				sum_ = 0
				for k in range(dim):
					sum_ += (klusters[j][k] - points[i][k])**2
				sum_ = np.sqrt(sum_)
				local_dist.append((j,sum_))

				if sum_ < lowest:
					lowest_idx = j
					lowest = sum_

			categorization[lowest_idx].append(i)
			local_dist.insert(0,((points[i][0], points[i][1]),lowest_idx))
			data_list.append(local_dist)

	elif function == "Taxi":
		for i in range(num_plots):
			local_dist = []
			lowest = upper_bounds*5
			lowest_idx = num_klusters+1
		
			for j in range(num_klusters):
				sum_ = 0
				for k in range(dim):
					sum_ += abs(klusters[j][k] - points[i][k])
				local_dist.append((j,sum_))

				if sum_ < lowest:
					lowest_idx = j
					lowest = sum_

			categorization[lowest_idx].append(i)
			local_dist.insert(0,((points[i][0], points[i][1]),lowest_idx))
			data_list.append(local_dist)

	elif function == "Cos":
		for i in range(num_plots):
			local_dist = []
			greatest = 0
			greaest_idx = -1
		
			for j in range(num_klusters):
				dot_prod = np.asarray(klusters[j]).dot(np.asarray(points[i]))
				mag_k = 0
				mag_p = 0
				for k in range(dim):
					mag_k+=klusters[j][k]**2
					mag_p+=points[i][k]**2
				mag_k = np.sqrt(mag_k)
				mag_p = np.sqrt(mag_p)
				cos_sim = dot_prod/(mag_k * mag_p)
				local_dist.append((j,cos_sim))

				if cos_sim > greatest:
					greatest_idx = j
					greatest = cos_sim

			categorization[greatest_idx].append(i)
			local_dist.insert(0,((points[i][0], points[i][1]),greatest_idx))
			data_list.append(local_dist)


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
	
	for item in data_list:
		print(item)
	for item in categorization.keys():
		data_array = np.asarray(categorization[item])
		print("{}: loc(".format(item), end="")
		for i in range(dim):
			if i < dim - 1:
				print("{}, ".format(klusters[item][i]),end="")
			else:
				print("{}".format(klusters[item][i]),end="")
		print(")\tnum_els:  {}, avg: {}, std: {}".format(len(categorization[item]),
			np.mean(data_array), np.std(data_array)))
	plt.show()


def main():
	upper_bounds = int(input("enter upper bounds\t"))
	num_plots = int(input("enter the number of points!\t"))
	num_klusters = int(input("enter the number of klusters\t"))
	func=input("enter the function!\t")
	knn(upper_bounds=upper_bounds, num_plots=num_plots, num_klusters=num_klusters,function=func)

if __name__ == "__main__":
	main()
			
