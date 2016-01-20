#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_CHAR_NUM 26
char freq_of_char[MAX_CHAR_NUM] = {0};

static enum {LEFT, RIGHT};
static char *static_site[] = {"do", "end", "else", "case", "downto", "goto",
			      "to", "otherwise", "type", "while", "const", "div",
			      "and", "set", "or", "of", "mod", "file", "record",
			      "packed", "not", "then", "procedure", "with", "repeat",
			      "var", "in", "array", "if", "nil", "for",
			      "begin", "until", "label", "function", "program"};

struct freq_tree {
	struct freq_tree *left;
	struct freq_tree *right;
	unsigned char freq;
	unsigned char str_len;
        char *str;
};

struct freq_char {
	unsigned char c;
	unsigned char freq;
};

struct freq_char *freq_of_char_in_order[MAX_CHAR_NUM] = {NULL};

struct freq_tree *tree_root = NULL;

struct freq_tree *insert_into_tree(char *instring)
{
	unsigned char this_freq = 0;
	struct freq_tree *tmp = NULL;
	struct freq_tree *seek = tree_root;
	struct freq_tree *papa = NULL;
	char left_or_right = LEFT;

	assert(instring != NULL);
	tmp = (struct freq_tree *)malloc(sizeof(struct freq_tree));
	if (tmp == NULL) {
		printf("malloc error!\n");
		exit(-1);
	}
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->str = instring;
	tmp->str_len = strlen(instring);
	tmp->freq = this_freq = freq_of_char[*instring - 'a'] + freq_of_char[*(instring + tmp->str_len - 1) - 'a'] + tmp->str_len;

	/* the first noot, which is root */
	if (seek == NULL) {
		tree_root = tmp;
		return tree_root;
	}
	
	while (seek != NULL) {
		papa = seek;
		if (seek->freq > tmp->freq) {
			seek = seek->left;
			left_or_right = LEFT;
		} else if (seek->freq < tmp->freq){
			seek = seek->right;
			left_or_right = RIGHT;
		} else {
			seek = seek->right;
			left_or_right = RIGHT;
			break;
		}
	}

	switch (left_or_right) {
	case LEFT:
		papa->left = tmp;
		break;
	case RIGHT:
		if (seek == NULL) {
			papa->right = tmp;
		} else {
			tmp->right = seek;
			papa->right = tmp;
		}
		break;
	default:
		break;
	}
}


void calc_string(char *one_str)
{
	int num = strlen(one_str);
	int key = num + (*one_str - 'a') + (*(one_str + num - 1) - 'a');
	printf("str(%s) \t= len(%d), key(%d, %d)\n", one_str, num, (*one_str - 'a'), (*(one_str + num - 1) - 'a'));
	freq_of_char[*one_str - 'a']++;
	freq_of_char[*(one_str + num - 1) - 'a']++;
}

void print_freq()
{
	int i = 0;
	char *tmp = NULL;
	for (; i < MAX_CHAR_NUM; i++) {
		printf("%c shows %d times!\n", i + 'a', freq_of_char[i]);
	}

	for (i = 0; i < sizeof(static_site)/sizeof(char *); i++) {
		tmp = *(static_site + i);
		printf("%s has %d freq!\n", static_site[i], freq_of_char[*tmp - 'a'] + freq_of_char[*(tmp + strlen(tmp) - 1) - 'a']);
	}
}

void print_freq_by_tree(struct freq_tree *fnode)
{
	if (fnode == NULL)
		return;

	print_freq_by_tree(fnode->left);
	printf("%s = %d\n", fnode->str, fnode->freq);
	print_freq_by_tree(fnode->right);
	
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

	for (i = mid_pos + 1; i < num; i++) {
		if (freq_of_char_in_order[i]->freq < freq_of_char_in_order[mid_pos]->freq) {
			swap(&freq_of_char_in_order[++m], &freq_of_char_in_order[i]);
		}
	}
	
	for (i = 0; i < MAX_CHAR_NUM; i++) {
		printf("%d ", freq_of_char_in_order[i]->freq);
	}
	printf("\n");
	printf("mid_pos = %d, m = %d\n", mid_pos, m);
	swap(&freq_of_char_in_order[mid_pos], &freq_of_char_in_order[m]);

	for (i = 0; i < MAX_CHAR_NUM; i++) {
		printf("%d ", freq_of_char_in_order[i]->freq);
	}
	printf("\n");
	printf("%d, %d\n", mid_pos, m - 1);
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
		freq_of_char_in_order[i] = fc;
	}


	/* just for test */
	for (i = 0; i < MAX_CHAR_NUM; i++) {
		fc = freq_of_char_in_order[i];
		printf("---->%c = %d\n", fc->c, fc->freq);
	}
	qsort_freq(0, MAX_CHAR_NUM);

	for (i = 0; i < MAX_CHAR_NUM; i++) {
		fc = freq_of_char_in_order[i];
		printf("----> new %c = %d\n", fc->c, fc->freq);
	}
	
	/* ordering string by char's freq. */
	for (i = 0;i < sizeof(static_site)/sizeof(char *); i++) {
		insert_into_tree(static_site[i]);
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
//		printf("%d : %s : ", i, static_site[i]);
//		printf("key = %d\n", hash_func(static_site[i]));
		calc_string(static_site[i++]);
	}
	print_freq();
	order_freq();
	print_freq_by_tree(tree_root);
	return 0;
}
