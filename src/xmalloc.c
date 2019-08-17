#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "xmalloc.h"

memchunk *alloced_data = NULL;
memchunk *alloced_nodes = NULL;

memchunk *free_data = NULL;
memchunk *free_nodes = NULL;

FILE *pype = NULL;

void *_find_chunk_from_ptr(void *ptr){
	memchunk *this_chunk = alloced_nodes;
	memchunk *retval = NULL;
	int i = 0;
	while (this_chunk){
		if ((ptr >= this_chunk->chunk) && (ptr < this_chunk->chunk + this_chunk->size)){
			return this_chunk->chunk;
		}
		this_chunk = this_chunk->next;
	}
	return retval;
}

int _move_memchunk(memchunk *chunk){
	// first check if chunk is a node
	memchunk *iter = alloced_nodes;
	while(iter != NULL){
		if(iter == chunk){ // This node is the one to be moved
			if(iter == alloced_nodes){
				alloced_nodes = alloced_nodes->next;
			}
			if(iter->prev){
				iter->prev->next = iter->next;
			}
			if(iter->next){
				iter->next->prev = iter->prev;
			}
			iter->next = free_nodes;
			iter->prev = NULL;
			
			if(free_nodes){
				free_nodes->prev = iter;
			}
			free_nodes = iter;
			
			return 0;
		}
		iter = iter->next;
	}

	// check if chunk is data
	iter = alloced_data;
	while(iter != NULL){
		if(iter == chunk){ // This node is the one to be moved
			if(iter == alloced_data){
				alloced_data = alloced_data->next;
			}
			if(iter->prev){
				iter->prev->next = iter->next;
			}
			if(iter->next){
				iter->next->prev = iter->prev;
			}
			iter->next = free_data;
			iter->prev = NULL;
			
			if(free_nodes){
				free_nodes->prev = iter;
			}

			free_data = iter;
			
			return 0;
		}
		iter = iter->next;
	}
	return -1;
}

int xmalloc_init(){
	
	// NOTE: this interface will probably change repeatedly while in dev
	// launches Flask server, opens pipe for logging
	// consider adding an atExit type event handler

	pype = popen("python3 ./../src/server/server_main.py", "w");

	if (pype == NULL){
		return -1;
	}

	return 0;
}

void *node_malloc(size_t size, void **dest){
	// *dest : out
	//  dest : in

	// obtain new chunk from the mm
	memchunk *new_chunk = malloc(sizeof(memchunk) + size);
	
	// sanity check
	if(new_chunk == NULL){
		return NULL;
	}
	
	// get pointer to base of chunk in which *dest resides
	memchunk *dest_chunk = _find_chunk_from_ptr(dest); // the pointer types here are an advanced postgrad problem, remember to ask in interview later
	
	// prepend to DLL
	new_chunk->next = alloced_nodes;
	new_chunk->prev = NULL;
	new_chunk->size = size;
	
	if (alloced_nodes){
		alloced_nodes->prev = new_chunk;
	}
	alloced_nodes = new_chunk;

	// place pointer to newly alloced block in outputretval =ble
	*dest = (void *) (new_chunk->chunk);

	if (dest_chunk) { // source pointer is also on heap
		fprintf(pype, "N:H:%x:%ld:%x\n", dest_chunk, dest-(void **)dest_chunk, new_chunk->chunk);
		fflush(pype);
	}
	else { // source pointer not on heap
		fprintf(pype, "N:S:%x:%x\n", dest, new_chunk->chunk);
		fflush(pype);
	}

	return (void *) new_chunk->chunk;
}

void *data_malloc(size_t size, void **dest){
	// *dest : out
	//  dest : in

	// obtain new chunk from the mm
	memchunk *new_chunk = malloc(sizeof(memchunk) + size);
	
	// sanity check
	if(new_chunk == NULL){
		return NULL;
	}
	
	// get pointer to base of chunk in which *dest resides
	memchunk *dest_chunk = _find_chunk_from_ptr(dest); // the pointer types here are an advanced postgrad problem, remember to ask in interview later

	// prepend to DLL
	new_chunk->next = alloced_data;
	new_chunk->prev = NULL;
	new_chunk->size = size;
	
	if (alloced_data){
		alloced_data->prev = new_chunk;
	}

	alloced_data = new_chunk;

	// place pointer to newly alloced block in output variable
	*dest = (void *) (new_chunk->chunk);

	if (dest_chunk) { // source pointer is also on heap
		fprintf(pype, "D:H:%x:%ld:%x\n", dest_chunk, dest-(void **)dest_chunk, new_chunk);
		fflush(pype);
	}
	else { // source pointer not on heap
		fprintf(pype, "D:S:%x:%x\n", dest, new_chunk);
		fflush(pype);
	}

	return (void *) new_chunk->chunk;
}

void xmalloc_free(void *ptr){
	if (ptr == NULL){
		return;
	}
	
	memchunk *this_chunk = (memchunk *)((char *) ptr - sizeof(memchunk)); // ????
	// DO NOT USE FREE, _move_memchunk may not work then
	// free(this_chunk); // This will not figure once I make the custom malloc
	
	// determine whether node or data
	// remove DLLnode from alloced
	// place DLLnode in freed
	int status = _move_memchunk(this_chunk);

	fprintf(pype, "F:%x\n", this_chunk->chunk);
	fflush(pype);
	return;
}

void ptrcpy(void **dest, void *src){
	
	*dest = src;
	
	memchunk *dest_chunk = _find_chunk_from_ptr(dest); // the pointer types here are an advanced postgrad problem, remember to ask in interview later

	if (dest_chunk) { // source pointer is also on heap
		fprintf(pype, "C:H:%x:%d:%x\n", dest_chunk, dest-(void **)dest_chunk, src);
		fflush(pype);
	}
	else { // source pointer not on heap
		fprintf(pype, "C:S:%x:%x\n", dest, src);
		fflush(pype);
	}
}

void xmalloc_bp(const char *label){
	
	fprintf(pype, "B:%s\n", label);
	fflush(pype);
	
	return;
}
