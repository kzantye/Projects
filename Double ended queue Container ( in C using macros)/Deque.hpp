/*
 Program Name: Deque.hpp
 Author: Kunal Zantye
 Program Intent: Implement a Container in C
 Input Data: Test File
 Output Data: In Readme File
 Compile Note: Use g++ to compile.
 */

/*---------------
 Include Section
 ----------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------
 Include Guards
 ----------------*/
#ifndef DEQUE_H
#define DEQUE_H
#define Deque_DEFINE(t)																							\
typedef struct Deque_##t Deque_##t;																				\
typedef struct Deque_##t Deque_##t;																				\
typedef struct Deque_##t##_Iterator{                                   											\
Deque_##t *itrdeq;																								\
t* curr_val;                                                  													\
int current_index;                                                    											\
int front_index;                                                       											\
int rear_index;                                                       											\
int max_size;                                                                                                   \
void (*inc) (Deque_##t##_Iterator *);                                 											\
void (*dec) (Deque_##t##_Iterator *);                                 											\
t& (*deref) (Deque_##t##_Iterator *);                                 											\
}Deque_##t##_Iterator;                                                                           				\
typedef struct Deque_##t{                                                 										\
t* container;                                                              										\
int front_index, rear_index, arr_size, current_size;                               								\
char type_name [sizeof("Deque_"#t)];                                  											\
bool (*empty)(struct Deque_##t*);                                     											\
void (*push_back)(struct Deque_##t*, t);                              											\
void (*push_front)(struct Deque_##t*, t);                             											\
void (*pop_front)(struct Deque_##t*);                                 											\
void (*pop_back)(struct Deque_##t*);                                  											\
t& (*front)(struct Deque_##t*);                                       											\
t& (*back)(struct Deque_##t*);                                        											\
t& (*at)(struct Deque_##t* deq, int index);                            											\
void (*dtor)(struct Deque_##t*);                                      											\
void (*clear)(struct Deque_##t*);                                     											\
int (*size)(struct Deque_##t*);                                       											\
bool (*check_eq) (const t &o1, const t &o2);                               										\
bool (*Deque_##t##_Iterator_equal)(Deque_##t##_Iterator, Deque_##t##_Iterator);           						\
Deque_##t##_Iterator (*begin)(struct Deque_##t*);                     											\
Deque_##t##_Iterator (*end)(struct Deque_##t*);                       											\
} Deque_##t;                                                              										\
bool empty(struct Deque_##t* deq) {                                        										\
if (deq->front_index == -1)                                                   									\
return true;     																								\
return false;                                    																\
}																												\
void push_back(struct Deque_##t *deq, t val)																	\
{																												\
if(empty(deq))																									\
{   																											\
deq->front_index=0;																								\
deq->rear_index=0;																								\
deq->container[deq->rear_index]=val;																			\
deq->current_size++;																							\
}																												\
else																											\
{																												\
if(deq->current_size >= deq->arr_size)																			\
{   																											\
t *temp;																										\
deq->rear_index=deq->current_size-1;																			\
deq->arr_size=deq->arr_size*2;																					\
temp=(t*)realloc(deq->container,deq->arr_size*sizeof(t));														\
if (temp)																										\
deq->container=temp;																							\
temp=NULL;																										\
}																												\
deq->rear_index=(deq->rear_index + 1) % deq->arr_size;															\
deq->container[deq->rear_index]=val;																			\
deq->current_size++;																							\
}																												\
} 																												\
void push_front(struct Deque_##t *deq, t val)																	\
{																												\
if(empty(deq))																									\
{   																											\
deq->front_index=0;																								\
deq->rear_index=0;																								\
deq->container[deq->rear_index]=val;																			\
deq->current_size++;																							\
}																												\
else																											\
{																												\
int i,j; 																										\
if(deq->current_size >= deq->arr_size)																			\
{   																											\
t *temp,*temp2;																									\
deq->arr_size=deq->arr_size*2;																					\
temp=(t*)realloc(deq->container,deq->arr_size*sizeof(t));														\
for (i = deq->front_index, j = deq->front_index; i != deq->rear_index; i = (i + 1) % (deq->arr_size/2)){        \
temp[j++] = deq->container[i];                                   												\
}                                                                 												\
temp[j] = deq->container[i];																					\
temp2=deq->container;																							\
deq->container=temp;																							\
temp=NULL;																										\
deq->rear_index=j;																								\
}																												\
deq->front_index = (deq->front_index - 1 + deq->arr_size) % deq->arr_size;          							\
deq->container[deq->front_index] = val;                                        									\
deq->current_size++;																							\
}																												\
}                                                                  												\
void pop_front(struct Deque_##t* deq){                                      									\
if (empty(deq)){                                                  												\
return;																											\
}                                                                     											\
else																											\
{																												\
if (deq->front_index == deq->rear_index){                                       								\
deq->front_index = deq->rear_index = -1;                                         								\
}                                                                     											\
else{                                                                 											\
deq->front_index = (deq->front_index + 1) % deq->arr_size;                         								\
}																												\
deq->current_size--;                                               												\
}                                                                    											\
}                                                                         										\
void pop_back(struct Deque_##t* deq){                                      										\
if (empty(deq)){                                                  												\
return;																											\
}                                                                 												\
else																											\
{ 																												\
if (deq->front_index == deq->rear_index)																		\
{                																								\
deq->front_index = deq->rear_index = -1;                                         								\
}                                                                 												\
else																											\
{                                                             													\
deq->rear_index = (deq->rear_index - 1 + deq->arr_size) % deq->arr_size;          								\
}                                                                 												\
deq->current_size--;                                               												\
}																												\
}    																											\
t& front(Deque_##t* deq){                                                  										\
return deq->container[deq->front_index];                                                 						\
}                                                                         										\
t& back(Deque_##t* deq){                                                   										\
return deq->container[deq->rear_index];                                                 						\
}                                                                         										\
t& at(struct Deque_##t* deq, int index){                                   										\
return (deq->container[(deq->front_index + index) % (deq->arr_size)]);                    						\
}         																										\
void dtor(struct Deque_##t* deq){                                                                               \
free(deq->container);                                                                                           \
deq->container = NULL;                                                                                          \
}                                                                                                               \
void clear(struct Deque_##t* deq){                                                                              \
deq->front_index = -1;                                                                                          \
deq->rear_index = -1;                                                                                           \
deq->current_size = 0;                                                                                          \
memset(deq->container, 0, sizeof(t)*deq->arr_size);                                                             \
}                                                                                                               \
int size(struct Deque_##t* deq) {                                                                               \
return deq->current_size;                                                                                       \
}                                                                                                               \
bool Deque_##t##_Iterator_equal (Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){                           \
if(it1.current_index == (it2.rear_index + 1) % (it2.max_size))                                                  \
return true;                                                                                                    \
else                                                                                                            \
{return false;}                                                                                                 \
}                                                                                                               \
bool Deque_##t##_equal(struct Deque_##t q1, struct Deque_##t q2){                                               \
if (q1.current_size == q2.current_size){                                                                        \
int i = q1.current_size-1, index=0;                                                                             \
for (i = q1.current_size-1,index=0; i>=0; i--,index++)                                                          \
{                                                                                                               \
if(!(q1.check_eq( q1.at(&q1,index), q2.at(&q2,index)) || q1.check_eq( q2.at(&q2,index), q1.at(&q1,index)) ))    \
continue;                                                                                                       \
else                                                                                                            \
{return false;}                                                                                                 \
}                                                                                                               \
return true;                                                                                                    \
}                                                                                                               \
return false;                                                                                                   \
}                                                                                                               \
void inc(Deque_##t##_Iterator * it)																				\
{                                                                                                				\
if (it->current_index == (it->max_size - 1))																	\
it->curr_val = it->curr_val - (it->max_size-1);       															\
else																											\
{        																										\
it->curr_val++;																									\
it->current_index++;																							\
}																												\
}                                                             													\
void dec(Deque_##t##_Iterator * it)																				\
{                                     																		 	\
if(it->current_index == -1)																						\
{                                               																\
it->curr_val = &it->itrdeq->container[it->itrdeq->rear_index];													\
it->current_index = it->rear_index;	                                       										\
}																												\
else																											\
{  	                                                              			 									\
if(it->current_index == 0)																						\
it->curr_val = it->curr_val + (it->max_size-1);       															\
else  																											\
{                                                        														\
it->curr_val--;   																								\
it->current_index--;                                            												\
}    																											\
}                                                                     											\
}      																											\
t& deref(Deque_##t##_Iterator * it){                                      										\
return *(it->curr_val);                                           												\
}     																											\
Deque_##t##_Iterator begin(Deque_##t* deq){                                										\
Deque_##t##_Iterator it;                                                  										\
it.inc = &inc;                                                            										\
it.dec = &dec;                                                            										\
it.deref = &deref;                     																			\
it.itrdeq= deq;                                   																\
it.curr_val =&(deq->container[deq->front_index]);                                 								\
it.current_index= deq->front_index;                                               								\
it.front_index= deq->front_index;                                                  								\
it.rear_index= deq->rear_index;                                                  								\
it.max_size= deq->arr_size;                                            											\
return  it;                                                               										\
}                                                              													\
Deque_##t##_Iterator end(Deque_##t* deq){                                  										\
Deque_##t##_Iterator it;                                                  										\
it.inc = &inc;                                                            										\
it.dec = &dec;                                                            										\
it.deref = &deref;   																							\
it.itrdeq= deq;                                                       											\
it.curr_val =NULL;																								\
it.current_index=-1;                                                       										\
it.front_index= deq->front_index;                                                  								\
it.rear_index= deq->rear_index;                                                  								\
it.max_size= deq->arr_size;                                            											\
return it;                                                                										\
}                                                                         										\
void  Deque_##t##_ctor (struct Deque_##t* deq, bool (*fptr) (const t &o1, const t &o2)){        				\
deq->front_index = -1;                                                            								\
deq->rear_index = -1;                                                            								\
deq->current_size = 0;                                                     										\
deq->arr_size = 2;                                                         										\
deq->container = (t*)malloc(sizeof(t) * 2);                                      								\
strcpy(deq->type_name,"Deque_"#t);                                         										\
deq->empty= &empty;                                                        										\
deq->push_back =  &push_back;                                               									\
deq->push_front =  &push_front;                                              									\
deq->pop_front =  &pop_front;                                               									\
deq->pop_back =  &pop_back;                                                										\
deq->front = &front;                                                       										\
deq->back = &back;                                                         										\
deq->at = &at;                                                          										\
deq->dtor =  &dtor;                                                  											\
deq->clear =  &clear;                                                  											\
deq->size = &size;                                                         										\
deq->Deque_##t##_Iterator_equal = &Deque_##t##_Iterator_equal;             										\
deq->check_eq=*fptr;                                                         									\
deq->begin = &begin;                                                       										\
deq->end = &end;}
#endif