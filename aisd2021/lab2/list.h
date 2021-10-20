#ifndef list_h
#define list_h

#include "data.h"

//QUEUE
typedef struct passenger_l{
	char* id;
	int ta;
	int ts;
	struct passenger_l* next;
}pas_l;

typedef struct stand_l{
	int lengh;
	int time;
	pas_l* pass;
	pas_l* first;
	pas_l* last;
}stand_l;

typedef struct queue_l{
	int sts;
	stand_l* st;
}queue_l;

int push_list(queue_l* q, dpas* pq, int time);

void pop_list(queue_l* q, int time);

void read_list(queue_l* q, int time);

void delete_list(queue_l* q);

queue_l* init_list(queue_l* q, int g);

int check_list(queue_l* q);

#endif // list_h
