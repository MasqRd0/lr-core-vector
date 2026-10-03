/* vector.c —— 你要实现的地方 */

#include "vector.h"
#include<stdlib.h>
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
		v->data=malloc(capacity*sizeof(int));
		if(v->data==NULL)
		{
			v->end=NULL;
			v->cap=NULL;
			return -1;			
		}

		v->cap=(v->data)+capacity;
		v->end=v->data;
	}
	
    return 0;
}

void vector_destroy(vector *v)
{
	v->cap=NULL;
	v->end=NULL;
	free(v->data);
	v->data=NULL;
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
    else if(index<=0) *out=*v->data;
	else *out=*((v->data)+index);
    return 0;
}

int set(vector *v, size_t index, int value) {
    if(index>=size(v)) return -1;
	else if(index<=0) *v->data=value;
	*((v->data)+index)=value;
    return 0;
}

int front(const vector *v, int *out) {
	if(empty(v)) return -1;
	*out=*v->data;
    return 0;
}

int back(const vector *v, int *out) {
    if(empty(v)) return -1;
    *out=*((v->data)+size(v)-1);
	return 0;
}

int push_back(vector *v, int value) {
    if(capacity(v)==0) 
	{
		int *tmp=realloc(v->data,(capacity(v)+1)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			v->data=tmp;
			*v->data=value;
			v->end=v->data+1;
			v->cap=v->data+1;
		}
	}
    else if(capacity(v)>size(v))
	{
		*(v->data+size(v))=value;
		(v->end)++;
	}
    else
    {
		if(2*capacity(v)>SIZE_MAX/sizeof(int)) return -1;
		int *tmp=realloc(v->data,2*capacity(v)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			v->cap=tmp+2*capacity(v);
			*(tmp+size(v))=value;
			v->end=tmp+size(v)+1;
			v->data=tmp;
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
		int *tmp=realloc(v->data,new_capacity*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			v->end=tmp+size(v);
			v->cap=tmp+new_capacity;
			v->data=tmp;
		}
	}
	return 0;
}

int shrink_to_fit(vector *v) {
	if(size(v)==0)
	{
		v->end=NULL;
		v->cap=NULL;
		free(v->data);
		v->data=NULL;
		return 0;
	}
	else
	{
		int *tmp=realloc(v->data,size(v)*sizeof(int));
		if(tmp==NULL) return -1;
		else
		{
			v->end=tmp+size(v);
			v->data=tmp;
			v->cap=v->end;
			return 0;
		}
	}
    return 0;
}

void clear(vector *v) {
	v->end=v->data;
}
