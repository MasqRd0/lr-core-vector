/* vector.c —— 你要实现的地方 */

#include "vector.h"
#include<stdlib.h>
int *buf=NULL;
int vector_init(vector *v, size_t capacity) {
	if(capacity==0)
	{
		v->data=NULL;
		v->end=NULL;
		v->cap=NULL;
		return 0;
	}
	else if(capacity>SIZE_MAX/sizeof(int))
	{
		v->data=NULL;
		v->end=NULL;
		v->cap=NULL;
		return -1;
	}
	else
	{
		buf=malloc(capacity*sizeof(int));
		if(buf==NULL)
		{
			v->data=NULL;
			v->end=NULL;
			v->cap=NULL;
			free(buf);
			return -1;			
		}
		v->data=buf;
		v->cap=buf+capacity;
		v->end=buf;
	}
	
    return 0;
}

void vector_destroy(vector *v)
{
	v->data=NULL;
	v->cap=NULL;
	v->end=NULL;
	free(buf);
	buf=NULL;
}

size_t size(const vector *v) {
    return ((v->end)-(v->data));
}

size_t capacity(const vector *v) {
    return ((v->cap)-(v->data));
}

int empty(const vector *v) {
	if(size(v)==0) return 1;
	else return 0;
}

int get(const vector *v, size_t index, int *out) {
    if(index>=size(v)) return -1;
    else if(index<=0) *out=*buf;
	else *out=*(buf+index);
    return 0;
}

int set(vector *v, size_t index, int value) {
    if(index>=size(v)) return -1;
	else if(index<=0) *buf=value;
	*(buf+index)=value;
    return 0;
}

int front(const vector *v, int *out) {
	if(empty(v)) return -1;
	*out=*(buf);
    return 0;
}

int back(const vector *v, int *out) {
    if(empty(v)) return -1;
    *out=*(buf+size(v)-1);
	return 0;
}

int push_back(vector *v, int value) {
    if(capacity(v)==0) 
	{
		int *tmp=realloc(buf,(capacity(v)+1)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			buf=tmp;
			*buf=value;
			v->end=buf+1;
			v->cap=buf+1;
			v->data=buf;
		}
	}
    else if(capacity(v)>size(v))
	{
		*(buf+size(v))=value;
		(v->end)++;
	}
    else
    {
		if(2*capacity(v)>SIZE_MAX/sizeof(int)) return -1;
		int *tmp=realloc(buf,2*capacity(v)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			buf=tmp;
			v->cap=buf+2*capacity(v);
			*(buf+size(v))=value;
			v->end=buf+size(v)+1;
			v->data=buf;
		}
		
	}
	return 0;
}

int pop_back(vector *v, int *out) {
    if(empty(v)) return -1;
    else *out=*((v->end)-1);
    (v->end)--;
	return 0;
}

int reserve(vector *v, size_t new_capacity) {
	if(new_capacity<=capacity(v)) return 0;
	else if(new_capacity>SIZE_MAX/sizeof(int))
		return -1;
	else
	{
		int *tmp=realloc(buf,new_capacity*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			buf=tmp;
			v->cap=buf+new_capacity;
			v->end=buf+size(v);
			v->data=buf;
		}
	}
	return 0;
}

int shrink_to_fit(vector *v) {
	if(size(v)==0)
	{
		v->data=NULL;
		v->end=NULL;
		v->cap=NULL;
		free(buf);
		buf=NULL;
		return 0;
	}
	else
	{
		int *tmp=realloc(buf,size(v)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			buf=tmp;
			(v->cap)=(v->end);
			return 0;
		}
	}
    return 0;
}

void clear(vector *v) {
	(v->end)=(v->data);
}
