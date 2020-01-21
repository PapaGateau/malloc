/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:46:33 by plogan            #+#    #+#             */
/*   Updated: 2019/08/21 18:28:11 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*new;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	new = start_calloc(count, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (new);
}

void	*start_calloc(size_t count, size_t size)
{
	size_t	malloc_size;
	void	*ptr;
	t_block *block;

	size = (size + 15) & ~15;
	block = NULL;
	if (size == 0)
		malloc_size = count * 32;
	else
		malloc_size = count * size;
	if (!(ptr = start_malloc(malloc_size)))
		return (NULL);
	bzero(ptr, malloc_size);
	block = (t_block *)((char *)ptr - sizeof(t_block));
	return (ptr);
}
