
#ifndef XMALLOC_H
#define XMALLOC_H

typedef struct Memchunk {
	struct Memchunk *prev;
	struct Memchunk *next;
	size_t size;
	char chunk[]; // C99 standard, char is irrelevant
} memchunk;

int xmalloc_init(); // 0 on success, -1 on failure

void *node_malloc(size_t size, void **dest); // dest holds pointer to location where the pointer to newly assigned memory will be placed
void *data_malloc(size_t size, void **dest);

// void *node_calloc(size_t nmemb, size_t size, void **dest);
// void *data_calloc(size_t nmemb, size_t size, void **dest);

void xmalloc_free(void *);

void ptrcpy(void **dest, void *src); // *dest = src;

#endif

// dest -> loc -> NULL
// dest -> loc -> newmem *dest = newmem;