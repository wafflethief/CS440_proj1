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
		void (*push_back)(Deque_##t * , t );													\
		void (*push_front)(Deque_##t *, t);													\
		void (*pop_back)(Deque_##t *);															\
		void (*pop_front)(Deque_##t *);															\
		size_t (*size)(Deque_##t *);															\
		bool (*empty)(Deque_##t *);																\
		Deque_##t##_Iterator (*begin)(Deque_##t *);												\
		Deque_##t##_Iterator (*end)(Deque_##t *);									\
	};																							\
	struct Deque_##t##_Iterator{										\
		(*inc)(Deque_##t##_Iterator *);															\
		/*(*equal)();									\
		(*deref)();*/									\
											\
											\
											\
											\
	};										\
	\
	void Deque_##t##_dtor(Deque_##t * dp){														\
		if(dp)																					\
			free(dp->data);																		\
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
	void Deque_##t##_push_back(Deque_##t * dp, t obj){											\
		if(dp->numElems == dp->curSize ||													\
		dp->head == dp->tail+1 ||																\
		(dp->head == 0 && dp->tail == dp->curSize - 1)){	/*DEQUE FULL*/					\
			printf("DEQUE FULL");																\
			t * temp_data = dp->data;	/*store old data while we resize*/						\
			dp->curSize *=2;																\
			dp->data = new t[dp->curSize]; 													\
			memcpy(&dp->data, &temp_data, sizeof(temp_data));							\
															\
		}																						\
		else{																					\
			if(dp->head == -1 && dp->numElems == 0){	/* DEQUE EMPTY*/						\
				printf("Deque empty\n");						\
				dp->head = 0;									\
				dp->tail = 0;									\
																\
			}																					\
			else if(dp->tail == dp->curSize - 1){	/*TAIL AT END OF DEQUE*/					\
				printf("Tail at end of deque\n");												\
				dp->tail = 0;														\
																		\
			}																					\
			else{	/*OTHERWISE JUST ADD TO BACK*/												\
				printf("Otherwise just to back\n");											\
				dp->tail += 1;															\
																			\
			}																\
		}																						\
		dp->data[dp->tail] = obj;																\
		dp->numElems += 1;																		\
																								\
	}																							\
	void Deque_##t##_push_front(Deque_##t * dp, t obj){											\
		if(dp->numElems == dp->curSize ||											\
		(dp->head == 0 && dp->tail == dp->curSize - 1)){										\
			printf("deque full\n");												\
			t * temp_data = dp->data;												\
			dp->curSize *= 2;												\
			dp->data = new t[dp->curSize];												\
			memcpy(&dp->data, &temp_data, sizeof(temp_data));									\
		}													\
		else{													\
			if(dp->head == -1 && dp->numElems == 0){				\
				printf("deque empty\n");											\
				dp->head = 0;																	\
				dp->tail = 0;																	\
			}												\
			else if (dp->head == 0){												\
				printf("head at first pos of deque\n");											\
				dp->head = dp->curSize - 1;														\
			}												\
			else{																				\
				printf("just adding to front\n");										\
				dp->head -= 1;												\
															\
			}												\
		}													\
		dp->data[dp->head] = obj;																\
		dp->numElems += 1;																		\
	}																							\
	void Deque_##t##_pop_front(Deque_##t * dp){												\
		if(!dp || dp->numElems == 0 || (dp->head == -1 && dp->tail == 0)){						\
			printf("Cannot pop from empty queue");												\
			return ;																			\
		}																						\
		else if(dp->head == dp->tail){					\
			printf("Only one elem to pop");				\
			dp->head = -1;														\
			dp->tail = -1; /*change to -1?*/										\
		}																						\
		else{													\
			if(dp->head == dp->curSize - 1){												\
				dp->head = 0;												\
			}												\
			else{												\
				dp->head++;												\
			}												\
			/*should I delete the object?*/												\
		}													\
		dp->numElems--;										\
	}														\
	void Deque_##t##_pop_back(Deque_##t * dp){													\
		if(!dp || dp->numElems == 0 || (dp->head == -1 && dp->tail == 0)){						\
			printf("Cannot pop from empty queue");												\
			return ;																			\
		}																						\
		if(dp->head == dp->tail){													\
			printf("only one elem to pop");													\
			dp->head = -1;																		\
			dp->tail = -1;																		\
		}													\
		else if(dp->tail == 0){													\
			dp->tail = dp->curSize - 1;											\
		}													\
		else{													\
			dp->tail--;													\
		}													\
		dp->numElems--;																			\
	}																							\
	void Deque_##t##_ctor(Deque_##t * dp, bool(*func)(const t &o1, const t &o2)){				\
		dp->data = /*(t*)malloc(50*sizeof(t));*/new t[50];										\
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
		dp->push_back = &(Deque_##t##_push_back);												\
		dp->push_front = &(Deque_##t##_push_front);												\
		dp->pop_front = &(Deque_##t##_pop_front);										\
		dp->pop_back = &(Deque_##t##_pop_back);										\
												\
	}

#endif
