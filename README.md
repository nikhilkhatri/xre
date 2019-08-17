# Xrē

A visual trace of your C data structures.
_We're going to call it Xre through the rest of this, because Xrē is really hard to type._

<p align="center">
	<img src="https://media.giphy.com/media/dAdEFJwevwxJgRlz0C/giphy.gif"/>
</p>


## Introduction

Xre allows you to implement any pointer-node based data-structures with minimum changes to the memory allocation portions of your code. Xre launches a local server which presents you with a visual representations of the nodes and data on your program's heap. This allows you to step through your program's visual trace, making it easy to spot dangling pointers, leaked memory and other pointer redirection errors.

## Functions

Three main functions are used to interact with Xre.

```
	void *node_malloc(size_t size, void **dest);
```
Behaves like malloc, but also tells xre that the space you've just allocated is for a node in your data structure. Places address of newly allocated space in `*dest` .
```	
	void xmalloc_free(void *);
```
Behaves like free. Also used by Xre to color nodes differently.
```
	void ptrcpy(void **dest, void *src);
```
Basically does `*dest = src`. The signature is more complex than seems necessary, but this information is needed by Xre to determine if the new source of the pointer is also a node. This ensures that you can have dynamic data structures, and the GUI will always reflect this accurately.
This function adds to client code complexity and we would love feedback on how we migh simplify this, while maintaining functionality.

## Prerequisites
- python-flask
- cytoscape - https://github.com/cytoscape/cytoscape.js
-- To use cytoscape-js, download the .js files found in the dist directory of branch 2.x of the above repo, and place them in `xre\src\server\static\scripts\` of your xre installation.

## Warning
The flask server launched must be manually killed before executing a new C program using xre. 
```
	ps -x | grep python
	kill -9 <proc-id>
```
This prevents multiple instances of the flask server from running simultaneously.

