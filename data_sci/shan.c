#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define BUFFSIZE 4096

struct termios orig_termios;

void disable_raw_mode(){
	tcsetattr(STDIN_FILENO,TCSAFLUSH, &orig_termios);
}

void enable_raw_mode(){
	tcgetattr(STDIN_FILENO,&orig_termios);
	atexit(disable_raw_mode);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}



struct prob_pair{
	char * word;
	int cnt;
	float rel_freq;
	//after such and such many words have been added, we go through 
	//and update our table of 2 letter combinations, creating a lookup
	//of associated freqs for markov chain-produced diphone pairings
};

struct node{
	struct prob_pair pair;
	struct node * nxt;
};

struct map{
	struct node * table[2];
	int sz;
};

void display(struct map mp){
	for (int i = 0; i < mp.sz; ++i){
		struct node * curr = mp.table[i];
		while(curr){
			printf("(%s : %f)\n", curr->pair.word, \
				curr->pair.rel_freq);
			curr = curr->nxt;
		}
	}
	return;
}



int hash( const char * word){
	int sum = 0;
	int len = strlen(word);
	for (int i = 0; i < len; ++i)
		sum+=word[i];
	return sum;
}

void store_word(struct map* mp, char * word){
	int lookup = hash(word);
	struct node * curr = mp->table[lookup%mp->sz];
	if (!curr){
		curr = (struct node*)malloc(sizeof(struct node));
		curr->pair.word = (char*)malloc(sizeof(char)*(strlen(word)+1));
		strcpy(curr->pair.word, word);

		curr->pair.rel_freq = 0;
		curr->pair.cnt = 0;
		curr->nxt = 0;
		mp->table[lookup%mp->sz] = curr;
		return;
	}
	else if (!curr->nxt){
		if (strcmp(curr->pair.word, word) == 0){
			++curr->pair.cnt;
			return;
		}
		curr->nxt = (struct node*)malloc(sizeof(struct node));
		curr->nxt->pair.word = (char*)malloc(sizeof(char)*(strlen(word)+1));
		strcpy(curr->nxt->pair.word,word);
		curr->nxt->pair.rel_freq = 0;
		curr->nxt->nxt = 0;
		return;
	}

	while(curr->nxt){
		if(strcmp(curr->pair.word, word)==0){
			++curr->pair.cnt;
			return;
		}
		curr = curr->nxt;
	}
	curr->nxt = (struct node*)malloc(sizeof(struct node));
	curr->nxt->pair.word = (char*)malloc(sizeof(char)*(strlen(word)+1));
	strcpy(curr->nxt->pair.word,word);
	curr->nxt->pair.rel_freq = 0;
	curr->nxt->nxt = 0;
	return;


}

int word_split(char* buffer, struct map * mp, int * word_count, int * letter_count){
	int len = strlen(buffer);



	char * input_word;
	int start = 0;
	int cnt = 0;
	int flag = 0;
	for (int i = 0; i < len+1; ++i){
		if (buffer[i] == 32 || buffer[i] == 0){
			cnt = start;
			while(buffer[cnt]!=32 && buffer[cnt]!=0)
				++cnt;
			input_word = (char*)malloc(sizeof(char)*((cnt-start)+1));
			int cnt2 = start;	
			for ( int i = 0; i < (cnt-start); ++i){
				input_word[i] = buffer[cnt2];
				++cnt2;
			}
			input_word[(cnt-start)+1] = 0;
			(*letter_count)+=strlen(input_word);
			(*word_count) += 1;
			store_word(mp,input_word);
			if((*word_count)%5 == 0)
				++flag;
			memset(input_word, 0, sizeof(char)*strlen(input_word));
			free(input_word);
			start = i+1;
		}
	}
	memset(buffer,0,strlen(buffer));
	return flag;
}


void freq_count(const struct map * mp, const int letter_count, float* prog_letter_freq){
	char letters[27] = {'a','b','c','d','e','f','g','h','i','j','k',\
	'l', 'm', 'n', 'o','p','q','r','s','t','u','v','w','x','y','z', 0};
	int local_cnt = 0;
	int cnt = 0;
	for (int c = 0; c < 26; ++c){
		for (int i = 0; i < mp->sz; ++i){
			struct node * curr = mp->table[i];
			while(curr){
				char* wrd = curr->pair.word;
				local_cnt = 0;
				for (int j = 0; j < strlen(curr->pair.word); ++j){
					if (letters[c] == wrd[j])
						++local_cnt;
				}
				if (curr->pair.cnt > 0)
					local_cnt*=curr->pair.cnt;
				cnt+=local_cnt;
				curr = curr->nxt;

			}

		}


		
		printf("%d\n",cnt);	
		float fcnt = (float)cnt;
		prog_letter_freq[c] = fcnt/(float)letter_count;


		cnt = 0;
	}

	for (int i = 0; i < 26; ++i)
		printf("%c : %f\n", letters[i], prog_letter_freq[i]);
	return;
}


int main(){
	enable_raw_mode();
	float letters[26] = {8.167, 1.492, 2.682, 4.253, 12.702,
		2.228,2.015,6.094,6.966,0.153,.772,4.025,2.406,6.749,7.507,
		1.929,0.095,5.987,6.327,9.056,2.758,.978,2.360,0.150,1.974,
		0.074
		};
	struct map mp;
	mp.sz = 2;
	memset(mp.table, 0, sizeof(struct node*)*2);

	char c;
	char buf[BUFFSIZE];
	memset(buf,0,sizeof(char)*BUFFSIZE);
	int cnt = 0;
	int word_count = 0;
	int letter_count = 0;
	int flag = 0;
	int flg = 0;
	
	float prog_letter_freq[26];	
	memset(prog_letter_freq, 0, sizeof(float)*26);


	while(read(STDIN_FILENO,&c,1)==1 && c != '0'){
		if (c == '\n'){
			if (strcmp(buf, "display")==0)
				display(mp);
			else
				flag = word_split(buf,&mp,&word_count,&letter_count);
			memset(buf,0,sizeof(char)*strlen(buf)+1);
			cnt = 0;
			if (flag){
				freq_count(&mp, letter_count, prog_letter_freq);
				flag = 0;

			}
		}
		else if (c == 32){
			printf(" \n");
			buf[cnt] = c;
			++cnt;
		}
		else if (c >= '0' && c <='9')	
			continue;
		else if (c >= 68 && c <= 90)
			c+=32;	
		else if (c == 0x7f){
			printf("%c\n",c);
			buf[--cnt] = 0;
	}
		else{
			if (c-97 < 0 || c-97 > 25)
				continue;
			buf[cnt] = c;
			++cnt;
			printf("%c : %f\n", c, letters[c-97]);
		}
	}
	for (int i =0; i < 26; ++i)
		printf("%f\n",prog_letter_freq[i]);
	disable_raw_mode();


	return 0;
}
