#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* str_data(char d[], int p){
	printf("%s", d);
	char buf[20] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%20[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}

data* new_data(data* l){
	l = (data *)calloc(1, sizeof(data));
	dpas* p = (dpas *)calloc(1, sizeof(dpas));
	p->id = NULL;
	int i = 0, t = 0;
	char c;
	printf("Enter id/ta/ts: ");
	do{
		
		p->id = (char *)calloc(100, sizeof(char));
		scanf("%[^/]s", p->id);
		scanf("%*c");
		if (t == 0){
			l->first = p;
			t = 1;
		}
		i = 0;
		scanf("%d%*c%d", &p->ta, &p->ts);
		scanf("%c", &c);
		p->next = NULL;
		if (c != '\n'){
			p->next = (dpas *)malloc(sizeof(dpas));
			p = p->next;
			p->id = NULL;
		}
	}while (c != '\n');
	return l;
}

void delete_data(data* l){
	dpas* pq = l->first;
	dpas* pp;
	while(pq){
		pp = pq->next;
		free(pq->id);
                free(pq);
                pq = pp;
	}
	free(l);
}