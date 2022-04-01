#include <assert.h>
#include <memory.h>
#include <rummy/util/memory/allocator.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void **alloc_array(size_t size) {
	void *array = malloc(size * sizeof(void *));
	assert(array != NULL);
	return array;
}

void free_array(void **array, size_t size, Deleter deleter) {
	if (array == NULL) {
		return;
	}
	if (deleter != NULL) {
		for (size_t i = 0; i < size; i++) {
			deleter(array[i]);
			array[i] = NULL;
		}
	} else {
		for (size_t i = 0; i < size; i++) {
			free(array[i]);
			array[i] = NULL;
		}
	}
	free(*array);
	*array = NULL;
}

void copy_array(void **src, void **dst, size_t size_src, size_t size_dst,
                Copier copier) {
	if (src == NULL || dst == NULL) {
		return;
	}
	if (copier != NULL) {
		for (size_t i = 0; i < size_src; i++) {
			copier(&src[i], &dst[i]);
		}
	} else {
		assert(size_src <= size_dst);
		memcpy(*dst, *src, size_src * sizeof(void *));
	}
}

void move_array(void **src, void **dst, size_t size_src, size_t size_dst,
                Mover mover) {
	if (src == NULL || dst == NULL) {
		return;
	}
	if (mover != NULL) {
		for (size_t i = 0; i < size_src; i++) {
			mover(&src[i], &dst[i]);
		}
	} else {
		assert(size_src <= size_dst);
		memmove(*dst, *src, size_src * sizeof(void *));
	}
}