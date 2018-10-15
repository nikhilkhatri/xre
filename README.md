# Xrē

A visual trace of your C data structures

## Introduction

Xre allows you to implement any pointer-node based data-structures with minimum changes to the memory allocation portions of your code. Xre launches a local server which presents you with a visual representations of the nodes and data on your program's heap. This allows you to step through your program's visual trace, making it easy to spot dangling pointers, leaked memory and other pointer redirection errors.

## functions

Three main functions are used to interact with xre.

```
	void *node_malloc(size_t size, void **dest);
```

```	
	void xmalloc_free(void *);
```

```
	void ptrcpy(void **dest, void *src);
```

## Prerequisites
	python-flask
