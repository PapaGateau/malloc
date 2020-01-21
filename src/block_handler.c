/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:15:38 by plogan            #+#    #+#             */
/*   Updated: 2019/08/21 19:16:32 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_range		**get_first_range(void)
{
	static t_range	*range = NULL;

	return (&range);
}

t_range		*make_new_range(int type, size_t range_size, t_range *next)
{
	t_range *new;

	if ((new = (t_range *)mmap(0, range_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	new->type = type;
	new->space = range_size - sizeof(t_range);
	new->next = next;
	return (new);
}

t_range		*check_range_space(int type, size_t size)
{
	t_range	*temp;

	temp = *get_first_range();
	while (temp)
	{
		if (temp->type == type && temp->space >= (size + sizeof(t_block)))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

t_block		*block_handler(size_t size, int type, size_t range_size)
{
	t_range	*temp;
	t_block	*block;

	block = NULL;
	temp = NULL;
	if (!*get_first_range())
	{
		*get_first_range() = make_new_range(type, range_size, NULL);
		return (init_block(*get_first_range(), size));
	}
	else if (type != LARGE && (block = check_free_blocks(type, size)))
		return (split_block(block, size));
	else if (type != LARGE && (temp = check_range_space(type, size)))
		return (init_block(temp, size));
	else
	{
		temp = *get_first_range();
		while (temp->next)
			temp = temp->next;
		temp->next = make_new_range(type, range_size, NULL);
		return (init_block(temp->next, size));
	}
}
