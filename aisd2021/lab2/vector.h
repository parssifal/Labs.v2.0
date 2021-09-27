#ifndef vector_h
#define vector_h

#include "data.h"

typedef struct passenger_v{
	char* id;
	int ta;
	int ts;
	//struct passenger* next;
}pas_v;

typedef struct stand_v{
	int lengh;
	int time;
	pas_v* pass;
	//pas* first;
	//pas* last;
}stand_v;

typedef struct queue_v{
	int sts;
	stand_v* st;
}queue_v;

void delete_vector(queue_v* q);

void pop_vector(queue_v* q, int time);

int push_vector(queue_v* q, dpas* pq, int time);

void read_vector(queue_v* q, int time);

int check_vector(queue_v* q);

queue_v* init_vector(queue_v* q, int g);

#endif //vector_h