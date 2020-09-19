#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(t)																			\
	struct Deque_##t;										\
	struct Deque_##t##_Iterator;																\
	struct Deque_##t{																			\
		t * data;																				\
		int head; 																				\
		int tail;																				\
		bool isFull;																			\
		size_t numElems;																		\
		int curSize;																			\
		char type_name[strlen("Deque_"#t) + 1];/*="Deque_"#t; len of type + nullbyte*/			\
		void (*ctor)(Deque_##t * , bool(*con)(const t &, const t &));							\
		void (*dtor)(Deque_##t *);															\
		t & (*front)(Deque_##t *);																\
		t & (*back)(Deque_##t *);																\
		/*void (*push_back)(Deque_##t * , t );													\
		void (*pop_back)(Deque_##t *);														\
		void (*push_front)(Deque_##t *, t);														\
		void (*pop_front)(Deque_##t *);	*/														\
		size_t (*size)(Deque_##t *);															\
		bool (*empty)(Deque_##t *);																\
	};																							\
	void Deque_##t##_dtor(Deque_##t * dp){														\
		free(dp->data);																			\
	}																							\
	size_t Deque_##t##_size(Deque_##t * dp){												\
		if(dp != nullptr && dp->numElems && !dp->empty(dp)){						\
			return dp->numElems;														\
		}																				\
		else{																		\
			return 0;																	\
		}														\
	}																							\
	bool Deque_##t##_empty(Deque_##t * dp){ 													\
		if(!dp) return true;																	\
		return dp->numElems == 0; 														\
	}																							\
	t & Deque_##t##_front(Deque_##t * dp){														\
		return dp->data[dp->head];																\
	}																							\
	t & Deque_##t##_back(Deque_##t * dp){														\
		return dp->data[dp->tail];																\
	}																							\
	void Deque_##t##_ctor(Deque_##t * dp, bool(*func)(const t &o1, const t &o2)){				\
		dp->data = (t*)malloc(50*sizeof(t));/*new t[50];*/										\
		dp->head = -1;																			\
		dp->tail = 0;																			\
		dp->isFull = false;																		\
		dp->numElems = 0;																		\
		dp->curSize = 50;																		\
		strcpy(dp->type_name, "Deque_"#t);														\
		dp->dtor = &(Deque_##t##_dtor);															\
		dp->front =	&(Deque_##t##_front);														\
		dp->back =	&(Deque_##t##_back);														\
		dp->size = 	&(Deque_##t##_size);														\
		dp->empty = &(Deque_##t##_empty);														\
												\
												\
	}

#endif
