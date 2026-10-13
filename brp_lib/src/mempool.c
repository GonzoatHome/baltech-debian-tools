#include "brp_lib/mempool.h"

#ifdef UNITTEST
void* realloc_testing(void *, size_t);
void  free_testing(void *);
#define realloc realloc_testing
#define free free_testing
#endif


struct brp_mempool_object_t {
	brp_mempool* mempool;
	struct brp_mempool_object_t* prev;
	struct brp_mempool_object_t* next;
	unsigned char buf[];
};


/*
 * Internal method to reallocate a mempool.
 * Based on the size for the contained buffer.
 */
struct brp_mempool_object_t* realloc_mempool_object(
		struct brp_mempool_object_t* obj, size_t buf_size)
{
	size_t min_size = sizeof(struct brp_mempool_object_t) + buf_size;
	size_t realloc_size = 1;
	while(min_size > realloc_size)
		realloc_size <<= 1;
	return (struct brp_mempool_object_t*)realloc(obj, realloc_size);
}

brp_buf brp_mempool_create_buf(brp_mempool *mempool, size_t initial_size)
{
	struct brp_mempool_object_t* obj = realloc_mempool_object(
			NULL, initial_size);
	
	if(obj == NULL)
		return NULL;
	
	obj->mempool = mempool;
	obj->prev = NULL;
	if(*mempool == NULL)
		obj->next = NULL;
	else {
		(*mempool)->prev = obj;
		obj->next = *mempool;
	}
	*mempool = obj;

	return (brp_buf)&(obj->buf);
}

brp_buf brp_mempool_resize_buf(brp_buf buf, size_t new_size)
{
	struct brp_mempool_object_t* old_obj =
			(struct brp_mempool_object_t*)
					(buf - sizeof(struct brp_mempool_object_t));
	struct brp_mempool_object_t* prev_obj = old_obj->prev;
	struct brp_mempool_object_t* next_obj = old_obj->next;
	struct brp_mempool_object_t* new_obj =
			realloc_mempool_object(old_obj, new_size);
	
	if (new_obj == NULL)
	{
		if(prev_obj == NULL)
			*(old_obj->mempool) = next_obj;
		else
			prev_obj->next = next_obj;

		if(next_obj != NULL)
			next_obj->prev = prev_obj;
		return NULL;
	}
	
	if(old_obj != new_obj)
	{
		if(prev_obj == NULL)
			*(new_obj->mempool) = new_obj;
		else
			prev_obj->next = new_obj;
		
		if(next_obj != NULL)
			next_obj->prev = new_obj;
	}
	
	return new_obj->buf;
}

void brp_mempool_free(brp_mempool* mempool)
{
	struct brp_mempool_object_t* next_obj;
	while(*mempool != NULL) {
		next_obj = (*mempool)->next;
		free(*mempool);
		*mempool = next_obj;
	}
}
