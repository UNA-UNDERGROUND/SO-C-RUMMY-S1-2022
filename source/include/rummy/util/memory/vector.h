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
 * @brief Delete a Vector object
 *
 * @param vector the vector to delete, if NULL nothing is done
 * @param deleter the function to delete the data, if NULL, will call free()
 * instead
 *
 */
void delete_vector(Vector *vector, Deleter deleter);
