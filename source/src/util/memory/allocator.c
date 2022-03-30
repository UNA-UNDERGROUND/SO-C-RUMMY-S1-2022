#include <assert.h>
#include <rummy/util/memory/allocator.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void **alloc_array(size_t size) {
	void *array = malloc(size * sizeof(void *));
	assert(array != NULL);
	return array;
}

void free_array(void ***array, size_t size, Deleter deleter) {
	if (array == NULL) {
		return;
	}
	if (deleter != NULL) {
		for (size_t i = 0; i < size; i++) {
			deleter((*array)[i]);
			(*array)[i] = NULL;
		}
	} else {
		for (size_t i = 0; i < size; i++) {
			free((*array)[i]);
			(*array)[i] = NULL;
		}
	}
	free(*array);
	*array = NULL;
}