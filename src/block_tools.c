/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:38:05 by plogan            #+#    #+#             */
/*   Updated: 2019/04/23 15:38:35 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*init_block(t_range *range, size_t block_size)
{
	t_block	*new;
	t_block	*temp;

	temp = NULL;
	if (!range)
		return (NULL);
	if ((range->type == TINY && TINY_RANGE_SIZE - sizeof(t_range) >
range->space) || (range->type == SMALL && SMALL_RANGE_SIZE -
	sizeof(t_range) > range->space))
	{
		new = (t_block *)((char *)range + sizeof(t_range));
		while (new->next)
			new = new->next;
		temp = new;
		new = (t_block *)((char *)temp + sizeof(t_block) + temp->size);
		temp->next = new;
	}
	else
		new = (t_block *)((char *)range + sizeof(t_range));
	new->freed = false;
	new->size = block_size;
	new->next = NULL;
	range->space -= (block_size + sizeof(t_block));
	return (new);
}

t_block		*check_free_blocks(int type, size_t size)
{
	t_range *range;
	t_block	*block;

	range = *get_first_range();
	block = NULL;
	while (range)
	{
		if (range->type == type)
		{
			block = (t_block *)((char *)range + sizeof(t_range));
			while (block)
			{
				if (block->freed && block->size >= size + sizeof(t_block))
					return (block);
				block = block->next;
			}
		}
		range = range->next;
	}
	return (block);
}

t_block		*split_block(t_block *block, size_t size)
{
	t_block	*new;

	new = (t_block *)((char *)block + sizeof(t_block) + size);
	new->freed = 1;
	new->size = block->size - size - sizeof(t_block);
	new->next = block->next;
	block->freed = 0;
	block->size = size;
	block->next = new;
	return (block);
}
