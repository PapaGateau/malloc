/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:18:37 by plogan            #+#    #+#             */
/*   Updated: 2019/10/29 15:13:25 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/resource.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# define TINY_MAX_BLOCK_SIZE 128
# define TINY_RANGE_SIZE (4 * getpagesize())

# define SMALL_MAX_BLOCK_SIZE 1024
# define SMALL_RANGE_SIZE (32 * getpagesize())

extern pthread_mutex_t	g_ft_malloc_mutex;

typedef enum			e_bool
{
	false,
	true
}						t_bool;

typedef enum			e_range_type
{
	TINY,
	SMALL,
	LARGE
}						t_range_type;

typedef struct			s_block
{
	char				padding[12];
	t_bool				freed;
	size_t				size;
	struct s_block		*next;
}						t_block;

typedef struct			s_range
{
	char				padding[12];
	enum e_range_type	type;
	size_t				space;
	struct s_range		*next;
}						t_range;

/*
**						Library functions
*/
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					show_alloc_mem(void);

/*
**						Library functions (bonus)
*/
void					*reallocf(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);

/*
**						Process
*/
void					*start_malloc(size_t size);
void					*start_calloc(size_t count, size_t size);
void					*start_realloc(void *ptr, size_t size);
void					start_free(void *ptr);
void					*start_reallocf(void *ptr, size_t size);
void					start_show_alloc_mem(void);
t_range					**get_first_range(void);
t_block					*block_handler(size_t size, int type,
		size_t range_size);
t_block					*init_block(t_range *range, size_t block_size);
t_block					*check_free_blocks(int type, size_t size);
t_block					*split_block(t_block *block, size_t size);
void					print_str(char *str);
void					print_nbr_base(unsigned long nb, int base_size,
		int mode);
int						print_block(t_block *block);
void					bzero(void *s, size_t n);

#endif
