/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:51:30 by plogan            #+#    #+#             */
/*   Updated: 2019/10/29 14:47:13 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*malloc(size_t size)
{
	void	*new;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	new = start_malloc(size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (new);
}

void		*start_malloc(size_t size)
{
	struct rlimit	rlp;
	t_block			*block;

	getrlimit(RLIMIT_DATA, &rlp);
	size = (size + 15) & ~15;
	if ((rlp.rlim_cur - sizeof(t_range) - sizeof(t_block)) < size)
		return (NULL);
	if (size <= TINY_MAX_BLOCK_SIZE)
		block = block_handler(size, TINY, TINY_RANGE_SIZE);
	else if (size <= SMALL_MAX_BLOCK_SIZE)
		block = block_handler(size, SMALL, SMALL_RANGE_SIZE);
	else
		block = block_handler(size, LARGE, size + sizeof(t_range) +
				sizeof(t_block));
	return ((void *)((char *)block + sizeof(t_block)));
}
