#pragma once
#include <rummy/util/memory/common.h>

// contains code used for memory allocation/deallocation and management

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
void free_array(void **ptr, size_t size, Deleter deleter);

/**
 * @brief copies the content of an array of pointers to another array of
 * pointers
 *
 * @note an assertion is raised if the size of the source array is greater than
 * the size of the destination array
 *
 * @param src the source array if null, nothing is done
 * @param dst the destination array if null, nothing is done
 * @param size_src the size of the source array
 * @param size_dst the size of the destination array
 * @param copier the function to call to copy the content of each element, if
 * NULL it will copy the memory
 *
 */
void copy_array(void **src, void **dst, size_t size_src, size_t size_dst,
                Copier copier);

/**
 * @brief moves the content of an array of pointers to another array of pointers
 *
 * @note an assertion is raised if the size of the source array is greater than
 * the size of the destination array
 *
 * @param src the source array if null, nothing is done
 * @param dst the destination array if null, nothing is done
 * @param size_src the size of the source array
 * @param size_dst the size of the destination array
 * @param mover the function to call to move the content of each element, if
 * NULL it will move the memory
 *
 */
void move_array(void **src, void **dst, size_t size_src, size_t size_dst,
                Mover mover);