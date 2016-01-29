#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_CHAR_NUM 26
#define MAX_KEY_WORD 36
char freq_of_char[MAX_CHAR_NUM] = {0};

static char *static_site[] = {"do", "end", "else", "case", "downto", "goto",
			      "to", "otherwise", "type", "while", "const", "div",
			      "and", "set", "or", "of", "mod", "file", "record",
			      "packed", "not", "then", "procedure", "with", "repeat",
			      "var", "in", "array", "if", "nil", "for",
			      "begin", "until", "label", "function", "program"};

char *static_site_in_order[MAX_KEY_WORD] = {NULL};

struct static_sites {
	char char1;
	char char2;
	char *str;
	char strlengh;
	char key_value;
} ss[MAX_KEY_WORD] = {{'d','o',"do", 2}, {'e','d',"end", 3}, {'e','e',"else", 4},
		      {'c','e',"case", 4}, {'d','o',"downto", 6}, {'g','o',"goto", 4},
		      {'t','o',"to", 2}, {'o','e',"otherwise", 9}, {'t','e',"type", 4},
		      {'w','e',"while", 5}, {'c','t',"const", 5}, {'d','v',"div", 3},
		      {'a','d',"and", 3}, {'s','t',"set", 3}, {'o','r',"or", 2},
		      {'o','f',"of", 2}, {'m','d',"mod", 3}, {'f','e',"file", 4},
		      {'r','d',"record", 6}, {'p','d',"packed", 6}, {'n','t',"not", 3},
		      {'t','n',"then", 4}, {'p','e',"procedure", 9}, {'w','h',"with", 4},
		      {'r','t',"repeat", 6}, {'v','r',"var", 3}, {'i','n',"in", 2},
		      {'a','y',"array", 5}, {'i','f',"if", 2}, {'n','l',"nil", 3},
		      {'f','o',"for", 3}, {'b','n',"begin", 5}, {'u','l',"until", 5},
		      {'l','l',"label", 5}, {'f','n',"function", 8}, {'p','m',"program", 7}};

struct static_sites *ssp[MAX_KEY_WORD] = {NULL};

struct freq_char {
	unsigned char c;
	unsigned char freq;
	unsigned char key;
};

struct freq_char *freq_of_char_in_order[MAX_CHAR_NUM] = {NULL};
struct freq_char *freq_of_char_in_alph[MAX_CHAR_NUM] = {NULL};
struct freq_char *c_c = freq_of_char_in_order;

void calc_string(char *one_str)
{
	int num = strlen(one_str);
	int key = num + (*one_str - 'a') + (*(one_str + num - 1) - 'a');
//	printf("str(%s) \t= len(%d), key(%d, %d)\n", one_str, num, (*one_str - 'a'), (*(one_str + num - 1) - 'a'));
	freq_of_char[*one_str - 'a']++;
	freq_of_char[*(one_str + num - 1) - 'a']++;
}

void swap(struct freq_char **first, struct freq_char **second)
{
	long temp = *first; 
	*first = *second;
	*second = (struct freq_char *)temp;
}

void qsort_freq(int mid_pos, int num)
{
	int i = 0;
	int m = mid_pos;
	struct freq_char *tmp = NULL;
	
	if (mid_pos >= num) {
		return;
	}

	for (i = mid_pos + 1; i <= num; i++) {
		if (freq_of_char_in_order[i]->freq >= freq_of_char_in_order[mid_pos]->freq) {
			swap(&freq_of_char_in_order[++m], &freq_of_char_in_order[i]);
		}
	}
	
	//printf("%*s|%*s|\n", (mid_pos<<1), "", (m<<1) - (mid_pos<<1) - 1, ""); 
	swap(&freq_of_char_in_order[mid_pos], &freq_of_char_in_order[m]);

	qsort_freq(mid_pos, m - 1);
	qsort_freq(m + 1, num);
}

