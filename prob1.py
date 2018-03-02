"""Lyle Hubbard Dec 9, 2017
function identifying most common character to appear in a word, out of all 
words in the sentence passed in. 
PARAMS: sentence - string
RETURN: tuple of max character(string), frequency (int), 
		word char found in (string)"""
import argparse

def prob1( sentence ):
	words = list()  #iterable container of per word character counts and parent word
	split_words = sentence.split(" ") 

	for el in split_words:
		lower_el = el.lower()	#create an all lower case version for consistency
		local_dict = dict() #map of letter to frequency per word
		for i in range( len(lower_el) ):
			if lower_el[i] not in local_dict.keys() and lower_el[i].isalpha(): #characters must only be letters
				local_dict[ lower_el[i] ] = 1
			elif lower_el[i].isalpha():
				local_dict[ lower_el[i] ]+=1

		words.append( (local_dict,el) ) # a tuple of the mapping and the word

	max_char = ""
	max_count = 0
	word_max_char = "" #identifying attributes of the maximum occurence

	for word in words:
		mapping = word[0] #word[0] is the dictionary
		for char_ in mapping.keys(): 
			if mapping[char_] > max_count:
				max_count = mapping[char_]
				max_char = char_
				word_max_char = word[1] #word that max_count resides in

	return (max_char, max_count,word_max_char) #return container of all attributes of max occurence

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("file_path",type=str,help="a path to the file")
	args = parser.parse_args()
	file_path = args.file_path

	with open(file_path,"r") as document:
		doc_in = document.read()

	ret_val = prob1(doc_in)
	print("the letter {} is the most frequent in the word {} appearing {} times".format(ret_val[0], ret_val[2], ret_val[1]))