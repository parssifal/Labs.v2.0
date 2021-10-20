#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "data.h"

void pop_list(queue_l* q, int time){
	stand_l* a = q->st;
	for (int r = 0; r < q->sts; r ++){
		while (a[r].lengh > 0 && a[r].time + a[r].first->ts == time){
			pas_l* p = a[r].first;
			a[r].first = p->next;
			a[r].lengh--;
			a[r].time = time;
			free(p);
			p = NULL;
			read_list(q, time);
		}
        }
}

queue_l* init_list(queue_l* q, int g){
	q->sts = g;
	q->st = (stand_l *)malloc(g * sizeof(stand_l));
	for (int i = 0; i < g; i ++){
		q->st[i].lengh = 0;
		q->st[i].pass = (pas_l *)malloc(sizeof(pas_l));
	}
	return q;
}

void read_list(queue_l* q, int time){
	printf("Time is %d.\n", time);
	for (int i = 0; i < q->sts; i ++){
		printf("Stand %d: ", i + 1);
		if (q->st[i].lengh > 0){
			pas_l* pq = q->st[i].first;
			for (int j = 0; j < q->st[i].lengh; j ++){
				printf("%s ", pq->id);
				pq = pq->next;
			}	
		}
		printf("\n");
	}
	printf("\n");
}

int push_list(queue_l* q, dpas* pq, int time){
	int k = 100000, r;
		for (int l = 0; l < q->sts; l++){
			if (q->st[l].lengh != 0) {
				if ((q->st[l].time/q->st[l].lengh) < k){
					k = q->st[l].time/q->st[l].lengh;
					r = l;
				}
			} else if (q->st[l].lengh == 0){
				r = l;
				k = 0;
				break;
			}
        }
	printf("%s\n", pq->id);
	q->st[r].pass->id = pq->id;
	q->st[r].pass->ta = pq->ta;
	q->st[r].pass->ts = pq->ts;
	if (q->st[r].lengh == 0){
		q->st[r].first = q->st[r].pass;
		q->st[r].time = pq->ta;
	}
	q->st[r].lengh += 1;
	q->st[r].last = q->st[r].pass;
	q->st[r].pass->next = (pas_l *)malloc(sizeof(pas_l));
	q->st[r].pass = q->st[r].pass->next;
	read_list(q, time);
	return 0;
}

int check_list(queue_l* q){
	for (int v = 0; v < q->sts; v ++){
			if (q->st[v].lengh > 0){
				return 1;
			}
	}
	return 0;
}

void delete_list(queue_l* q){
	for (int i = 0; i < q->sts; i ++){
		free(q->st[i].first);
	}
	free(q->st);
	free(q);
}