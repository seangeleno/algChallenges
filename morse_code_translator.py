"""Saw some guy's pet website dedicated to morse code translation
and widgets for sound, light, and vibration.  I thought it was pretty cool, 
since some friends and I were pretending our morse messages coulnd't be
read by the ZUCC, so I got some good practice in writing morse from memory.
But sometimes that is tedious, so I figured out a better solution instead.
Should work in all cases, added pound symbols for cases of unrecognized
characters.  Enjoy!

Lyle Hubbard III 03/28/2017
"""



def main():
	morse_lookup = {
		"A" : ".-", 
		"B" : "-...", 
		"C" : "-.-.",
		"D" : "-..",
		"E" : ".",
		"F" : "..-.",
		"G" : "--.",
		"H" : "....",
		"I" : "..",
		"J" : ".---",
		"K" : "-.-",
		"L" : ".-..",
		"M" : "--",
		"N" : "-.",
		"O" : "---",
		"P" : ".--.",
		"Q" : "--.-",
		"R" : ".-.",
		"S" : "...",
		"T" : "-",
		"U" : "..-",
		"V" : "...-",
		"W" : ".--",
		"X" : "-..-",
		"Y" : "-.--",
		"Z" : "--..",

		"0" : "-----",
		"1" : ".----",
		"2" : "..---",
		"3" : "...--",
		"4" : "....-",
		"5" : ".....",
		"6" : "-....",
		"7" : "--...",
		"8" : "---..",
		"9" : "----.",

		"." : ".-.-.-",
		"," : "--..--",
		":" : "---...",
		"?" : "..--..",
		"'" : ".----.",
		" " : " / "
		}

	morse_to_char = {
		".-"    : "A",
		"-..."  : "B",
		"-.-."  : "C",
		"-.."   : "D",
		"."     : "E", 
		"..-."  : "F",
		"--."   : "G",
		"...."  : "H",
		".."    : "I",
		".---"  : "J",
		"-.-"   : "K",
		".-.."  : "L",
		"--"    : "M",
		"-."    : "N",
		"---"   : "O",
		".--."  : "P",
		"--.-"  : "Q",
		".-."   : "R",
		"..."   : "S",
		"-"     : "T",
		"..-"   : "U",
		"...-"  : "V",
		".--"   : "W",
		"-..-"  : "X",
		"-.--"  : "Y",
		"--.."  : "Z",

		"-----" : "0",
		".----" : "1",
		"..---" : "2",
		"...--" : "3",
		"....-" : "4",
		"....." : "5",
		"-...." : "6",
		"--..." : "7",
		"---.." : "8",
		"----." : "9",

		".-.-.-" : ".",
		"..--.." : "?",
		"--..--" : ",",
		"---..." : ":",
		".----." : "'",
		"/"      : " ",
		" "      : ""
	}
	while True:
		char_to_morse_flag = False;
		in_string = input("enter the item to convert to morse\n")
		if in_string == "q":
			break;
		out_string = ""

		for el in in_string:
			if el.isalnum():
				char_to_morse_flag = True

		if char_to_morse_flag:	
			in_string = in_string.upper()	
			for el in in_string:

				try:
					out_string+=" " + morse_lookup[el]
				except:
					out_string+=" "+"#"
		else:
			el_list = in_string.split(" ")
			for el in el_list:
				try:
					out_string+=morse_to_char[el]
				except:
					out_string+="#"



		print(out_string)
	return

if __name__ == "__main__":
	main()
