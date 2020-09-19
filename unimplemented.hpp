																								\
	void Deque_##t##_push_back(Deque_##t * dp, t obj){											\
		printf("BONGOOOOOBALOOOOOOO");									\
		if(dp->numElems == dp->curSize ||													\
		dp->head == dp->tail+1 ||																\
		(dp->head == 0 && dp->tail == dp->curSize - 1)){	/*DEQUE FULL*/					\
			printf("DEQUE FULL");																\
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
	}	/*																						\
	void Deque_##t##_push_front(Deque_##t * dp, t obj){											\
																	\
																	\
																	\
	}																		\
	void Deque_##t##_pop_back(Deque_##t * dp){													\
																\
