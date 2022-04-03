#pragma once
#include <rummy/util/memory/common.h>
#include <stddef.h>

#define VECTOR_INITIAL_CAPACITY 4

typedef struct {
	size_t size;
	size_t capacity;
	void **data;
} Vector;

/**
 * @brief Create a Vector object
 *
 * @return Vector* the vector created
 */
Vector *new_vector();

/**
 * @brief push a new element to the vector
 *
 * @param vector the vector to push
 * @param element the element to push
 */
void vector_push_back(Vector *vector, void *element);

/**
 * @brief pop the last element from the vector
 *
 * @param vector the vector to pop
 * @return void* the element popped
 */
void vector_remove(Vector *vector, size_t index);

/**
 * @brief resize the vector using malloc
 *
 * @note if the new capacity is smaller the operation will assert
 *
 * @param vector the vector to resize
 */
void vector_resize(Vector *vector, size_t new_capacity);

/**
 * @brief get the element at the top of the vector
 *
 * @param vector the vector to get the element from
 */
void *vector_top(Vector *vector);

/**
 * @brief Delete a Vector object
 *
 * @param vector the vector to delete, if NULL nothing is done
 * @param deleter the function to delete the data, if NULL, will call free()
 * instead
 *
 */
void delete_vector(Vector *vector, Deleter deleter);
