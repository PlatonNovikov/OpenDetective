#ifndef VECTOR_H
#define VECTOR_H

/*
A simple vector lib
Honestly, i have no idea why do i write it from scratch
It's slow and pointless
i guess just for fun
*/

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_vec
{
	void	**data;
	size_t	size;
	size_t	capacity;
} t_vec;

t_vec	*init_vec(void)
{
	t_vec *vec = (t_vec *)calloc(1, sizeof(t_vec));
	if (!vec)
		exit(EXIT_FAILURE);
	return vec;
}

void	vec_append(t_vec *vec, void *ptr)
{
	if (!vec->data)
	{
		vec->data = (void **)calloc(1, sizeof(void *));
		vec->data[0] = ptr;
		vec->capacity = 1;
		vec->size = 1;
		return ;
	}

	if (vec->size >= vec->capacity)
	{
		vec->capacity *= 2;
		vec->data = (void **)realloc(vec->data, sizeof(void *) * vec->capacity);
		if (!vec->data)
			exit(EXIT_FAILURE);
	}

	vec->data[vec->size] = ptr;
	vec->size++;
}

bool	vec_ord_rm(t_vec *vec, void *ptr)
{
	size_t i = 0;

	while (i < vec->size && vec->data[i] != ptr)
		i++;

	if (i == vec->size)
		return false;

	vec->data[i] = vec->data[vec->size - 1];
	vec->size--;

	return true;
}

#endif
