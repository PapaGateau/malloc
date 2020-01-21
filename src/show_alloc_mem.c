/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:50:10 by plogan            #+#    #+#             */
/*   Updated: 2019/08/21 18:30:29 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

char	*get_range_type(int type)
{
	if (type == 0)
		return ("TINY : ");
	else if (type == 1)
		return ("SMALL : ");
	else
		return ("LARGE : ");
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_ft_malloc_mutex);
	start_show_alloc_mem();
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}

void	start_show_alloc_mem(void)
{
	t_range		*range;
	t_block		*block;
	size_t		total;

	total = 0;
	if (!(range = *get_first_range()))
		return ;
	while (range)
	{
		print_str(get_range_type(range->type));
		print_nbr_base((unsigned long)range, 16, 3);
		block = (t_block *)((char *)range + sizeof(t_range));
		while (block)
		{
			if (!block->freed && print_block(block))
				total += block->size;
			block = block->next;
		}
		range = range->next;
	}
	print_str("Total ");
	print_nbr_base((unsigned long)total, 10, 3);
}
