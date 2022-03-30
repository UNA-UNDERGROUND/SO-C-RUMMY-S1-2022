#pragma once
#include <stddef.h>
#include <stdlib.h>
// contains code used for memory allocation/deallocation and management

/**
 * @brief Function deleter for a list of pointers in a array, useful for objects
 * that need custom deallocation
 *
 */
typedef void (*Deleter)(void *);

/**
 * @brief tries to allocate memory for an array of size elements
 *
 * @note if the allocation fails, the program exits with EXIT_FAILURE
 *
 * @param size the size of the array
 * @param element_size the size of each element
 * @return void* the pointer to the allocated memory
 */
void **alloc_array(size_t size);

/**
 * @brief clears the memory allocated for an array of pointers, and frees the
 * memory for each element not null of the array, then set the pointer to null
 *
 * @param ptr the pointer to the array, if null, nothing is done
 * @param size the size of the array
 * @param deleter the function to call to free the memory of each element, if
 * null just free the memory
 */
void free_array(void ***ptr, size_t size, Deleter deleter);