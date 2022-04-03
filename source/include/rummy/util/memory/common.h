#pragma once
#include <stddef.h>

// common memory definitions

/**
 * @brief Function deleter for a list of pointers in a array, useful for objects
 * that need custom deallocation
 *
 */
typedef void (*Deleter)(void *ptr);

/**
 * @brief Function copier for two elements of the same type
 *
 */
typedef void (*Copier)(void **src, void **dest);

/**
 * @brief Function mover for two elements of the same type
 *
 */
typedef void (*Mover)(void **src, void **dest);

/**
 * @brief custom deleter that does nothing (set the pointer to NULL), useful for
 * views
 *
 * @param ptr the pointer to the object that will be set to NULL
 *
 */
void view_deleter(void *ptr);

/**
 * @brief custom deleter that frees the memory using free() and then set to NULL
 *
 * @param ptr the pointer to the object that will be freed
 *
 */
void free_deleter(void *ptr);

/**
 * @brief view copier just copy the pointer, but does not copy the object
 *
 * @param src the source pointer, if NULL, the destination will be set to NULL
 * @param dest the destination pointer
 *
 */
void view_copier(void **src, void **dst);

/**
 * @brief moves the pointer value from src to dest, src is set to NULL
 *
 * @param src the source pointer, if NULL, the destination will be set to NULL
 * @param dest the destination pointer
 *
 */
void pointer_mover(void **src, void **dst);

/**
 * @brief swaps the values of two pointers
 *
 * @param a the first pointer
 * @param b the second pointer
 */
void swap(void **a, void **b);