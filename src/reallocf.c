/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:38:54 by plogan            #+#    #+#             */
/*   Updated: 2019/08/21 18:29:17 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void	*new;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	new = start_reallocf(ptr, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (new);
}

void	*start_reallocf(void *ptr, size_t size)
{
	void	*new;

	new = start_realloc(ptr, size);
	if (!new && (size > 0))
		start_free(ptr);
	return (new);
}
