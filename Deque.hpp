#ifndef DEQUE_HPP
#define DEQUE_HPP
// use macro for double-ended container
// MUST implement as a CIRCULAR, DYNAMIC ARRAY. NO LINKED LIST!!
// 2 struct types: one for the container itself, the other for the iterator
// should be able to contain any type w/o using void *
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void Deque__##t##__ctor(Deque__##t * dp, bool(*)(const t &o1, const t &o2);
*/
// Sometimes it is that simple.
#define Deque_DEFINE(t)																			\
	struct Deque_##t{																			\
		t * data;																				\
		int head; 																				\
		int tail;																				\
		bool isFull;																			\
		size_t numElems;																			\
		int maxSize;																			\
		void (*ctor)(Deque__##t * dp, bool(*con)(const t &, const t &);			\
	};																							\
	void Deque__##t##__ctor(Deque__##t * dp, bool(*)(const t &o1, const t &o2)){				\
		dp->head = 0;																			\
		dp->tail = 0;																			\
		isFull = false;																			\
		numElems = 0;																			\
	}																							\
	void Deque__##t##__dtor(Deque__##t * dp){													\
		free(dp->data);																			\
	}																							\
	size_t Deque__size(Deque__##t deq){ 															\
		return numElems;/*return sizeof(deq.data)/sizeof(* deq.data);*/ 				\
	}																							\
	/*void push_back(Deque__##t * dp, t){													\
																\
	}															\
	void pop_back(Deque__##t){ 															\
																\
	}															\
	bool Deque_##t##_equal(){									\
																\
	}*/															\
	}

#endif
