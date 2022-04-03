#include <assert.h>
#include <memory.h>
#include <rummy/util/memory/common.h>
#include <stdlib.h>
#include <string.h>

void view_deleter(void *ptr) { ptr = NULL; }

void free_deleter(void *ptr) {
	if (ptr != NULL) {
		free(ptr);
		ptr = NULL;
	}
}

void view_copier(void **src, void **dst) {
	if (src != NULL && dst != NULL) {
		*dst = *src;
	} else {
		dst = NULL;
	}
}

void pointer_mover(void **src, void **dst) {
	if (src != NULL && dst != NULL) {
		*dst = *src;
		*src = NULL;
	} else {
		dst = NULL;
	}
	src = NULL;
}

void swap(void **a, void **b) {
	assert(a != NULL && b != NULL);
	void *tmp = *a;
	*a = *b;
	*b = tmp;
}