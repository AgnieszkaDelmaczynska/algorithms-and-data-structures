#include <stdio.h>


	enum { 
		CMD_LENGTH,
		CMD_PRINT,
		CMD_ERROR
	} ecmd;

	struct Elem {
		int key;
		Elem* next;
		Elem(Elem* e, int k) : next(e), key(k) { }
	};

	char cmd;
	int n;
	bool isEmptyQueue;
	Elem *first, *last;


int parseEnum(char cmd) {
	return cmd == 'L' ? CMD_LENGTH :
		cmd == 'P' ? CMD_PRINT :
		CMD_ERROR;
}

Elem *search(int key)
{
	if(!first) return NULL;
	Elem *tmp = first;
	while(tmp->key != key && tmp != last) tmp = tmp->next;
	if (tmp->key == key) return tmp;
	else return NULL;
}

void printAll() {
	if(!first || isEmptyQueue) printf("-\n");	
	else {
		Elem *tmp = first;
		while(tmp != last) {
			printf("%d->", tmp->key);
			tmp = tmp->next;
		}
		printf("%d\n", last->key);
	}
}

int totalLength()
{
	if(!first) return 0;
	int len(1);
	Elem *tmp = first;
	while(tmp->next != first) { tmp = tmp->next; len++; }
	return len;
}

int main()
{
	isEmptyQueue  = true;
	while(scanf("%c", &cmd) > 0) {
		switch (parseEnum(cmd))
		{	
			case CMD_LENGTH:
				printf("%d\n", totalLength());
				break;

			case CMD_PRINT:
				printAll();
				break;
			
			case CMD_ERROR:
			default:
				break;
		}

	}
	return 0;
}

