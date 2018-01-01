# malloc

This project involves implementing a dynamic allocation mechanism of the memory.

# Functions

*malloc*
--
``
void  *malloc(size_t size);
``
The malloc () function allocates "size" bytes of memory and returns a pointer to the allocated memory.
In case of error, malloc () returns a NULL pointer

*realloc*
--
``
void  *realloc(void *ptr, size_t size);
``
The realloc () function attempts to change the size of the allocation pointed to by "ptr" to "size" bytes, and returns "ptr".
If there is not enough space at the memory location pointed to by "ptr", realloc () creates a new allocation, copying
as much data from the old allocation as possible within the size of the new allocation, release the old allocation and 
return a pointer to this new allocation. In case of error, realloc () returns a NULL pointer

*free*
--
``
void  free(void *ptr);
``
The free () function frees the allocation of the memory pointed to by "ptr". If "ptr" is NULL, free () does not do anything

# Start the program

- ```make```
- ```./run.sh ./test* ```
