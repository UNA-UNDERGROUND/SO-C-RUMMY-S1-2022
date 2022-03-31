#include <rummy/util/memory/vector.h>
#include <stdlib.h>

Vector *new_vector() {
	Vector *vector = malloc(sizeof(Vector));
	vector->size = 0;
	vector->capacity = 0;
	vector->data = NULL;
	return vector;
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