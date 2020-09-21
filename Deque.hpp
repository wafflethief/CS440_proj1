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
		long head; 																				\
		long tail;																				\
		bool isFull;																			\
		size_t numElems;																		\
		long curSize;																			\
		char type_name[strlen("Deque_"#t) + 1];/* len of type + nullbyte*/			\
		void (*ctor)(Deque_##t * , bool(*)(const t &, const t &));							\
		void (*dtor)(Deque_##t *);															\
		t & (*front)(Deque_##t *);																\
		t & (*back)(Deque_##t *);																\
		void (*push_back)(Deque_##t * , t );													\
		void (*push_front)(Deque_##t *, t);														\
		void (*pop_back)(Deque_##t *);															\
		void (*pop_front)(Deque_##t *);															\
		size_t (*size)(Deque_##t *);															\
		bool (*empty)(Deque_##t *);																\
		Deque_##t##_Iterator  (*begin)(Deque_##t *);											\
		Deque_##t##_Iterator (*end)(Deque_##t *);												\
		t & (*at)(Deque_##t *, size_t);															\
		void (*clear)(Deque_##t *);																\
		bool (*equal)(Deque_##t, Deque_##t);											\
		bool (*compar)(const t &, const t &);									\
		void (*sort)(Deque_##t *, Deque_##t##_Iterator , Deque_##t##_Iterator );\
		int (*eq)(const void *, const void *, void *);	\
	};																						\
	struct Deque_##t##_Iterator{										\
		void (*inc)(Deque_##t##_Iterator *);					\
		int value;														\
		t & (*deref)(Deque_##t##_Iterator *);									\
		bool (*equal)(Deque_##t##_Iterator, Deque_##t##_Iterator );					\
		Deque_##t * deq;									\
		void (*dec)(Deque_##t##_Iterator *);									\
											\
	};										\
												\
	void Deque_##t##_dtor(Deque_##t * dp){														\
		if(dp && dp->data != nullptr){			\
			free(dp->data);/*delete dp->data;*/											\
		}																				\
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
		if(dp->head == dp->tail+1 ||(dp->head == 0 && dp->tail == dp->curSize - 1)){	/*DEQUE FULL*/		\
			t * temp_data = dp->data;								\
			dp->data = (t*)malloc(sizeof(t)*dp->curSize*2);				\
			if(dp->head > dp->tail){													\
				memcpy(&(dp->data[0]), &(temp_data[0]), sizeof(t)*(dp->tail + 1));		\
				memcpy(&(dp->data[dp->curSize + dp->head]), &(temp_data[dp->head]), sizeof(t)*(dp->curSize - dp->head));\
				dp->head += dp->curSize;										\
				dp->tail += 1;										\
				free(temp_data);										\
			}													\
			else if(dp->head < dp->tail){													\
				memcpy(&(dp->data[0]), &(temp_data[0]), sizeof(t)*(dp->curSize));					\
												\
												\
				dp->tail += 1;								\
				free(temp_data);								\
			}																		\
			dp->curSize *= 2;								\
		}																						\
		else{																					\
			if(dp->head == -1 && dp->numElems == 0){	/* DEQUE EMPTY*/						\
				/*printf("Deque empty\n");*/						\
				dp->head = 0;									\
				dp->tail = 0;									\
			}																					\
			else if(dp->tail == dp->curSize - 1){	/*TAIL AT END OF DEQUE*/					\
				/*printf("Tail at end of deque\n");*/											\
				dp->tail = 0;														\
			}																					\
			else{	/*OTHERWISE JUST ADD TO BACK*/												\
				/*printf("Otherwise just to back\n");*/											\
				dp->tail += 1;															\
			}																\
		}																						\
		dp->tail %= dp->curSize;												\
		dp->data[dp->tail] = obj;											\
		dp->numElems += 1;																		\
	}																							\
	void Deque_##t##_push_front(Deque_##t * dp, t obj){											\
		if(			\
		(dp->head == 0 && dp->tail == dp->curSize - 1)){										\
			t * temp_data = dp->data;					\
			dp->data = (t*)malloc(sizeof(t)*dp->curSize*2);				\
			if(dp->head > dp->tail){													\
				memcpy(&(dp->data[0]), &(temp_data[0]), sizeof(t)*(dp->tail + 1));		\
				memcpy(&(dp->data[dp->curSize + dp->head]), &(temp_data[dp->head]), sizeof(t)*(dp->curSize - dp->head));\
				dp->head += dp->curSize -1;										\
			}													\
			else if(dp->head < dp->tail){													\
				memcpy(&(dp->data[0]), &(temp_data[0]), sizeof(t)*(dp->curSize));					\
				dp->head -= 1;								\
			}																		\
			free(temp_data);																\
		}																			\
		else{													\
			if(dp->head == -1 && dp->numElems == 0){				\
				/*printf("deque empty\n");			*/								\
				dp->head = 0;																	\
				dp->tail = 0;																	\
			}												\
			else if (dp->head == 0){												\
				/*printf("head at first pos of deque\n");*/										\
				dp->head = dp->curSize - 1;														\
			}												\
			else{																				\
			/*	printf("just adding to front\n");	*/									\
				dp->head -= 1;												\
															\
			}												\
		}													\
		dp->head %= dp->curSize;											\
		dp->data[dp->head] = obj;																\
		dp->numElems += 1;																		\
	}																							\
	void Deque_##t##_pop_front(Deque_##t * dp){												\
		if(!dp || dp->numElems == 0 || (dp->head == -1 && dp->tail == 0)){						\
			printf("Cannot pop from empty queue");												\
			return ;																			\
		}																						\
		else if(dp->head == dp->tail){ /*what about overlap?*/					\
			/*printf("Only one elem to pop");		*/		\
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
		}													\
		dp->numElems--;										\
	}														\
	void Deque_##t##_pop_back(Deque_##t * dp){													\
		if(!dp || dp->numElems == 0 || (dp->head == -1 && dp->tail == 0)){						\
			printf("Cannot pop from empty queue");											\
			return ;																			\
		}																						\
		if(dp->head == dp->tail){													\
			/*printf("only one elem to pop");	*/												\
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
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator * it){					\
		if(!it){												\
			printf("uninitialized iterator");													\
			return ;																			\
		}													\
		else{											\
			it->value += 1;															\
			it->value %= it->deq->curSize;											\
		}																						\
	}																							\
	t & Deque_##t##_Iterator_deref(Deque_##t##_Iterator * it){									\
		/*printf("Bob I want a divorce\n");		*/												\
		if (it)	return (it->deq->data)[it->value];												\
		else return (it->deq->data)[0];															\
	}																							\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it, Deque_##t##_Iterator iter){		\
		return (it.value) == iter.value;									\
	}																				\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator * it){								\
		it->value -= 1;															\
		it->value %= it->deq->curSize;															\
	}																\
	t & Deque_##t##_at(Deque_##t * dp, size_t i){								\
		i += dp->head;											\
		return dp->data[i%dp->curSize];							\
		/*as logically wrong as this seems, it doth work*/								\
	}													\
	void Deque_##t##_clear(Deque_##t * dp){													\
		dp->numElems = 0;																\
		dp->head = -1;								\
		dp->tail = 0;																	\
	}																					\
	int Deque_##t##_eq(const void * ob1, const void * ob2, void * dp){								\
		/*cast void pointers to correct types*/								\
		t banana1 = *(t*)ob1;					\
		t banana2 = *(t*)ob2;					\
		Deque_##t * deq = (Deque_##t *) dp;					\
		if (deq->compar(banana1, banana2)) return -1; /*ob1 > ob2*/					\
		else if (deq->compar(banana2, banana1)) return 1;	/*ob1 < ob2 or true*/						\
		return 0; /*values are equal*/								\
	}								\
	void Deque_##t##_sort(Deque_##t * dp, Deque_##t##_Iterator it2, Deque_##t##_Iterator it1){	\
		size_t range = (it1.value < it2.value) ? (it2.value-it1.value) : (it1.value - it2.value);		\
																										\
		qsort_r(&(dp->data[it2.value]), range, sizeof(t),(int(*)(const void* o1,const void* o2, void *))dp->eq, dp);\
												\
	}																						\
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t * dp){									\
		Deque_##t##_Iterator it;									\
		it.deq = dp;														\
		it.value = dp->head;												\
		it.inc = &(Deque_##t##_Iterator_inc);								\
		it.deref = &(Deque_##t##_Iterator_deref);												\
		it.dec = &(Deque_##t##_Iterator_dec);										\
		return it;										\
	}																							\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t * dp){										\
		Deque_##t##_Iterator it;													\
		it.deq = dp;												\
		it.value = dp->tail + 1;											\
		it.inc = &(Deque_##t##_Iterator_inc);												\
		it.deref = &(Deque_##t##_Iterator_deref);												\
		it.dec = &(Deque_##t##_Iterator_dec);										\
		return it;													\
	}																							\
	bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){										\
		if((deq1.numElems != deq2.numElems) || (deq1.curSize != deq2.curSize))					\
			return false;															\
		Deque_##t##_Iterator it1 = deq1.begin(&deq1);								\
		Deque_##t##_Iterator it2 = deq2.begin(&deq2);								\
																						\
		while(!Deque_##t##_Iterator_equal(it1, deq1.end(&deq1))){							\
			bool yum = deq1.compar(it1.deref(&it1), it2.deref(&it2));							\
			bool y2 = deq2.compar(it2.deref(&it2), it1.deref(&it1));					\
			if(y2 || yum) return false;													\
			it1.inc(&it1);										\
			it2.inc(&it2);									\
		}												\
		return true;											\
	}																		\
	void Deque_##t##_ctor(Deque_##t * dp, bool(*func)(const t &o1, const t &o2)){				\
		dp->data = /*new t[10*sizeof(t)];*/(t*)malloc(sizeof(t)*10);							\
		dp->head = -1;																			\
		dp->tail = 0;																			\
		dp->isFull = false;																		\
		dp->numElems = 0;																		\
		dp->curSize = 10;																		\
		strcpy(dp->type_name, "Deque_"#t);														\
		dp->dtor = &(Deque_##t##_dtor);															\
		dp->front =	&(Deque_##t##_front);														\
		dp->back =	&(Deque_##t##_back);														\
		dp->size = 	&(Deque_##t##_size);														\
		dp->empty = &(Deque_##t##_empty);														\
		dp->push_back = &(Deque_##t##_push_back);												\
		dp->push_front = &(Deque_##t##_push_front);												\
		dp->pop_front = &(Deque_##t##_pop_front);										\
		dp->pop_back = &(Deque_##t##_pop_back);											\
		dp->begin = &(Deque_##t##_begin);												\
		dp->end = &(Deque_##t##_end);													\
		dp->at = &(Deque_##t##_at);													\
		dp->clear = &(Deque_##t##_clear);											\
		dp->equal = &(Deque_##t##_equal);											\
		dp->compar = (func);																	\
		dp->eq = &(Deque_##t##_eq);																\
		dp->sort = &(Deque_##t##_sort);					\
	}

#endif
