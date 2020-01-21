/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:48:18 by plogan            #+#    #+#             */
/*   Updated: 2019/04/23 15:48:58 by plogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	print_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	make_str(unsigned long nb, unsigned long p, int size, int base_size)
{
	char	str[size];
	char	*base;
	int		i;

	str[size] = '\0';
	i = 0;
	base = "0123456789ABCDEF";
	while (i < size)
	{
		str[i++] = base[(nb / p) % base_size];
		p = p / base_size;
	}
	if (base_size == 16)
		print_str("0x");
	print_str(str);
	if (base_size == 10)
		print_str(" bytes");
}

void	print_nbr_base(unsigned long nb, int base_size, int mode)
{
	unsigned long	temp;
	unsigned long	p;
	int				size;

	p = 1;
	size = 1;
	temp = nb;
	while (temp > (unsigned long)(base_size - 1) && (p = p * base_size))
	{
		temp = temp / base_size;
		size++;
	}
	make_str(nb, p, size, base_size);
	if (mode == 1)
		print_str(" - ");
	if (mode == 2)
		print_str(" : ");
	if (mode == 3)
		print_str("\n");
	return ;
}

int		print_block(t_block *block)
{
	print_nbr_base((unsigned long)block + sizeof(t_block), 16, 1);
	print_nbr_base((unsigned long)block + sizeof(t_block) + block->size,
			16, 2);
	print_nbr_base((unsigned long)block->size, 10, 3);
	return (1);
}
