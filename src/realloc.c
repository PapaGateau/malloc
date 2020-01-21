/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 15:42:20 by plogan            #+#    #+#             */
/*   Updated: 2019/10/29 12:31:46 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	mem_copy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	temp_dest = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
}

int		check_ptr(void *ptr)
{
	t_range *range;
	t_block *block;

	if (!(range = *get_first_range()))
		return (0);
	while (range)
	{
		block = (t_block *)((char *)range + sizeof(t_range));
		while (block)
		{
			if ((void *)block + sizeof(t_block) == ptr)
			{
				return (1);
			}
			block = block->next;
		}
		range = range->next;
	}
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	void *new;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	new = start_realloc(ptr, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (new);
}

void	*start_realloc(void *ptr, size_t size)
{
	void		*new;
	t_block		*block;

	block = NULL;
	new = NULL;
	if (!ptr)
		return (start_malloc(size));
	if (!size && ptr)
	{
		start_free(ptr);
		return (start_malloc(16));
	}
	if (!check_ptr(ptr))
		return (NULL);
	else
	{
		block = (t_block *)((char *)ptr - sizeof(t_block));
		new = start_malloc(size);
		block->size < size ? mem_copy(new, ptr, block->size) :
			mem_copy(new, ptr, size);
		start_free(ptr);
	}
	return (new);
}
