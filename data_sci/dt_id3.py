import sklearn.datasets

import numpy as np


def main_id3():
	iris = datasets.load_iris()
	sepal_width  = iris[:,0]
	sepal_length = iris[:,1]
	petal_width  = iris[:,2]
	petal_length = iris[:,3]

class node:
	def __init__(self,dat):
		self.data = dat
		self.l = None
		self.r = None
	
class tree:
	def __init__(self):
		self.root = None

	def insert_t(self, curr, data):
		if not curr:
			return 0 
		if data < curr.data:
			if not curr.l:
				curr.l = node(data)
				return 1
			return self.insert_t(curr.l, data)+1
		elif not curr.r:
			curr.r = node(data)
			return 1
		return self.insert_t(curr.r, data)+1


	def insert(self, data):
		if not self.root:
			self.root = node(data)
			return 
		return self.insert_t(self.root, data)
	
	 
	def pre(self, curr):
		if not curr:
			return 
		print(curr.data)
		self.pre(curr.l)
		self.pre(curr.r)
		return

	def display_pre(self):
		self.pre(self.root)	 

	def in_(self, curr):
		if not curr:
			return
		self.in_(curr.l)
		print(curr.data)
		self.in_(curr.r)
	
	def display_in(self):
		self.in_(self.root)

def main():
	t = tree()

	#entropy  = -np.log(pmf)
	for i in range(50):
		data = np.random.randint(0,50)
		t.insert(data)
	
	t.display_pre()
	t.display_in()
	return

if __name__ == "__main__":
	main()