void order_freq()
{
	int i = 0;
	struct freq_char *fc = NULL;
	/* we need to order char by freq. */
	for (; i < MAX_CHAR_NUM; i++) {
		fc = (struct freq_char *)malloc(sizeof(struct freq_char));
		if (fc == NULL) {
			printf("malloc error!\n");
			exit(-1);
		}
		fc->freq = freq_of_char[i];
		fc->c = i + 'a';
		fc->key = 0;
		freq_of_char_in_order[i] = fc;
		freq_of_char_in_alph[i] = fc;
	}

	qsort_freq(0, MAX_CHAR_NUM - 1);
#if 0
	/* we could delete these code, we don't use it anymore */
	/* ordering string by char's freq. */
	for (i = 0;i < sizeof(static_site)/sizeof(char *); i++) {
		insert_into_tree(static_site[i]);
	}
#endif
}
void order_freq_of_word()
{
	int i = 0;
	int j = 0;
	int s = 0;
	int num = 0;
	for (; i < MAX_CHAR_NUM; i++) {
		for (j = 0; j <= i; j++) {
//			printf("==== > %c %c\n",freq_of_char_in_order[i]->c, freq_of_char_in_order[j]->c);
			for (s = 0; s < MAX_KEY_WORD; s++) {
				if ((ss[s].char1 == freq_of_char_in_order[i]->c) && (ss[s].char2 == freq_of_char_in_order[j]->c)) {
					printf("num = %d, %s\n", num, ss[s].str);
					static_site_in_order[num] = static_site[s];
					ssp[num] = &ss[s];
					num++;
					continue;
				} else if ((ss[s].char2 == freq_of_char_in_order[i]->c) && (ss[s].char1 == freq_of_char_in_order[j]->c)) {
					printf("num = %d, %s\n", num, ss[s].str);
					static_site_in_order[num] = static_site[s];
					ssp[num] = &ss[s];
					num++;
					continue;
				} else {
					continue;
				}
			}
		}
	}

	for (i = 0; i < MAX_KEY_WORD; i++)
		printf("%d = %s\n",i, static_site_in_order[i]);
	
}

char check_collision(char num)
{
	int i = 0;
	for (; i < num; i++) {
		//printf("<%s> <%s>\n", ssp[i]->str, ssp[num]->str);
		if (ssp[i]->key_value == ssp[num]->key_value) {
			//printf("-------->%s, %s collision\n", ssp[i]->str, ssp[num]->str);
			return 1;
		}
	}
	return 0;
}

char update_keyvalue(int i)
{

	while (check_collision(i)) {
		/*
		 * We should update key value here
		 * And we need to check collision once we update key value
		 */
		ssp[i]->key_value = ssp[i]->key_value + 1;
	}
}

void processing_char()
{
	int i = 0;
	char c_c = 0; // current char
	for (; i < MAX_KEY_WORD; i++) {
		ssp[i]->key_value = freq_of_char_in_alph[ssp[i]->char1 - 'a']->key + freq_of_char_in_alph[ssp[i]->char2 - 'a']->key + ssp[i]->strlengh;
		printf("[%s = %c ... %d ... %c] = %d\n", ssp[i]->str, ssp[i]->char1, ssp[i]->strlengh, ssp[i]->char2, ssp[i]->key_value);
	}

	for (i = 0; i < MAX_KEY_WORD; i++) {
		update_keyvalue(i);
#if 0
		if (c_c == ssp[i]->char1) {
			
		} else if (c_c == ssp[i]->char2) {

		}
#endif
	}
	for (i = 0; i < MAX_KEY_WORD; i++) {
		printf("[%s = %c ... %d ... %c] = %d\n", ssp[i]->str, ssp[i]->char1, ssp[i]->strlengh, ssp[i]->char2, ssp[i]->key_value);
	}
}

int hash_func(char *str)
{
	/* hash value = key length + first character + last charater */
	unsigned char key = 0;
	key = strlen(str);
	key += (*str + *(str + key - 1));
	return key;
}

int main(int argc, char *argv[])
{
	int i = 0;
	
	while (i < sizeof(static_site)/sizeof(char *)) {
		calc_string(static_site[i++]);
	}
	
	order_freq();
	for (i = 0; i < MAX_CHAR_NUM; i++) {
		printf("%c = %d\n", freq_of_char_in_order[i]->c, freq_of_char_in_order[i]->freq);
	}
	order_freq_of_word();
	processing_char();
//	print_freq_by_tree(tree_root);
	return 0;
}
