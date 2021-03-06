#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
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


typedef struct{
	struct prob_pair pair;
	struct t_node* child[2];
}t_node;

struct ord_table{
	t_node* root;
};	




struct map{
	struct node * table[501];
	int sz;
};

int insert_t(struct ord_table *, char *);
int insert(t_node**, char*);
void display_t(struct ord_table);
void disp_in(const t_node*);

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




int insert_t(struct ord_table * t, char * d){
	return insert(&t->root, d);
}

int insert( t_node ** curr, char * d){
	if (!(*curr)){
		(*curr) = (t_node *) malloc(sizeof(t_node));
		(*curr)->pair.word = (char*)malloc(sizeof(char)*(strlen(d)+1));
		strcpy((*curr)->pair.word, d);
		(*curr)->pair.cnt = 1;
		memset((*curr)->child,0,sizeof(t_node*)*2);
		return 1;
	}
	if (strcmp((*curr)->pair.word,d)==0){
		++(*curr)->pair.cnt;
		return 1;
	}
	else if (strcmp(d,(*curr)->pair.word)<0)
		return insert(&(*curr)->child[0],d);
	else return insert(&(*curr)->child[1],d);
}

void display_t(struct ord_table t){
	disp_in(t.root);
}

void disp_in( const t_node* curr){
	if(!curr)
		return;
	disp_in(curr->child[0]);
	printf("%s %f %d\n",curr->pair.word, curr->pair.rel_freq, curr->pair.cnt);
	disp_in(curr->child[1]);
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
		curr->pair.cnt = 1;
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
			memset(input_word, 0, sizeof(char)*strlen(input_word));//unique mem locs but still getting lngering mem?
			free(input_word); 
			start = i+1; //use to locate offset from beginning of word
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



int phoneme_gen(struct map * mp, struct ord_table * t, const int phoneme_len){
	char * phoneme;
	clock_t t1,t2;
	t1 = clock();
	int sig = 0;
	phoneme = (char*)malloc(sizeof(char)*(phoneme_len+1));
	for (int i = 0; i < mp->sz; ++i){
		struct node * curr = mp->table[i];
		while(curr){
			int c = 0;
			//int cnt = 0;
			while(curr->pair.word[c] != 0)	{
				for (int i = 0; i < phoneme_len; ++i){
					phoneme[i] = curr->pair.word[c];
			//		if (curr->pair.word[c] == 0)
			//			++cnt;
					++c;
				}
			//	if (cnt)
			//		break;
				sig += insert_t(t, phoneme);
				memset(phoneme,0,sizeof(char)*3);
				c-=(phoneme_len-1);
			}
			curr=curr->nxt;
		}
	}
	free(phoneme);
	t2 = clock();
	printf("elapsed %lf\n",(double)((t2-t1)/CLOCKS_PER_SEC));
	return sig;
}
int main(){
	enable_raw_mode();
	float letters[26] = {8.167, 1.492, 2.682, 4.253, 12.702,
		2.228,2.015,6.094,6.966,0.153,.772,4.025,2.406,6.749,7.507,
		1.929,0.095,5.987,6.327,9.056,2.758,.978,2.360,0.150,1.974,
		0.074
		};
	struct map mp;
	mp.sz = 501;
	memset(mp.table, 0, sizeof(struct node*)*mp.sz);

	char c;
	char buf[BUFFSIZE];
	memset(buf,0,sizeof(char)*BUFFSIZE);
	int cnt = 0;
	int word_count = 0;
	int letter_count = 0;
	int flag = 0;
	FILE * fr;
	int flg = 0;
	struct ord_table t;
	t.root = NULL;
	if ((fr=fopen("wordstore.csv","r"))!=NULL){
		while((c = fgetc(fr))&& c !='0' && !feof(fr)){ //handles and terminates file read stream
			if (c==','){
				word_split(buf,&mp,&word_count,&letter_count);//load words into lookup as they are streamd
				memset(buf,0,sizeof(char)*strlen(buf));
				cnt = 0;
			}
			else{
				if (c>=68 && c <= 90)
					c+=32;
				if (c < 97 || c > 97+25)
					continue;
				buf[cnt] = c;
				++cnt;
			}
		}
		fclose(fr);
	}
	if ((fr=fopen("text.txt","r"))!=NULL){

		while((c = fgetc(fr))&& c !='0' && !feof(fr))
		{ //handles and terminates file read stream
			if (c=='\n'){
				word_split(buf,&mp,&word_count,&letter_count);//load words into lookup as they are streamd
				memset(buf,0,sizeof(char)*strlen(buf));
				cnt = 0;
			}
			else{
				if (c>=68 && c <= 90)
					c+=32;
				if ((c < 97 || c > 97+25) && c!=32 && c!='\n')
					continue;
				buf[cnt] = c;
				++cnt;
			}
		}
		fclose(fr);
	}


	
	float prog_letter_freq[26];	
	memset(prog_letter_freq, 0, sizeof(float)*26);
	/*int len = 1;
	while (phoneme_gen(&mp, &t, len) != 0)
		++len;
	*/
	for (int i =1; i < 6; ++i)
		phoneme_gen(&mp, &t, i);



	while(read(STDIN_FILENO, &c, 1)&& c !='0'){
		if (c == '\n'){
		//handle display call (should link to stats overview)
			if (strcmp(buf, "display")==0)
				display(mp);
			else if (strcmp(buf,"tdisp")==0)
				display_t(t);	
			else if (strcmp(buf,"freq")==0)
				freq_count(&mp, letter_count, prog_letter_freq);
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
			//separator for words as they are fed into parser. just around to make it cleaner
			printf(" \n");
			buf[cnt] = c;
			++cnt;
			}
		else if (c >= '0' && c <='9')	
			//handle numerical values
			continue;

		else if (c == 0x7f){
			//backspace handling on inputs
			printf("%c\n",c);
			buf[--cnt] = 0;
		}

		else{
			if (c >= 68 && c <= 90){
				//if captial, shift to lowercase
				c+=32;
				printf("%c\n",c);
			}

			else if (c-97 < 0 || c -97 > 25)
				//if it exceeds the bounds of our lookup, see ya later
				continue;

			//else we add the ltter to our buffer and display relative freq
			buf[cnt] = c;
			++cnt;
			printf("%c : %f\n", c, letters[c-97]);
		}
	}
	//look at our stuff before you go!
	for (int i =0; i < 26; ++i)
		printf("%f\n",prog_letter_freq[i]);
	display(mp);

	//write out to file for reloading. store all words and all times appear
	FILE *fp;
	if ((fp=fopen("wordstore.csv","w"))==NULL)
		printf("cannot open file\n");
	for (int i = 0; i < mp.sz; ++i){
		struct node * curr = mp.table[i];
		while(curr){
			for(int j = 0; j < curr->pair.cnt; ++j){
				fprintf(fp,"%s,",curr->pair.word);
			}
			curr = curr->nxt;
		}
	}
	fclose(fp);

	return 0;
}
