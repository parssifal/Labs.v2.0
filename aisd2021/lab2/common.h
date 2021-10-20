#ifndef common_h
#define common_h

#ifdef FLAG
	#include "list.h"
#else 
	#include "vector.h"
#endif

#include "data.h"

typedef struct CONTEINER{
	#ifdef FLAG
		queue_l cont;
	#else
		queue_v cont;
	#endif
}CONTEINER;

typedef struct{
	CONTEINER* conteiner;
}QUEUE;

void pop_queue(CONTEINER* q, int time);

void push_queue(CONTEINER* q, dpas* pq, int time);

CONTEINER* init_queue(CONTEINER* q, int g);

void delete_queue(CONTEINER* q);

int check_queue(CONTEINER* q);

#endif //common_h