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
	struct Deque_##t##_Iterator;																\
	struct Deque_##t{																			\
		t * data;																				\
		int head; 																				\
		int tail;																				\
		bool isFull;																			\
		size_t numElems;																		\
		int curSize;																			\
		char type_name[strlen("Deque_"#t) + 1]; /*len of type name + nullbyte*/					\
		void (*ctor)(Deque_##t * , bool(*con)(const t &, const t &));							\
		void (*dtor)(Deque_##t *);																\
		t & (*front)(Deque_##t *);																\
		t & (*back)(Deque_##t *);																\
		void (*push_back)(Deque_##t * , t );													\
		void (*pop_back)(Deque_##t *);															\
		void (*push_front)(Deque_##t *, t);														\
		void (*pop_front)(Deque_##t *);															\
		size_t (*size)(Deque_##t *);															\
		bool (*empty)(Deque_##t *);																\
	};																							\
	void Deque_##t##_ctor(Deque_##t * dp, bool(*comparator)(const t &o1, const t &o2)){			\
		dp->data = new t[50];	/* we start at 50 in this house*/								\
		dp->head = -1;																			\
		dp->tail = 0;																			\
		dp->isFull = false;																		\
		dp->numElems = 0;														\
		dp->curSize = 50;																	\
	}																							\
	void Deque_##t##_dtor(Deque_##t * dp){														\
		free(dp->data);																			\
	}																							\
	size_t Deque_##t##_size(Deque_##t * dp){ 													\
		if(dp != nullptr){															\
			return dp->numElems;														\
		}															\
		else return 0;															\
	}																							\
	bool Deque_##t##_empty(Deque_##t * dp){ 													\
		return (dp->numElems == 0); 														\
	}																							\
	t & Deque_##t##_front(Deque_##t * dp){														\
		return dp->data[dp->head];																\
	}																							\
	t & Deque_##t##_back(Deque_##t * dp){														\
		return dp->data[dp->tail];																\
	}																							\
																								\
																								\
	void Deque_##t##_push_back(Deque_##t * dp, t obj){											\
		printf("BONGOOOOOBALOOOOOOO");									\
		if(dp->numElems == dp->curSize ||													\
		dp->head == dp->tail+1 ||																\
		(dp->head == 0 && dp->tail == dp->curSize - 1)){	/*DEQUE FULL*/					\
			printf("DEQUE FULL.");																\
			t * temp_data = dp->data;	/*store old data while we resize*/						\
			dp->curSize *=2;																\
			dp->data = new t[dp->curSize]; 													\
			memcpy(&dp->data, &temp_data, sizeof(temp_data));							\
															\
															\
															\
															\
															\
															\
		}																						\
		else{																					\
			if(dp->head == -1 && dp->numElems == 0){	/* DEQUE EMPTY*/						\
				dp->head = 0;									\
				dp->tail = 0;									\
																\
			}																					\
			else if(dp->tail == dp->curSize - 1){	/*TAIL AT END OF DEQUE*/					\
				dp->tail = 0;														\
																		\
																		\
																		\
																		\
																		\
			}																					\
			else{	/*OTHERWISE JUST ADD TO BACK*/												\
				dp->tail += 1;															\
																			\
			}																\
		}																						\
		dp->data[dp->tail] = obj;																\
		dp->numElems += 1;																		\
		printf("BONGO");																		\
																								\
																								\
	}																					/*		\
	void Deque_##t##_push_front(Deque_##t * dp, t obj){											\
																	\
																	\
																	\
	}																		\
	void Deque_##t##_pop_back(Deque_##t * dp){													\
																\
		if(dp->numElems == 1){														\
			dp->head = -1;							\
			dp->tail = -1;							\
		}											\
		dp->numElems -= 1;																		\
																						\
																						\
	}																							\
																			\
																			\
																			\
																			\
																			\
	void Deque_##t##_pop_front(Deque_##t * dp){								\
														\
														\
	}*/
	
#endif
