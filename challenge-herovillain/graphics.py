import matplotlib.pyplot as plt
import argparse
import time
def visual( input_, dimensions, skipByHunds):
	for i in xrange( input_ ):
		j = 0
		if skipByHunds == 1:
			fl = open("player-data"+str(100*i)+".txt","r")
		else:
			fl = open("player-data"+str(i)+".txt","r")
		X = []
		y = []
		plt.axis([-dimensions/2,dimensions/2,-dimensions/2,dimensions/2])
		plt.autoscale(enable=False)
		for element in fl.read().split("\r\n"):
			element = element.split(",")
			try:
				plt.scatter(element[1],element[2],marker="${}$".format(j))
				plt.title(str(i))
				j+=1
			except: pass
		plt.show()
		plt.close()
		fl.close()
if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("dimensions",type=int)
	parser.add_argument("numberIt",type=int)
	parser.add_argument("skip", type=int)
	args = parser.parse_args()
	dimensions = args.dimensions
	iterations = args.numberIt
	skipByHunds = args.skip
	visual( iterations, dimensions, skipByHunds)
