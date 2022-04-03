#include <assert.h>
#include <rummy/util/memory/vector.h>
#include <stdlib.h>

Vector *new_vector() {
	Vector *vector = malloc(sizeof(Vector));
	vector->size = 0;
	vector->capacity = 0;
	vector->data = NULL;
	return vector;
}

void vector_push_back(Vector *vector, void *element) {
	if (vector->size == vector->capacity) {
		vector_resize(vector, vector->capacity * 2);
	}
	vector->data[vector->size] = element;
	vector->size++;
}

void vector_remove(Vector *vector, size_t index) {
	if (index >= vector->size) {
		return;
	}
	for (size_t i = index; i < vector->size - 1; i++) {
		vector->data[i] = vector->data[i + 1];
	}
	vector->size--;
}

void vector_resize(Vector *vector, size_t new_capacity) {
	assert(new_capacity > 0);
	assert(vector->size <= new_capacity);
	// alloc a new array
	void **new_data = malloc(new_capacity * sizeof(void *));
	// copy old data to new array
	for (size_t i = 0; i < vector->size; i++) {
		new_data[i] = vector->data[i];
	}
	// free old array
	free(vector->data);
	// update vector
	vector->data = new_data;
	vector->capacity = new_capacity;
}

void *vector_top(Vector *vector) {
	assert(vector->size > 0);
	return vector->data[vector->size - 1];
}

void delete_vector(Vector *vector, Deleter deleter) {
	if (vector == NULL) {
		return;
	}
	if (vector->data != NULL) {
		if (deleter != NULL) {
			for (size_t i = 0; i < vector->size; i++) {
				deleter(vector->data[i]);
			}
		} else {
			for (size_t i = 0; i < vector->size; i++) {
				free(vector->data[i]);
				vector->data[i] = NULL;
			}
		}
		free(vector->data);
		vector->data = NULL;
	}
	free(vector);
}